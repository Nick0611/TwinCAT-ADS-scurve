#pragma once
#include <CPSAPI/CPSAPI.h>
#include <CPSAPI/CPSDef.h>
#include "ParallelControlUI.h"

class Handler : public CCPSEventHandler
{
public:
	Handler(CCPSAPI* api, ParallelControlUI* ui) :m_api(api), m_main_ui(ui)
	{}
	// Connect event
	virtual void OnConnected()
	{
		m_api->SubscribeDevice(MOVE_SERVER_DEV_ID);

		printf("OnConnected\n");
		emit m_main_ui->SginalOnConnected();
	}
	// Disconnect event
	virtual void OnDisconnected()
	{
		printf("OnDisconnected\n");
		emit m_main_ui->SginalOnDisconnected();
	}
	// Message event
	virtual void OnMsg(uint32_t from_id, uint32_t msg_type, const char* data, uint32_t msg_len)
	{
		switch (msg_type)
		{
		case MSG_RSP_MOVE_POS:
			this->OnRspMovePos(from_id, (ST_RspMove_POS*)data);
		case MSG_RSP_MOVE_VEL:
			this->OnRspMoveVel(from_id, (ST_RspMove_VEL*)data);
		default:
			break;
		}
	}

	void OnRspMovePos(uint32_t from_id, ST_RspMove_POS* rsp)
	{
		emit m_main_ui->SignalOnRspMovePos(rsp);
	}
	void OnRspMoveVel(uint32_t from_id, ST_RspMove_VEL* rsp)
	{
		emit m_main_ui->SignalOnRspMoveVel(rsp);
	}
private:
	CCPSAPI* m_api = nullptr;
	ParallelControlUI* m_main_ui = nullptr;
};