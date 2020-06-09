#pragma once
#include <iostream>
#include <conio.h> //控制台输入输出头文件
#include <windows.h> //windowsAPI的函数声明和宏
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h" //结构体和常量的声明
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h" // ADS函数的声明
#include <CPSAPI/CPSDef.h>
#include <CPSAPI/CPSAPI.h>
#include <string>
#include <cstring> 
#include "include.h"

#ifndef MyADSDef_hpp
#define MyADSDef_hpp

//template <typename T>

class BASE
{
public:
	virtual void WriteTest(const char* data, uint32_t msg_len) {};
};

class MyADSDef
{
private:
	//T *m_pArr;
	CCPSAPI* m_api;
	long nErr, nPort; //定义端口变量
	AmsAddr Addr; //定义AMS地址变量
	PAmsAddr pAddr = &Addr; //定义端口地址变量
	ST_MsgRsp msg_rsp;
	unsigned long lHdlVar;
	unsigned long pcbReturn;
	unsigned long indexOffset;
	unsigned long length;

public:

	MyADSDef();//ADS通讯构造函数
	~MyADSDef();//ADS通讯析构函数

	bool ReadBool(unsigned long indexOffset, unsigned long length);//读取bool值
	short ReadInt(unsigned long indexOffset, unsigned long length);//读取int值
	float ReadFloat(unsigned long indexOffset, unsigned long length);//读取float值
	ST_ReqMove ReadStruct(char var[], int N, ST_ReqMove *req);
	void ReadStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//读取结构体

	void WriteBool(unsigned long indexOffset, unsigned long length, bool data);//写入bool值
	void WriteInt(unsigned long indexOffset, unsigned long length, short data);//写入int值
	void WriteFloat(unsigned long indexOffset, unsigned long length, float data);//写入float值
	void WriteStruct(char var[], int N, ST_ReqMove *req);
	void WriteStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//写入结构体

	bool ReadBool(uint32_t from_id, unsigned long indexOffset, unsigned long length);//读取bool值
	short ReadInt(uint32_t from_id, unsigned long indexOffset, unsigned long length);//读取int值
	float ReadFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length);//读取float值
	ST_ReqMove ReadStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req);
	void ReadStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//读取结构体

	void WriteBool(uint32_t from_id, unsigned long indexOffset, unsigned long length, bool data);//写入bool值
	void WriteInt(uint32_t from_id, unsigned long indexOffset, unsigned long length, short data);//写入int值
	void WriteFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length, float data);//写入float值
	void WriteStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req);
	void WriteStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//写入结构体

};

#endif /* MyADSDef_hpp */
