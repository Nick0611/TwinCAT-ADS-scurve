#include "fifth_order_interpolation.h"

double* fifth_order_interpolation(double pos_last, double pos, double vel_last, double vel, double acc_last, double acc, double t_move, int Interpolation_Num, double *req_pos_resample)
{
	fifth_coefficient factor = { 0 };
	factor.a0 = pos_last;
	factor.a1 = vel_last;
	factor.a2 = acc_last / 2;
	factor.a3 = (20 * pos - 20 * pos_last - (8 * vel + 12 * vel_last)*t_move - (3 * acc_last - acc)*t_move * t_move) / (2 * t_move * t_move * t_move);
	factor.a4 = (30 * pos_last - 30 * pos + (14 * vel + 16 * vel_last)*t_move + (3 * acc_last - 2 * acc)*t_move * t_move) / (2 * t_move * t_move * t_move * t_move);
	factor.a5 = (12 * pos - 12 * pos_last - (6 * vel + 6 * vel_last)*t_move - (acc_last - acc)*t_move * t_move) / (2 * t_move * t_move * t_move * t_move * t_move); //计算五次多项式系数
	for (int i = 0; i < Interpolation_Num; i++)
	{
		double x = i / 1.0 / Interpolation_Num;
		req_pos_resample[i] = factor.a0 + factor.a1 * x + factor.a2 * x * x + factor.a3 * x * x * x + factor.a4 * x * x * x * x + factor.a5 * x * x * x * x * x;
	}
	return req_pos_resample;
}

/******************** linear interpolation**********************/
		//for (int i = 0; i < Interpolation_Num; i++)
		//{
		//	if (i == 0)
		//	{
		//		req_pos_resample1_flag[i] = 1;
		//		req_pos_resample2_flag[i] = 1;
		//		req_pos_resample3_flag[i] = 1;
		//		req_pos_resample4_flag[i] = 1;
		//	}
		//	req_pos_resample1[i] = req_pos_last.m1 + (req_pos.m1 - req_pos_last.m1)*i / 1.0/Interpolation_Num;
		//	req_pos_resample2[i] = req_pos_last.m2 + (req_pos.m2 - req_pos_last.m2)*i / 1.0/Interpolation_Num;
		//	req_pos_resample3[i] = req_pos_last.m3 + (req_pos.m3 - req_pos_last.m3)*i / 1.0/Interpolation_Num;
		//	req_pos_resample4[i] = req_pos_last.m4 + (req_pos.m4 - req_pos_last.m4)*i / 1.0/Interpolation_Num;
		//	//std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << req_pos_resample1[i] << std::endl;
		//	mtx.lock();
		//	queue1.push(req_pos_resample1[i]);
		//	queue2.push(req_pos_resample2[i]);
		//	queue3.push(req_pos_resample3[i]);
		//	queue4.push(req_pos_resample4[i]);
		//	queue1_flag.push(req_pos_resample1_flag[i]);
		//	queue2_flag.push(req_pos_resample2_flag[i]);
		//	queue3_flag.push(req_pos_resample3_flag[i]);
		//	queue4_flag.push(req_pos_resample4_flag[i]);
		//	mtx.unlock();
		//}
/******************** linear interpolation**********************/
