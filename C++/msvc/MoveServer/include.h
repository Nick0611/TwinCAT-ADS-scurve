#pragma once

#define	MSG_REQ_MOVE_RESAMPLE			0x609
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

#define T_PLC_Ms 20
#define T_APP_Ms 1000
