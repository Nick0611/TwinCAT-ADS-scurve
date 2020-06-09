#include "ParallelControlUI.h"
#include "MyHandler.h"

ParallelControlUI::ParallelControlUI(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Init();
}

void ParallelControlUI::Init()
{
	ui.btn_calc->setEnabled(false);
	ui.btn_calc->setText(QString::fromLocal8Bit("总线未连接..."));

	connect(this, SIGNAL(SginalOnConnected()), this, SLOT(slot_on_connected()));
	connect(this, SIGNAL(SginalOnDisconnected()), this, SLOT(slot_on_disconnected()));
	connect(this, SIGNAL(SignalOnRspMovePos(ST_RspMove_POS*)),
		this, SLOT(slot_on_rsp_move_pos(ST_RspMove_POS*)),
		Qt::BlockingQueuedConnection);
	connect(this, SIGNAL(SignalOnRspMoveVel(ST_RspMove_VEL*)),
		this, SLOT(slot_on_rsp_move_vel(ST_RspMove_VEL*)),
		Qt::BlockingQueuedConnection);

	connect(ui.btn_calc, SIGNAL(clicked()), this, SLOT(slot_btn_calc_click()));

	m_api = CCPSAPI::CreateAPI();
	m_handler = new Handler(m_api, this);

	if (m_api->Init(E_CPS_TYPE_APP, 0, CONTROL_SERVER_APP_ID,
		"127.0.0.1", 5000, "127.0.0.1", 8888, m_handler) != 0)
	{
		printf("API init failed.\n");
	}
}

void ParallelControlUI::closeEvent(QCloseEvent* event)
{
	if (m_api)
	{
		m_api->Release();
		m_api = nullptr;
	}
	if (m_handler)
	{
		delete m_handler;
		m_handler = nullptr;
	}

	QDialog::closeEvent(event);
}

void ParallelControlUI::slot_btn_calc_click()
{
	ST_ReqMove req = { 0 };
	req.m1 = ui.spin_x->value();
	req.m2 = ui.spin_y->value();
	req.m3 = ui.spin_x_2->value();
	req.m4 = ui.spin_y_2->value();

	m_api->SendAPPMsg(MOVE_SERVER_DEV_ID, MSG_REQ_MOVE, (const char*)&req, sizeof(ST_ReqMove));

	ui.btn_calc->setEnabled(false);
	ui.btn_calc->setText(QString::fromLocal8Bit("计算请求已发送"));
}


void ParallelControlUI::slot_on_connected()
{
	ui.btn_calc->setEnabled(true);
	ui.btn_calc->setText(QString::fromLocal8Bit("请求计算"));
}

void ParallelControlUI::slot_on_disconnected()
{
	ui.btn_calc->setEnabled(false);
	ui.btn_calc->setText(QString::fromLocal8Bit("总线未连接..."));
}

void ParallelControlUI::slot_on_rsp_move_pos(ST_RspMove_POS* rsp)
{
	if (rsp->info.error_code == 0)
	{
		ui.label_sum->setText(QString::number(rsp->ppp1));
		ui.label_sum_2->setText(QString::number(rsp->ppp2));
		ui.label_sum_3->setText(QString::number(rsp->ppp3));
		ui.label_sum_4->setText(QString::number(rsp->ppp4));
	}
	else
	{
		ui.label_sum->setText(QString("error: "));
		ui.label_sum_2->setText(QString("error: "));
		ui.label_sum_3->setText(QString("error: "));
		ui.label_sum_4->setText(QString("error: "));
	}
	ui.btn_calc->setEnabled(true);
	ui.btn_calc->setText(QString::fromLocal8Bit("计算请求"));
}

void ParallelControlUI::slot_on_rsp_move_vel(ST_RspMove_VEL* rsp)
{
	if (rsp->info.error_code == 0)
	{
		ui.label_sum_5->setText(QString::number(rsp->vvv1));
		ui.label_sum_6->setText(QString::number(rsp->vvv2));
		ui.label_sum_7->setText(QString::number(rsp->vvv3));
		ui.label_sum_8->setText(QString::number(rsp->vvv4));
	}
	else
	{
		ui.label_sum_5->setText(QString("error: "));
		ui.label_sum_6->setText(QString("error: "));
		ui.label_sum_7->setText(QString("error: "));
		ui.label_sum_8->setText(QString("error: "));
	}
}
