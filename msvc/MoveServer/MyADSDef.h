#pragma once
#include <iostream>
#include <conio.h> //����̨�������ͷ�ļ�
#include <windows.h> //windowsAPI�ĺ��������ͺ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h" //�ṹ��ͳ���������
#include "E:\Program Files\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h" // ADS����������
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
	long nErr, nPort; //����˿ڱ���
	AmsAddr Addr; //����AMS��ַ����
	PAmsAddr pAddr = &Addr; //����˿ڵ�ַ����
	ST_MsgRsp msg_rsp;
	unsigned long lHdlVar;
	unsigned long pcbReturn;
	unsigned long indexOffset;
	unsigned long length;

public:

	MyADSDef();//ADSͨѶ���캯��
	~MyADSDef();//ADSͨѶ��������

	bool ReadBool(unsigned long indexOffset, unsigned long length);//��ȡboolֵ
	short ReadInt(unsigned long indexOffset, unsigned long length);//��ȡintֵ
	float ReadFloat(unsigned long indexOffset, unsigned long length);//��ȡfloatֵ
	ST_ReqMove ReadStruct(char var[], int N, ST_ReqMove *req);
	void ReadStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//��ȡ�ṹ��

	void WriteBool(unsigned long indexOffset, unsigned long length, bool data);//д��boolֵ
	void WriteInt(unsigned long indexOffset, unsigned long length, short data);//д��intֵ
	void WriteFloat(unsigned long indexOffset, unsigned long length, float data);//д��floatֵ
	void WriteStruct(char var[], int N, ST_ReqMove *req);
	void WriteStructExpansion(char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//д��ṹ��

	bool ReadBool(uint32_t from_id, unsigned long indexOffset, unsigned long length);//��ȡboolֵ
	short ReadInt(uint32_t from_id, unsigned long indexOffset, unsigned long length);//��ȡintֵ
	float ReadFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length);//��ȡfloatֵ
	ST_ReqMove ReadStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req);
	void ReadStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//��ȡ�ṹ��

	void WriteBool(uint32_t from_id, unsigned long indexOffset, unsigned long length, bool data);//д��boolֵ
	void WriteInt(uint32_t from_id, unsigned long indexOffset, unsigned long length, short data);//д��intֵ
	void WriteFloat(uint32_t from_id, unsigned long indexOffset, unsigned long length, float data);//д��floatֵ
	void WriteStruct(uint32_t from_id, char var[], int N, ST_ReqMove *req);
	void WriteStructExpansion(uint32_t from_id, char var[], int N, uint32_t msg_type, const char* data, uint32_t msg_len);//д��ṹ��

};

#endif /* MyADSDef_hpp */
