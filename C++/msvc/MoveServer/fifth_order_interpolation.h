#pragma once

typedef struct
{
	double a0;
	double a1;
	double a2;
	double a3;
	double a4;
	double a5;
}fifth_coefficient;

double* fifth_order_interpolation(double pos_last, double pos, double vel_last, double vel, double acc_last, double acc, double t_move, int Interpolation_Num, double *req_pos_resample);