#pragma once
#include <stdint.h>

#define CONTROL_SERVER_APP_ID		0x1001
#define GENERATION_SERVER_APP_ID		0x1002

#define MOVE_SERVER_DEV_ID			0x302


#pragma pack(push, 4)

// 初始化消息
#define MSG_CMD_INIT				0x501

// 错误消息
#define MSG_RSP_INFO				0x500
typedef struct
{
	int		error_code;
	char	error_msg[128];
}ST_MsgRsp;

typedef struct
{
	int req_no;
}ST_CMDInit;

// 初始化消息应答
#define MSG_CMD_INIT_RSP			0x502
typedef struct
{
	int req_no;
	ST_MsgRsp rsp;
}ST_CMDInitRsp;

// 停止消息
#define MSG_CMD_STOP				0x503
typedef struct
{
	int req_no;
}ST_CMDStop;

// 停止消息应答
#define MSG_CMD_STOP_RSP			0x504
typedef struct
{
	int req_no;
	ST_MsgRsp rsp;
}ST_CMDStopRsp;

// Reset请求
#define MSG_CMD_RESET				0x505
typedef struct
{
	int req_no;
}ST_CMDReset;

// Reset请求
#define MSG_CMD_CONTINUE				0x506
typedef struct
{
	int req_no;
}ST_CMDContinue;

////////////////////////////////消息定义////////////////////////////////////////

// Move请求
#define	MSG_REQ_MOVE				0x801
typedef struct
{
	int req_id;
	double m1;
	double m2;
	double m3;
	double m4;
}ST_DriverReqMove;

// Move POS: 持续推送
#define	MSG_RSP_MOVE_POS			0x802
typedef struct
{
	int req_id;
	ST_MsgRsp		info;
	double ppp1;
	double ppp2;
	double ppp3;
	double ppp4;
}ST_RspMove_POS;


// Move VEL应答：暂时不需要
#define	MSG_RSP_MOVE_VEL			0x803
typedef struct
{
	ST_MsgRsp		info;
	double vvv1;
	double vvv2;
	double vvv3;
	double vvv4;
}ST_RspMove_VEL;

#define	MSG_MODE_FLAG				0x804
typedef struct
{
	int finish_flag; // 运动请求标志：0表示未完成，1表示完成
}ST_ModeFlag;

#pragma pack(pop)

