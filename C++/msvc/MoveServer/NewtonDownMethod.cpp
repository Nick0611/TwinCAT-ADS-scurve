#include "NewtonDownMethod.h"

double func1(double sc, double InitV, double J, double v) {//ԭ����
	return sc - 4 * InitV*v - 2 * J*pow(v, 3);
}
double func1_dot(double sc, double InitV, double J, double v) {//����
	return 4 * InitV - 6 * J*pow(v, 2);//����1�ĵ���
}
double func2(double sc, double InitV, double J, double v1, double T1, double v) {//ԭ����
	return -sc + (double(1) / 6)*J*pow(T1, 3) + InitV * T1 + 0 + v1 * v + (double(1) / 2)*J*T1*pow(v, 2)
		+ (double(1) / 6)*(-1 * J)*pow(T1, 3) + (double(1) / 2)*(J*T1 + 0 * v)*pow(T1, 2) + (v1 + J * T1*v)*T1;
}
double func2_dot(double sc, double InitV, double J, double v1, double T1, double v) {//����
	return v1 + J * T1*v + J * T1*T1;//����2�ĵ���
}
double NewtonDownMethod(double sc, double InitV, double J, double x) {
	int i = 0;
	double x1, u = 1;
	//printf("---------------ţ����ɽ��------------------\n");
	//printf("��ʼֵΪ%f\n", x);
	while (fabs(func1(sc, InitV, J, x) / func1_dot(sc, InitV, J, x)) > percise) {
		u = 1;
		x1 = x - u * func1(sc, InitV, J, x) / func1_dot(sc, InitV, J, x);
		if (fabs(func1(sc, InitV, J, x1)) >= fabs(func1(sc, InitV, J, x)))
			u *= 0.5;
		i++;
		//printf("��������Ϊ:%d,��ʱxΪ%f,x1Ϊ%f,uΪ%f\n", i, x, x1, u);
		x = x1;
	}
	return x;
}
double NewtonDownMethod(double sc, double InitV, double J, double x, double T1, double v) {
	int i = 0;
	double x1, u = 1;
	//printf("---------------ţ����ɽ��------------------\n");
	//printf("��ʼֵΪ%f\n", x);
	while (fabs(func2(sc, InitV, J, x,T1,v) / func2_dot(sc, InitV, J, x, T1, v)) > percise) {
		u = 1;
		x1 = x - u * func2(sc, InitV, J, x, T1, v) / func2_dot(sc, InitV, J, x, T1, v);
		if (fabs(func2(sc, InitV, J, x1, T1, v)) >= fabs(func2(sc, InitV, J, x, T1, v)))
			u *= 0.5;
		i++;
		//printf("��������Ϊ:%d,��ʱxΪ%f,x1Ϊ%f,uΪ%f\n", i, x, x1, u);
		x = x1;
	}
	return x;
}