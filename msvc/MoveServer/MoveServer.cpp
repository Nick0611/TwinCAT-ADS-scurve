#include <CPSAPI/CPSAPI.h>
#include <CPSAPI/CPSDef.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> //控制台输入输出头文件
#include <windows.h> //windowsAPI的函数声明和宏
#include <time.h>
#include <winbase.h> 
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h" //结构体和常量的声明
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h" // ADS函数的声明
#include <chrono>
#include <cmath>
#include "queuedefine.h"
#include <thread>
#include <stdlib.h> 
#include <mutex>
#include <queue>
#include <cstdlib>
#include <iomanip> //要用到格式控制符
#include <math.h>
#include "MyADSDef.h"
#include "fifth_order_interpolation.h"
#include "scurve.h"
#include "include.h"

queuedefine queue1;//插值后所有点队列
queuedefine queue2;
queuedefine queue3;
queuedefine queue4;
queuedefine queue1_flag;//插值后关键点对应flag置1
queuedefine queue2_flag;
queuedefine queue3_flag;
queuedefine queue4_flag;
double t0, t1, t2, t3, t4, t5, t6, t7;
bool FillFlag;//PLC需求填充缓存标志位
bool MoveDoneFlag;//运动完成标志位
short index_x;//辅助判断运动完成的标志，x是PLC中缓存数组正在执行的index
std::mutex mtx;
ST_RspMove_POS RSP_POS = { };
ST_RspMove_VEL RSP_VEL = { };
bool thread1; bool thread2;
bool Init_Done_Flag;

class Handler : public CCPSEventHandler
{
public:
	Handler(CCPSAPI * api) :m_api(api)
	{}
	// Connect event
	virtual void OnConnected()
	{
		m_api->RegisterDevice();
		printf("OnConnected\n");
	}
	// Disconnect event
	virtual void OnDisconnected()
	{
		printf("OnDisconnected\n");
	}
	// Message event
	virtual void OnMsg(uint32_t from_id, uint32_t msg_type, const char* data, uint32_t msg_len)
	{
		switch (msg_type)
		{
		case MSG_REQ_MOVE://位置点数据
		{
			this->OnReqMoveProcess(from_id, (ST_DriverReqMove*)data);
			break;
		}
		case MSG_CMD_INIT:
		{
			std::cout << "收到初始化请求" << '\n';
			this->OnReqInit(from_id);
			break;
		}
		case MSG_CMD_STOP:
		{
			std::cout << "收到停止请求" << '\n';
			this->OnReqMoveStop(from_id);
			break;
		}
		case MSG_CMD_RESET:
		{
			std::cout << "收到复位请求" << '\n';
			this->OnReqReset(from_id);
			break;
		}
		case MSG_CMD_CONTINUE:
		{
			std::cout << "收到继续请求" << '\n';
			this->OnReqContinue(from_id);
			break;
		}
		case MSG_RSP_MOVE_POS:
		{
			m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&RSP_POS, sizeof(ST_RspMove_POS));
			m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_VEL, (const char*)&RSP_VEL, sizeof(ST_RspMove_VEL));
			break;
		}
		default:
			break;
		}
	}

	void OnReqInit(uint32_t from_id)//向电机发送初始化命令
	{
		bool req_Init = 1;
		MyADSDef ADS_OnReqInit;
		Init_Done_Flag = ADS_OnReqInit.ReadBool(0x0, 0x78);//读缓存填充标志位
		if (!Init_Done_Flag)
		{
			ADS_OnReqInit.WriteBool(from_id, 0x60, 0x1, req_Init);
		}
		//if (Init_Done_Flag)
		//{
			ST_CMDInitRsp rsp = { 0 };
		Sleep(10000);
			m_api->SendDeviceMsg(CONTROL_SERVER_APP_ID, MSG_CMD_INIT_RSP, (const char*)&rsp, sizeof(ST_CMDInitRsp));
		//}	
		std::cout << "已经初始化" << '\n';	
	}
	void OnReqMoveStop(uint32_t from_id)//向电机发送急停命令
	{
		MyADSDef ADS_OnReqMoveStop;
		bool req_stop = 1;
		ADS_OnReqMoveStop.WriteBool(from_id, 0x10, 0x1, req_stop);
		std::cout << "已经stop" << '\n';
	}
	void OnReqReset(uint32_t from_id)//向电机发送复位命令
	{
		MyADSDef ADS_OnReqReset;
		bool req_reset = 1;
		ADS_OnReqReset.WriteBool(from_id, 0x30, 0x1, req_reset);//6
		std::cout << "已经复位" << '\n';
	}
	void OnReqContinue(uint32_t from_id)//向电机发送继续运动命令
	{
		MyADSDef ADS_OnReqContinue;
		bool req_continue = 1;
		ADS_OnReqContinue.WriteBool(from_id, 0x38, 0x1, req_continue);//7
		std::cout << "已经继续" << '\n';
	}

	void OnReqMoveProcess(uint32_t from_id, ST_DriverReqMove* req)//处理总线发过来的数据点，插值，入队进缓存
	{
		int Interpolation_Num = T_APP_Ms / T_PLC_Ms;
		double t_move = T_APP_Ms / 1000.0;
		printf("执行Move请求，m1: %f, m2: %f,m3: %f, m4: %f\n", req->m1, req->m2, req->m3, req->m4);
		ST_DriverReqMove req_pos = { 0 };
		ST_DriverReqMove vel = { 0 };
		ST_DriverReqMove acc = { 0 };
		static ST_DriverReqMove req_pos_last = { 0 };
		static ST_DriverReqMove vel_last = { 0 };
		static ST_DriverReqMove acc_last = { 0 };
		double *req_pos_resample1 = new double [Interpolation_Num];
		double *req_pos_resample2 = new double [Interpolation_Num];
		double *req_pos_resample3 = new double [Interpolation_Num];
		double *req_pos_resample4 = new double [Interpolation_Num];
		double *req_pos_resample1_flag = new double[Interpolation_Num];
		double *req_pos_resample2_flag = new double[Interpolation_Num];
		double *req_pos_resample3_flag = new double[Interpolation_Num];
		double *req_pos_resample4_flag = new double[Interpolation_Num];
		req_pos.m1 = req->m1;
		//std::cout << "+++++++++++++++++++++" << std::endl;
		//std::cout << Interpolation_Num << std::endl;
		//std::cout << "+++++++++++++++++++++" << std::endl;
		req_pos.m2 = req->m2;
		req_pos.m3 = req->m3;
		req_pos.m4 = req->m4;
		vel.m1 = (req_pos.m1 - req_pos_last.m1) / t_move;
		vel.m2 = (req_pos.m2 - req_pos_last.m2) / t_move;
		vel.m3 = (req_pos.m3 - req_pos_last.m3) / t_move;
		vel.m4 = (req_pos.m4 - req_pos_last.m4) / t_move;
		acc.m1 = (vel.m1 - vel_last.m1) / t_move;
		acc.m2 = (vel.m2 - vel_last.m2) / t_move;
		acc.m3 = (vel.m3 - vel_last.m3) / t_move;
		acc.m4 = (vel.m4 - vel_last.m4) / t_move;

		req_pos_resample1 = fifth_order_interpolation(req_pos_last.m1, req_pos.m1, vel_last.m1, vel.m1, acc_last.m1, acc.m1, 
			t_move, Interpolation_Num, req_pos_resample1);
		req_pos_resample2 = fifth_order_interpolation(req_pos_last.m2, req_pos.m2, vel_last.m2, vel.m2, acc_last.m2, acc.m2, 
			t_move, Interpolation_Num, req_pos_resample2);
		req_pos_resample3 = fifth_order_interpolation(req_pos_last.m3, req_pos.m3, vel_last.m3, vel.m3, acc_last.m3, acc.m3, 
			t_move, Interpolation_Num, req_pos_resample3);
		req_pos_resample4 = fifth_order_interpolation(req_pos_last.m4, req_pos.m4, vel_last.m4, vel.m4, acc_last.m4, acc.m4, 
			t_move, Interpolation_Num, req_pos_resample4);

		//std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << c << std::endl;
		for (int i = 0; i< Interpolation_Num; i++)
		{
			if (i == 0)
			{
				req_pos_resample1_flag[i] = 1;
				req_pos_resample2_flag[i] = 1;
				req_pos_resample3_flag[i] = 1;
				req_pos_resample4_flag[i] = 1;
			}
			else
			{
				req_pos_resample1_flag[i] = 0;
				req_pos_resample2_flag[i] = 0;
				req_pos_resample3_flag[i] = 0;
				req_pos_resample4_flag[i] = 0;
			}
			//std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << req_pos_resample3[i] << std::endl;
			mtx.lock();
			
			queue1.push(req_pos_resample1[i]);
			queue2.push(req_pos_resample2[i]);
			queue3.push(req_pos_resample3[i]);
			queue4.push(req_pos_resample4[i]);
			queue1_flag.push(req_pos_resample1_flag[i]);
			queue2_flag.push(req_pos_resample2_flag[i]);
			queue3_flag.push(req_pos_resample3_flag[i]);
			queue4_flag.push(req_pos_resample4_flag[i]);
			mtx.unlock();
		}

		delete req_pos_resample1, req_pos_resample2, req_pos_resample3, req_pos_resample4, 
			req_pos_resample1_flag, req_pos_resample2_flag, req_pos_resample3_flag, req_pos_resample4_flag;

		req_pos_last = req_pos;
		vel_last = vel;
		acc_last = acc;

	}
private:
	CCPSAPI* m_api;
};

void PositionFill()
{
	MyADSDef ADS_PositionFill;
	char szVar_Resample[] = { "MAIN.POS_REQ_Resample1.POS_Resample" };
	ST_ReqMove_Resample req_pos_resample = { 0 };
	//mtx.lock;
	double *p1, *p2, *p3, *p4, *p1_flag, *p2_flag, *p3_flag, *p4_flag;
	p1 = new double[15]; p2 = new double[15]; p3 = new double[15]; p4 = new double[15];
	p1_flag = new double[15]; p2_flag = new double[15]; p3_flag = new double[15]; p4_flag = new double[15];
	if (queue1.get_size()>15)
	{
		//std::cout << queue1.get_size()<<std::endl;
		//插值后所有点队列
		p1 = queue1.output(p1);
		p2 = queue2.output(p2);
		p3 = queue3.output(p3);
		p4 = queue4.output(p4);
		//插值后总线给定关键点flag置1，插值点为0，用于判断电机是否到达给定位置
		p1_flag = queue1_flag.output(p1_flag);
		p2_flag = queue2_flag.output(p2_flag);
		p3_flag = queue3_flag.output(p3_flag);
		p4_flag = queue4_flag.output(p4_flag);
		for (int i = 0; i < 15; i++)
		{
			req_pos_resample.p[0][i] = p1[i];
			req_pos_resample.p[1][i] = p2[i];
			req_pos_resample.p[2][i] = p3[i];
			req_pos_resample.p[3][i] = p4[i];
			req_pos_resample.p[4][i] = p1_flag[i];
			req_pos_resample.p[5][i] = p2_flag[i];
			req_pos_resample.p[6][i] = p3_flag[i];
			req_pos_resample.p[7][i] = p4_flag[i];
			std::cout << req_pos_resample.p[2][i] << std::endl;
		}
		t0 = req_pos_resample.p[0][14]; t1 = req_pos_resample.p[1][14]; t2 = req_pos_resample.p[2][14];
		t3 = req_pos_resample.p[3][14];
		delete p1; delete p2; delete p3; delete p4; delete p1_flag; delete p2_flag; delete p3_flag; delete p4_flag;
		for (int i = 0; i < 15; i++)
		{
			queue1.pop(); queue2.pop(); queue3.pop(); queue4.pop();
			queue1_flag.pop(); queue2_flag.pop(); queue3_flag.pop(); queue4_flag.pop();
		}
		ADS_PositionFill.WriteStructExpansion(szVar_Resample, sizeof(szVar_Resample), MSG_REQ_MOVE_RESAMPLE,
			(const char*)&req_pos_resample, sizeof(req_pos_resample));//向电机发送插值后的点
		//std::cout << req_pos_resample.p[1][0] << std::endl;
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			req_pos_resample.p[0][i] = t0;
			req_pos_resample.p[1][i] = t1;
			req_pos_resample.p[2][i] = t2;
			req_pos_resample.p[3][i] = t3;
			req_pos_resample.p[4][i] = t4;
			req_pos_resample.p[5][i] = t5;
			req_pos_resample.p[6][i] = t6;
			req_pos_resample.p[7][i] = t7;
		}
		ADS_PositionFill.WriteStructExpansion(szVar_Resample, sizeof(szVar_Resample), MSG_REQ_MOVE_RESAMPLE,
			(const char*)&req_pos_resample, sizeof(req_pos_resample));//向电机发送插值后的点
		std::cout << 222 << std::endl;
	}
}

void ReadFromTwincat(CCPSAPI* api)//开线程，时时读取twincat中的标志位
{
	POS_RSP POS = { 0 };
	static bool FillFlagTemp;
	static bool MoveDoneFlagTemp;
	static short IndexXTemp;
	while (1)
	{
		MyADSDef ADS_ReadFromTwincat;
		FillFlag = ADS_ReadFromTwincat.ReadBool(0x0, 0x1);//读缓存填充标志位
		//std::cout << FillFlag << std::endl;
		MoveDoneFlag = ADS_ReadFromTwincat.ReadBool(0x1, 0x1);//读运动完成标志位
		index_x = ADS_ReadFromTwincat.ReadInt(0x4, 0x2);//读PLC缓存区数组index
		//std::cout << index_x << std::endl;
		ST_ModeFlag Done_flag = {};
		if (FillFlag && (FillFlagTemp == 0))
		{
			std::cout << "装填" << '\n'; 
			std::thread th3(PositionFill);  //实例化一个线程对象th2，填充twincat缓存区
			th3.join();
		}
		if ((index_x - IndexXTemp != 0) && MoveDoneFlag)
		{
			std::cout << "Done" << MoveDoneFlag << '\n';
			Done_flag.finish_flag = 1;
			//向总线发送运动完成标志
			api->SendDeviceMsg(CONTROL_SERVER_APP_ID, MSG_MODE_FLAG, (const char*)&Done_flag, sizeof(ST_ModeFlag));
		}
		FillFlagTemp = FillFlag;
		MoveDoneFlagTemp = MoveDoneFlag;
		IndexXTemp = index_x;
	}
}
void ReadPosVel(CCPSAPI* api)//开线程，时时读取twincat中的标志位
{
	MyADSDef ADS_POS_RSP;
	MyADSDef ADS_VEL_RSP;
	POS_RSP rsp_pos;
	VEL_RSP rsp_vel;
	char szVar_pos[] = { "MAIN.POS_RSP1" };
	char szVar_vel[] = { "MAIN.VEL_RSP1" };
	while (thread2)
	{
		//读取电机位置
		ADS_POS_RSP.ReadStructExpansion(szVar_pos, sizeof(szVar_pos), MSG_RSP_MOVE_POS, (const char*)&rsp_pos, sizeof(ST_RspMove_POS));
		//读取电机速度
		ADS_POS_RSP.ReadStructExpansion(szVar_vel, sizeof(szVar_vel), MSG_RSP_MOVE_VEL, (const char*)&rsp_vel, sizeof(ST_RspMove_VEL));
		RSP_POS.ppp1 = rsp_pos.ppp1;
		RSP_POS.ppp2 = rsp_pos.ppp2;
		RSP_POS.ppp3 = rsp_pos.ppp3;
		RSP_POS.ppp4 = rsp_pos.ppp4;
		RSP_VEL.vvv1 = rsp_vel.vvv1;
		RSP_VEL.vvv2 = rsp_vel.vvv2;
		RSP_VEL.vvv3 = rsp_vel.vvv3;
		RSP_VEL.vvv4 = rsp_vel.vvv4;
		RSP_POS.info = {};
		RSP_VEL.info = {};
	}
}

int main()
{
	CCPSAPI* api = CCPSAPI::CreateAPI();
	Handler handler(api);

	if (api->Init(E_CPS_TYPE_DEVICE, MOVE_SERVER_DEV_ID, 0,
		"127.0.0.1", 5000, "127.0.0.1", 8888, &handler) != 0)//192.168.1.101
	{
		printf("API init failed.\n");
		return -1;
	}
	else
	{ }
	
	thread1 = 1;
	thread2 = 1;
	std::thread th1(ReadFromTwincat, api);  //实例化一个线程对象th1，从twincat时时读取
	std::thread th2(ReadPosVel, api);

	while (true)
	{
		MyADSDef ADS_OnReqPower;
		//bool test1 = 0;
		//test1=ADS_OnReqPower.ReadBool(0x50, 0x1);
		//bool test2 = 0;
		//test2 = ADS_OnReqPower.ReadBool(0x58, 0x2);
		//std::cout << test1 << test2 << '\n';

		int q = 0;
		std::cin >> q;
		ADS_OnReqPower.WriteBool(0x58, 0x2, q);

		if (q == 0)
		{
			break;
		}	
	}
	
	// exit
	th1.join();
	th2.join();
	api->Release();
	return 0;
}
