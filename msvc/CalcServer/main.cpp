#include <CPSAPI/CPSAPI.h>
#include <CPSAPI/CPSDef.h>
#include <stdio.h>
#include <iostream>

class Handler: public CCPSEventHandler
{
public:
	Handler(CCPSAPI * api):m_api(api)
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
		case MSG_REQ_CALC_SUM:
			this->OnReqCalcSum(from_id, (ST_ReqCalcSum*)data);
		default:
			break;
		}
	}

	void OnReqCalcSum(uint32_t from_id, ST_ReqCalcSum* req)
	{
		printf("收到计算请求，x: %f, y: %f\n", req->x, req->y);
		ST_RspCalcSum rsp = { 0 };
		rsp.info.error_code = 0;

		rsp.sum = req->x + req->y;

		m_api->SendDeviceMsg(from_id, MSG_RSP_CALC_SUM, (const char*)&rsp, sizeof(ST_RspCalcSum));
		printf("发送计算结果，sum: %f\n", rsp.sum);
	}
private:
	CCPSAPI* m_api;
};

int main()
{
	CCPSAPI* api = CCPSAPI::CreateAPI();
	Handler handler(api);

	if (api->Init(E_CPS_TYPE_DEVICE, CALC_SERVER_DEV_ID, 0,
		"116.232.13.15", 64000, "116.232.13.15", 64888, &handler) != 0)
	{
		printf("API init failed.\n");
		return -1;
	}

	while (true)
	{
		int q = 0;
		std::cin >> q;

		if (q == 0)
		{
			break;
		}
	}

	// exit
	api->Release();
	return 0;
}