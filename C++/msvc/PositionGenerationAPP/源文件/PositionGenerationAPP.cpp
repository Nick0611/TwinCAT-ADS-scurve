// PositionGenerationAPP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <CPSAPI/CPSAPI.h>
#include <CPSAPI/CPSDef.h>
#include <stdio.h>
#include <iostream>
#include <string> 
#include <conio.h> //控制台输入输出头文件
#include <windows.h> //windowsAPI的函数声明和宏
#include <time.h>
#include <winbase.h> //windows 头文件之一
#include <chrono>
#include <thread>
#include <random>
#include <iomanip> //要用到格式控制符
#include <fstream>
#include <vector> 
#include <sstream>


typedef struct
{
	double p[8][15];
	//int t;
}ST_ReqMove_Resample;

typedef struct
{
	double ppp1;
	double ppp2;
	double ppp3;
	double ppp4;
}POS_RSP;

typedef struct
{
	double vvv1;
	double vvv2;
	double vvv3;
	double vvv4;
}VEL_RSP;

typedef struct
{
	double m1;
	double m2;
	double m3;
	double m4;
}ST_ReqMove;

typedef struct
{
	int flag;
}ST_ReqFlag;


#define Rsp_MoveDone 0
#define Rsp_Power 1
#define Rsp_Init 2
#define Rsp_MoveStop 3
#define Rsp_NoPower 4
#define Rsp_Reset 5
#define Rsp_Continue 6
#define Rsp_GetMoveReq 7
#define Rsp_SwitchMode 8
#define Rsp_GetVel 9
#define Rsp_Start 10
#define Rsp_Set0 11


#define Req_Power 1
#define Req_Init 2
#define Req_MoveStop 3
#define Req_NoPower 4
#define Req_Reset 5
#define Req_Continue 6
#define Req_Start 7
#define Req_Set0 8

#define T_PLC_Ms 200
#define T_APP_Ms 1000


class Handler : public CCPSEventHandler
{
public:
	Handler(CCPSAPI * api) :m_api(api)
	{}

	// Connect event
	virtual void OnConnected()
	{
		m_api->SubscribeDevice(MOVE_SERVER_DEV_ID);
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
		//switch (msg_type)
		//{
		//case MSG_RSP_FLAG:
		//	this->OnRspFlag(from_id, (ST_RspFlag*)data);
		//	break;
		//default:
		//	break;
		//}
	}

	/*void OnRspFlag(uint32_t from_id, ST_RspFlag* rsp)
	{
		if (rsp->flag == Rsp_MoveDone)
			std::cout << "Move Done " << '\n';
		if (rsp->flag == Rsp_Power)
			std::cout << "Rsp_Power Done " << '\n';
		if (rsp->flag == Rsp_Init)
			std::cout << "Rsp_Init Done " << '\n';
		if (rsp->flag == Rsp_MoveStop)
			std::cout << "Rsp_MoveStop Done " << '\n';
		if (rsp->flag == Rsp_NoPower)
			std::cout << "Rsp_NoPower Done " << '\n';
		if (rsp->flag == Rsp_Reset)
			std::cout << "Rsp_Reset Done " << '\n';
		if (rsp->flag == Rsp_Continue)
			std::cout << "Rsp_Continue Done " << '\n';
		if (rsp->flag == Rsp_SwitchMode)
			std::cout << "Rsp_SwitchMode Done " << '\n';
		if (rsp->flag == Rsp_GetVel)
			std::cout << "Rsp_GetVel Done " << '\n';
	}*/
private:
	CCPSAPI* m_api;
};

void SendPosition(CCPSAPI* api)
{
	ST_ReqMove req = { 0 };
	float t = 1;
	while (1)
	{
		auto start = std::chrono::steady_clock::now();
		std::random_device rd;
		std::default_random_engine e(rd());
		std::uniform_real_distribution<double> u(0, 1);
		double noise = u(e);
		noise = 0;
		//std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3) << u(e) << std::endl;
		req.m1 = 360 * sin(3 * t*3.1415926 / 180.0) + 10 * noise;
		//req.m1 = 30*sin(2 * t*3.1415926 / 180.0);
		req.m2 = 360 * sin(3 * t*3.1415926 / 180.0) + 10 * noise;
		req.m3 = 360 * sin(3 * t*3.1415926 / 180.0) + 10 * noise;
		req.m4 = 360 * sin(3 * t*3.1415926 / 180.0) + 10 * noise;
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> elapsed = end - start; // std::micro 表示以微秒为时间单位
		while (elapsed.count() < 100000)
		{
			end = std::chrono::steady_clock::now();
			elapsed = end - start; // std::micro 表示以微秒为时间单位
		}
		t += 1;

		api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_REQ_MOVE, (const char*)&req, sizeof(req));

		//std::cout << "time: " << elapsed.count() << "us" << std::endl;
		//std::cout << req.m1 << "," << req.m2 << "," << req.m3 << "," << req.m4 << std::endl;
	}
}

void  readxls()
{
	std::ifstream inFile("four_motor_test_data.csv", std::ios::in);
	std::string lineStr;
	std::vector<std::vector<std::string>> strArray;
	int i, j;
	i = 0;
	double array[31][4] = {};
	if (inFile.fail())
		std::cout << "读取文件失败" << std::endl;
	while (getline(inFile, lineStr))
	{
		j = 0;
		// 存成二维表结构  
		std::stringstream ss(lineStr);
		std::string str;
		std::vector<std::string> lineArray;
		// 按照逗号分隔  
		while (getline(ss, str, ','))
		{
			array[i][j] =atof(str.c_str());              //string -> int
			j++;
		}
		i++;
		//     strArray.push_back(lineArray);  
	}
	//for (int i = 0; i < 31; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//		std::cout << array[i][j]<<" ";
	//	std::cout << std::endl;
	//}
}

	/*for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << array[i][j];
		std::cout << std::endl;
	}*/
	//std::string value;
	////char filename[256];
	//std::string filename = "four_motor_test_data.csv";
	//std::ifstream infile(filename);
	//while (infile.good()) {
	//	//.csv文件用","作为分隔符
	//	getline(infile, value, ',');
	//	std::cout << value << std::endl;
	//}
	//std::string filename = "four_motor_test_data.csv";
	//std::ifstream fin(filename.c_str());//以输入方式打开文件存到缓冲空间fin中
	//std::string line;
	//int i = 0;
	//int comma = 0;
	//float A[124] = {};
	//while (getline(fin, line))//读取fin中的整行字符存在line中
	//{
	//	int comma = line.find(',', 0);
	//	A[i] = atof(line.substr(comma + 1, line.length() - comma - 1).c_str());
	//	//将line中的相应位置的字符串转换成float类型放在数组中
	//	i++;
	//	std::cout << A[i] << std::endl;
	//}
	

int main()
{
	CCPSAPI* api = CCPSAPI::CreateAPI();
	Handler handler(api);
	int i;
	int mode_flag;
	ST_ReqFlag req_flag = { 0 };

	std::ifstream inFile("four_motor_test_data.csv", std::ios::in);
	std::string lineStr;
	std::vector<std::vector<std::string>> strArray;
	int ii, j;
	ii = 0;
	double array[41][4] = {};
	if (inFile.fail())
		std::cout << "读取文件失败" << std::endl;
	while (getline(inFile, lineStr))
	{
		j = 0;
		// 存成二维表结构  
		std::stringstream ss(lineStr);
		std::string str;
		std::vector<std::string> lineArray;
		// 按照逗号分隔  
		while (getline(ss, str, ','))
		{
			array[ii][j] = atof(str.c_str());              //string -> int
			j++;
		}
		ii++;
		//     strArray.push_back(lineArray);  
	}

	if (api->Init(E_CPS_TYPE_APP, 0, GENERATION_SERVER_APP_ID,
		"127.0.0.1", 5000, "127.0.0.1", 8888, &handler) != 0)
	/*if (api->Init(E_CPS_TYPE_APP, 0, GENERATION_SERVER_APP_ID,
		"116.232.13.15", 64000, "116.232.13.15", 64888, &handler) != 0)*/
	{
		printf("API init failed.\n");
		return -1;
	}
	else
	{
	}

	//for (int i = 0; i < ii; i++)
	//{
	//	ST_ReqMove req = { 0 };
	//	req.m1 = array[i][0];
	//	req.m2 = array[i][1];
	//	req.m3 = array[i][2];
	//	req.m4 = array[i][3];
	//	api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_REQ_MOVE, (const char*)&req, sizeof(req));
	//}

	ST_DriverReqMove req = { 0 };

	//std::thread th1(SendPosition, api);  //实例化一个线程对象th1，从twincat时时读取
	while (1)
	{
		req.req_id++;
		std::cin >> req.m1 >> req.m2 >> req.m3 >> req.m4;
		api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_REQ_MOVE, (const char*)&req, sizeof(req));
			/*std::cout << std::endl;
			std::cout << "===========================" << std::endl;
			std::cout << "可输入:" << std::endl;
			std::cout << "Req_Init:" << Req_Init << std::endl;
			std::cout << "Req_MoveStop:" << Req_MoveStop << std::endl;
			std::cout << "Req_Reset:" << Req_Reset << std::endl;
			std::cout << "Req_Continue:" << Req_Continue << std::endl;
			std::cout << "---------------------" << std::endl;

			std::cin >> i;
			if (i == Req_Init)
			{
				api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_CMD_INIT, (const char*)&req_flag, sizeof(req_flag));
				std::cout << "Req_Init" << std::endl;
			}
			if (i == Req_MoveStop)
			{
				api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_CMD_STOP, (const char*)&req_flag, sizeof(req_flag));
				std::cout << "Req_MoveStop" << std::endl;
			}

			if (i == Req_Reset)
			{
				api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_CMD_RESET, (const char*)&req_flag, sizeof(req_flag));
				std::cout << "Req_Reset" << std::endl;
			}
			if (i == Req_Continue)
			{
				api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_CMD_CONTINUE, (const char*)&req_flag, sizeof(req_flag));
				std::cout << "Req_Continue" << std::endl;
			}

			std::cout << "===========================" << std::endl;*/
	}

	// exit
	//th1.join();
	api->Release();
	return 0;
}


