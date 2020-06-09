#pragma once
#include <QtWidgets/QDialog>
#include "ui_ParallelControlUI.h"
#include <CPSAPI/CPSAPI.h>
#include <CPSAPI/CPSDef.h>

class Handler;

class ParallelControlUI : public QDialog
{
	Q_OBJECT

public:
	ParallelControlUI(QWidget *parent = Q_NULLPTR);

	void Init();

public slots:
	void slot_btn_calc_click();
	void slot_on_connected();
	void slot_on_disconnected();
	void slot_on_rsp_move_pos(ST_RspMove_POS* rsp);
	void slot_on_rsp_move_vel(ST_RspMove_VEL* rsp);
signals:
	void SginalOnConnected();
	void SginalOnDisconnected();
	void SignalOnRspMovePos(ST_RspMove_POS* rsp);
	void SignalOnRspMoveVel(ST_RspMove_VEL* rsp);
protected:
	virtual void closeEvent(QCloseEvent* event);
protected:
	CCPSAPI* m_api = nullptr;
	Handler* m_handler = nullptr;
private:
	Ui::ParallelControlUIClass ui;
};
