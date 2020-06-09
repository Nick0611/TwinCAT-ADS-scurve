#pragma once

#if defined _WIN32
#   if defined CPS_API_STATIC
#       define CPS_API_EXPORT
#   elif defined CPS_API_DLL
#       define CPS_API_EXPORT __declspec(dllexport)
#   else
#       define CPS_API_EXPORT __declspec(dllimport)
#   endif
#else
#   define CPS_API_EXPORT
#endif

#include <stdint.h>

// CPSAPI type
enum E_CPS_TYPE
{
	E_CPS_TYPE_DEVICE = 0x1,
	E_CPS_TYPE_APP = 0x2,
	E_CPS_TYPE_MIX = E_CPS_TYPE_DEVICE | E_CPS_TYPE_APP
};


class CCPSEventHandler
{
public: // interfaces
	// Connect event
	virtual void OnConnected() {};
	// Disconnect event
	virtual void OnDisconnected() {};
	// Message event
	virtual void OnMsg(uint32_t from_id, uint32_t msg_type, const char* data, uint32_t msg_len) {};
};

/*
	Note:
	1. API Users are classcified into two type, Device and APP
	2. Device should not use methods designed for APP, vice versa.
	3. Device can send msg to specified APP which subscribe this device
	4. Device can broadcast msg to all apps which subscribe this device
	5. Device can not send msg to another device
	6. APP can send msg to specified device which itself subscribes
	7. APP can not send msg to APP, if this is necessary, use mixed types
	About mixed types:
	1. If the preceding rules does not meet your needs, this api can also support mixed type
	2. Mixed type should call both functions: RegisterDevice & RegisterAPP 
	3. At this time, all the rules can be used for mixed type
*/
class CPS_API_EXPORT CCPSAPI
{
public:
	// Create API Instance
	static CCPSAPI* CreateAPI();
	// Get API Version Info
	static const char* GetApiVersion();

	// Api init
	// for E_CPS_TYPE_DEVICE, dev_id is used
	// for E_CPS_TYPE_APP, app_id is used
	// for E_CPS_TYPE_MIX, both dev_id and app_id are used
	// Note: device id are not arbitray, please ask your admin for your device id
	// APP id should be in range [0x1001, 0x2000], and should be unique in the whole system
	virtual int Init(E_CPS_TYPE api_type, uint32_t dev_id, uint32_t app_id,
		const char* server_ip, int server_port,
		const char* log_ip, int log_port,
		CCPSEventHandler* handler) = 0;

	// Release api
	virtual void Release() = 0;

	///////////////////////////////////////////////////////////////////////
	// These methods are used by device, should be called after connection established
	// Register Device. 
	virtual int RegisterDevice() = 0;
	// UnRegister Device
	virtual int UnregisterDevice() = 0;
	// Send Message as Device. If app_id is -1, send becomes broadcast
	virtual int SendDeviceMsg(int app_id, uint32_t msg_type, const char* data, uint32_t msg_len) = 0;
	///////////////////////////////////////////////////////////////////////
	// These methods are used by APP, should be called after connection established
	// Subscribe Device
	virtual int SubscribeDevice(uint32_t device_id) = 0;
	// Unsubscribe Device
	virtual int UnSubscribeDevice(uint32_t device_id) = 0;
	// Send Message as APP
	virtual int SendAPPMsg(uint32_t device_id, uint32_t msg_type, const char* data, uint32_t msg_len) = 0;
};

