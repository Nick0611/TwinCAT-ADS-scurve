#include "MyADSDef.h"

MyADSDef::MyADSDef()
{
	nPort = AdsPortOpenEx(); //打开ADS通讯端口
	//nErr = AdsGetLocalAddressEx(nPort, pAddr); //自动获取本地地址
	//if (nErr) std::cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';
	pAddr->port = AMSPORT_R0_PLC_TC3; //TC3的通讯端口为851
	pAddr->netId.b[0] = 5; //手动填写目标设备的AMSNETID
	pAddr->netId.b[1] = 57; //在我们例子中设备通讯AMSNETID为5.23.20.78.1.1
	pAddr->netId.b[2] = 226;
	pAddr->netId.b[3] = 116;
	pAddr->netId.b[4] = 1;	
	pAddr->netId.b[5] = 1;
}

MyADSDef::~MyADSDef()
{
	nErr = AdsPortCloseEx(nPort); //关闭ADS通讯端口
	if (nErr) std::cerr << "Error: AdsPortClose: " << nErr << '\n'; //检查关闭通讯端口的操作是否执行成功
}

bool MyADSDef::ReadBool(unsigned long indexOffset, unsigned long length)
{

	bool data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4021, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncReadBoolReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
	}
	return data;
}

short MyADSDef::ReadInt(unsigned long indexOffset, unsigned long length)
{
	short data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4020, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncReadIntReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
	}
	return data;
}

float MyADSDef::ReadFloat(unsigned long indexOffset, unsigned long length)
{
	float data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4020, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncReadFloatReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
	}
	return data;
}

ST_ReqMove MyADSDef::ReadStruct(char var[], int N, ST_ReqMove *req)
{
	ST_ReqMove reqq = *req;
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
	}
	nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(reqq), &reqq, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
	}
	//std::cout << reqq.m1 << std::endl;
	delete[]vars;
	return reqq;
}

void MyADSDef::ReadStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len)
{
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
	}
	switch (msg_type)
	{
	case MSG_RSP_MOVE_POS:
	{
		POS_RSP rsp = { 0 };
		nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(rsp), &rsp, &pcbReturn);
		if (nErr)
		{
			std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
		}
		*(POS_RSP*)data = rsp;
		break;
	}
	case MSG_RSP_MOVE_VEL:
	{
		VEL_RSP rsp = { 0 };
		nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(rsp), &rsp, &pcbReturn);
		if (nErr)
		{
			std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
		}
		*(VEL_RSP*)data = rsp;
		break;
	}

	default:
	{
		std::cout << "which struct to be read?" << std::endl;
		break;
	}
	}
	delete[]vars;
}

void MyADSDef::WriteBool(unsigned long indexOffset, unsigned long length, bool data)
{
	bool rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4021, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteBoolReq: " << nErr << '\n';//检查获取地址的操作是否执行成功
	}
}

void MyADSDef::WriteInt(unsigned long indexOffset, unsigned long length, short data)
{
	short rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4020, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteIntReq: " << nErr << '\n';//检查获取地址的操作是否执行成功
	}
}

void MyADSDef::WriteFloat(unsigned long indexOffset, unsigned long length, float data)
{
	float rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4020, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteFloatReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
	}
}

void MyADSDef::WriteStruct(char var[], int N, ST_ReqMove *req)
{
	ST_ReqMove reqq = *req;
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
	}
	nErr = AdsSyncWriteReqEx(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(reqq), &reqq);
	if (nErr)
	{
		std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
	}
	//std::cout << reqq.m1 << std::endl;
	delete[]vars;
}

void MyADSDef::WriteStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len)
{
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
	}

	ST_ReqMove_Resample req = *(ST_ReqMove_Resample*)data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(req), &req);
	if (nErr)
	{
		std::cerr << "Error: Ads: write struct: " << nErr << '\n';
	}
	delete[]vars;
}



bool MyADSDef::ReadBool(uint32_t from_id, unsigned long indexOffset, unsigned long length)
{

	bool data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4021, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{	
		std::cerr << "Error: AdsSyncReadBoolReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncReadBoolReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}	
	return data;
}

short MyADSDef::ReadInt(uint32_t from_id, unsigned long indexOffset, unsigned long length)
{
	short data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4020, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncReadIntReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncReadIntReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}	
	return data;
}

float MyADSDef::ReadFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length)
{
	float data;
	nErr = AdsSyncReadReqEx2(nPort, pAddr, 0x4020, indexOffset, length, &data, &pcbReturn); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncReadFloatReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncReadFloatReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	return data;
}

ST_ReqMove MyADSDef::ReadStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req)
{
	ST_ReqMove reqq = *req;
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncReadWriteReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(reqq), &reqq, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: Ads: Read rsp_pos struct: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	//std::cout << reqq.m1 << std::endl;
	delete[]vars;
	return reqq;
}

void MyADSDef::ReadStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len)
{
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Test:Error: AdsSyncReadWriteReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	switch (msg_type)
	{
	case MSG_RSP_MOVE_POS:
	{
		POS_RSP rsp = { 0 };
		nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(rsp), &rsp, &pcbReturn);
		if (nErr)
		{
			std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
			msg_rsp.error_code = nErr;
			std::string error_msg = "Error: Ads: Read rsp_pos struct: " + std::to_string(nErr);
			char* p = const_cast<char*>(error_msg.c_str());
			strcpy_s(msg_rsp.error_msg, p);
			m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
		}
		*(POS_RSP*)data = rsp;
		break;
	}
	case MSG_RSP_MOVE_VEL:
	{
		VEL_RSP rsp = { 0 };
		nErr = AdsSyncReadReqEx2(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(rsp), &rsp, &pcbReturn);
		if (nErr)
		{
			std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
			msg_rsp.error_code = nErr;
			std::string error_msg = "Error: Ads: Read rsp_pos struct: " + std::to_string(nErr);
			char* p = const_cast<char*>(error_msg.c_str());
			strcpy_s(msg_rsp.error_msg, p);
			m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
		}
		*(VEL_RSP*)data = rsp;
		break;
	}
	
	default:
	{
		std::cout << "which struct to be read?" << std::endl;
		break;
	}
	}
	delete[]vars;
}

void MyADSDef::WriteBool(uint32_t from_id, unsigned long indexOffset, unsigned long length, bool data)
{
	bool rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4021, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteBoolReq: " << nErr << '\n';//检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncWriteBoolReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
}

void MyADSDef::WriteInt(uint32_t from_id, unsigned long indexOffset, unsigned long length, short data)
{
	short rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4020, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteIntReq: " << nErr << '\n';//检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncWriteIntReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
}

void MyADSDef::WriteFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length, float data)
{
	float rec = data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, 0x4020, indexOffset, length, &rec); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，&BOOL1:接收数据的缓存
	if (nErr)
	{
		std::cerr << "Error: AdsSyncWriteFloatReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: AdsSyncWriteFloatReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
}

void MyADSDef::WriteStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req)
{
	ST_ReqMove reqq = *req;
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Test:Error: AdsSyncReadWriteReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	nErr = AdsSyncWriteReqEx(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(reqq), &reqq);
	if (nErr)
	{
		std::cerr << "Error: Ads: Read rsp_pos struct: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: Ads: Read rsp_pos struct: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	//std::cout << reqq.m1 << std::endl;
	delete[]vars;
}

void MyADSDef::WriteStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len)
{
	char *vars = new char[N];
	for (int i = 0; i < N; i++)
	{
		vars[i] = var[i];
	}
	nErr = AdsSyncReadWriteReqEx2(nPort, pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, strlen(vars) + 1, vars, &pcbReturn);
	if (nErr)
	{
		std::cerr << "Test:Error: AdsSyncReadWriteReq: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Test:Error: AdsSyncReadWriteReq: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}

	ST_ReqMove_Resample req = *(ST_ReqMove_Resample*)data;
	nErr = AdsSyncWriteReqEx(nPort, pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(req), &req);
	if (nErr)
	{
		std::cerr << "Error: Ads: write struct: " << nErr << '\n';
		msg_rsp.error_code = nErr;
		std::string error_msg = "Error: Ads: write struct: " + std::to_string(nErr);
		char* p = const_cast<char*>(error_msg.c_str());
		strcpy_s(msg_rsp.error_msg, p);
		m_api->SendDeviceMsg(from_id, MSG_RSP_MOVE_POS, (const char*)&msg_rsp, sizeof(msg_rsp));
	}
	delete[]vars;
}


