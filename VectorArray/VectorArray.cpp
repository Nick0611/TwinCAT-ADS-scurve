// VectorArray.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;
#define percise 0.000000001
#define PLC_Sync 0.05

double func1(double v) {//原函数
	return 1000-2*240*pow(v,3);//方程1 x^2-3*x+2-e^x=0
}
double func2(double v) {//导数
	return -1440*pow(v,2);//方程1的导数
}
double func3(double sc, double InitV, double J, double v1, double T1, double v) {//原函数
	return -sc + (double(1) / 6)*J*pow(T1, 3) + InitV * T1 + 0 + v1 * v + (double(1) / 2)*J*T1*pow(v, 2)
		+ (double(1) / 6)*(-1 * J)*pow(T1, 3) + (double(1) / 2)*(J*T1 + 0 * v)*pow(T1, 2) + (v1 + J * T1*v)*T1;
}
double func3_dot(double sc, double InitV, double J, double v1, double T1, double v) {//导数
	return v1 + J * T1*v + J * T1*T1;//方程2的导数
}
double func4(double sc, double InitV, double J, double v) {//原函数
	return sc - 4 * InitV*v - 2 * J*pow(v, 3);
}
double func4_dot(double sc, double InitV, double J, double v) {//导数
	return 4 * InitV - 6 * J*pow(v, 2);//方程1的导数
}
void dichotomy(double x, double y) {
	double middle = (x + y) / 2;
	int i = 0;
	printf("-----------------二分法-------------------\n");
	printf("初始值为:左边界点%f,右边界点%f\n", x, y);
	while (fabs(func1(middle)) > percise) {
		func1(middle)*func1(x) > 0 ? x = middle : y = middle;
		middle = (x + y) / 2;
		i++;
		//printf("迭代次数为:%d,左边界点%f,右边界点%f\n", i, x, y);
	}
	printf("最终结果为%f\n", middle);
}
void NewtonMethod(double x) {
	int i = 0;
	printf("-----------------牛顿法-------------------\n");
	printf("初始值为%f\n", x);
	while (fabs(func1(x) / func2(x)) > percise) {
		x -= func1(x) / func2(x);
		i++;
		//printf("迭代次数为:%d,此时x为%f\n", i, x);
	}
	printf("最终结果为%f\n", x);
}
void NewtonDownMethod(double x) {
	int i = 0;
	double x1, u = 1;
	printf("---------------牛顿下山法------------------\n");
	printf("初始值为%f\n", x);
	while (fabs(func1(x) / func2(x)) > percise) {
		u = 1;
		x1 = x - u * func1(x) / func2(x);
		if (fabs(func1(x1)) >= fabs(func1(x)))
			u *= 0.5;
		i++;
		//printf("迭代次数为:%d,此时x为%f,x1为%f,u为%f\n", i, x, x1, u);
		x = x1;
	}
	printf("最终结果为%f\n", x);
}
void SecantMethod(double x, double y) {
	int i = 0;
	printf("-----------------弦割法-------------------\n");
	while (fabs(func1(x)*(y - x) / (func1(y) - func1(x))) > percise) {
		x -= func1(x)*(y - x) / (func1(y) - func1(x));
		i++;
		//printf("迭代次数为:%d,此时x为%f\n", i, x);
	}
	printf("最终结果为%f\n", x);
}

double NewtonDownMethod(double sc, double InitV, double J, double x, double T1, double v) {
	int i = 0;
	double x1, u = 1;
	//printf("---------------牛顿下山法------------------\n");
	//printf("初始值为%f\n", x);
	while (fabs(func3(sc, InitV, J, x, T1, v) / func3_dot(sc, InitV, J, x, T1, v)) > percise) {
		u = 1;
		x1 = x - u * func3(sc, InitV, J, x, T1, v) / func3_dot(sc, InitV, J, x, T1, v);
		if (fabs(func3(sc, InitV, J, x1, T1, v)) >= fabs(func3(sc, InitV, J, x, T1, v)))
			u *= 0.5;
		i++;
		//printf("迭代次数为:%d,此时x为%f,x1为%f,u为%f\n", i, x, x1, u);
		x = x1;
	}
	return x;
}

/////////////////////////////////////////////////////////////////////////////////////////////
double NewtonDownMethod(double sc, double InitV, double J, double x) {
	int i = 0;
	double x1, u = 1;
	//printf("---------------牛顿下山法------------------\n");
	//printf("初始值为%f\n", x);
	while (fabs(func4(sc, InitV, J, x) / func4_dot(sc, InitV, J, x)) > percise) {
		u = 1;
		x1 = x - u * func4(sc, InitV, J, x) / func4_dot(sc, InitV, J, x);
		if (fabs(func4(sc, InitV, J, x1)) >= fabs(func4(sc, InitV, J, x)))
			u *= 0.5;
		i++;
		//printf("迭代次数为:%d,此时x为%f,x1为%f,u为%f\n", i, x, x1, u);
		x = x1;
	}
	return x;
}
bool SProfileT1(double S0, double J, double Vs, std::vector<double>&t, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		s.push_back(S0 + (double(1) / 6)*J*pow(*it, 3) + Vs * (*it));  //s
		v.push_back((double(1) / 2)*J*pow((*it), 2) + Vs);  //v
		a.push_back(J*(*it));  //a
	}
	return true;
}

// S2段曲线
bool SProfileT2(double T1, double J, double Vl, std::vector<double>&t, double S0, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		s.push_back(S0 + Vl * (*it) + (double(1) / 2)*J*T1*pow((*it), 2));  //s
		v.push_back(Vl + J * T1*(*it));  //v
		a.push_back(J * T1 + 0 * (*it));  //a
	}
	return true;
}

// S3段曲线末端速度倒推型
bool SProfileT3(double T3, double J, double Vc, std::vector<double>&t, double St3, double a3, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		v.push_back(Vc + (double(1) / 2)*J*pow((T3 - (*it)), 2) - a3 * (T3 - (*it)));  //s
		s.push_back(St3 - (double(1) / 6)*J*pow((T3 - (*it)), 3) + (double(1) / 2)*a3*pow((T3 - (*it)), 2) - Vc * (T3 - (*it)));  //v
		a.push_back(a3 - J * (T3 - (*it)));  //a
	}
	return true;
}

// S3段曲线末端速度正推型
bool SProfileT32(double am, double J, double vm, std::vector<double>&t, double sm, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		a.push_back(am + J * (*it));  //s
		v.push_back(vm + am * (*it) + (double(1) / 2)*J*pow((*it), 2));  //v
		s.push_back(sm + (double(1) / 6)*J*pow((*it), 3) + (double(1) / 2)*am*pow((*it), 2) + vm * (*it));  //a
	}
	return true;
}

// S4段曲线
bool SProfileT4(double S0, double Vc, std::vector<double>&t, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		a.push_back((*it) * 0);  //s
		v.push_back(Vc + 0 * (*it));  //v
		s.push_back(Vc * (*it) + S0);  //a
	}
	return true;
}

// S5段曲线
bool SProfileT5(double J, double Vc, std::vector<double>&t, double s4, double a4, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		v.push_back(Vc + (double(1) / 2)*J*pow((*it), 2) + a4 * (*it));  //s
		s.push_back(s4 + Vc * (*it) + (double(1) / 6)*J*pow((*it), 3) + (double(1) / 2)*a4*pow((*it), 2));  //v
		a.push_back(a4 + J * (*it));  //a
	}
	return true;
}

// S6段曲线
bool SProfileT6(double T5, double J, double Vm2, std::vector<double>&t, double S5, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		v.push_back(Vm2 + J * T5*(*it));  //s
		s.push_back(S5 + Vm2 * (*it) + (double(1) / 2)*J*T5*pow((*it), 2));  //v
		a.push_back(J * T5 + 0 * (*it));  //a
	}
	return true;
}

// S7段曲线倒推型
bool SProfileT7(double T7, double J, double Vs2, std::vector<double>&t, double St7, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		v.push_back(Vs2 + (double(1) / 2)*J*pow((T7 - (*it)), 2));  //s
		s.push_back(St7 - (double(1) / 6)*J*pow(T7, 3) + (double(1) / 2)*J*pow(T7, 2) * (*it) - (double(1) / 2)*J*T7*pow((*it), 2) + (double(1) / 6)*J*pow((*it), 3) - Vs2 * T7 + Vs2 * (*it));  //v
		a.push_back(-J * (T7 - (*it)));  //a
	}
	return true;
}

// S7段曲线正推型
bool SProfileT72(double al2, double J, double vl2, std::vector<double>&t, double sl2, std::vector<double>&s, std::vector<double>&v, std::vector<double>&a)
{
	for (std::vector<double>::iterator it = t.begin(); it != t.end(); it++) {
		a.push_back(al2 + J * (*it));  //s
		v.push_back(vl2 + al2 * (*it) + (double(1) / 2)*J*pow((*it), 2));  //v
		s.push_back(sl2 + (double(1) / 6)*J*pow((*it), 3) + (double(1) / 2)*al2*pow((*it), 2) + vl2 * (*it));  //a
	}
	return true;
}

void scurve()
{
	bool nerr;
	double GoalV = 500.0; //单位mm/s
	double GoalS = 1000.0; //单位mm
	double Acc = 100.0;
	double Jerk = 200.0;

	double InitV = 0.0;
	double InitS = 0.0;
	double T1, T2, T3, T4, T5, T6, T7;
	int n1, n2, n3, n4, n5, n6, n7;
	double S[8] = { 0 };
	double Vs2 = InitV;
	int n = 100;
	T1 = Acc / Jerk;
	double Vtemp = pow(Acc, 2) / Jerk; //这个速度变化量包括了加加速度段和加减速度段的速度变化

	double Vmax = abs(GoalV - InitV);

	double Vs = InitV; //所以不用担心速度跟不上的情况，只要考虑好如何优化分配位移的情况就行了。

	double J = Jerk;
	//T1 = sqrt((((GoalV + Vs) / 2 - Vs) * 2) / J);
	std::vector<double> T_stage1; std::vector<double> s1; std::vector<double> v1; std::vector<double> a1;
	std::vector<double> T_stage2; std::vector<double> s2; std::vector<double> v2; std::vector<double> a2;
	std::vector<double> T_stage3; std::vector<double> s3; std::vector<double> v3; std::vector<double> a3;
	std::vector<double> T_stage4; std::vector<double> s4; std::vector<double> v4; std::vector<double> a4;
	std::vector<double> T_stage5; std::vector<double> s5; std::vector<double> v5; std::vector<double> a5;
	std::vector<double> T_stage6; std::vector<double> s6; std::vector<double> v6; std::vector<double> a6;
	std::vector<double> T_stage7; std::vector<double> s7; std::vector<double> v7; std::vector<double> a7;
	std::vector<double> t1; std::vector<double> t2; std::vector<double> t3; std::vector<double> t4; std::vector<double> t5; std::vector<double> t6; std::vector<double> t7;
	double s1_0 = { 0 }; double s3_0 = { 0 }; double s5_0 = { 0 }; double s7_0 = { 0 }; double v1_0 = { 0 }; double a1_0 = { 0 };
	s1_0 = (double(1) / 6)*Jerk*pow(T1, 3) + Vs * T1;
	v1_0 = (double(1) / 2)*J*pow(T1, 2) + Vs;
	a1_0 = Jerk * T1;

	T3 = T1;
	J = -Jerk;
	double Vc = 2 * (v1_0 - InitV) + InitV;
	double t = 0;
	s3_0 = 0 + (double(1) / 6)*J*pow(T3, 3) - (double(1) / 2)*J*pow(T3, 2) * t + (double(1) / 2)*J*T3*pow(t, 2) - (double(1) / 6)*J*pow(t, 3) + Vc * T3 - Vc * t;

	J = Jerk;

	s7_0 = 0 + (double(1) / 6)*J*pow(T3, 3) - (double(1) / 2)*J*pow(T3, 2) * t + (double(1) / 2)*J*T3*pow(t, 2) - (double(1) / 6)*J*pow(t, 3) + Vs * T3 - Vs * t; //这部分只是计算相对T7段的位移变化量
	J = -Jerk;
	s5_0 = 0 + Vc * T1 + (double(1) / 6)*J*pow(T1, 3) + (double(1) / 2) * 0 * pow(T1, 2);

	S[4] = s1_0 + s3_0 + s5_0 + s7_0; //这是四段曲线位移的分界点
	J = Jerk;
	S[4] = 4 * InitV*T1 + 2 * J*pow(T1, 3); //这个没加初始的位移变化量，所以前面的计算的s(1)、s(3)、s(5)、s(7)都没有加初始的位移
	if (Vmax < Vtemp || Vmax == Vtemp) //速度最大变化量小于加加速度段和减减速度段的速度变化量，此时速度曲线分为四段或五段，此时看位移的情况当前的情况下速度都是可以跟的上的
	{
		if (S[4] < abs(GoalS - InitS)) // && InitV == Vs2 就用五段曲线 else是用四段曲线
		{
			t1.clear(); t2.clear(); t3.clear(); t4.clear(); t5.clear(); t6.clear(); t7.clear();
			s1.clear(); s2.clear(); s3.clear(); s4.clear(); s5.clear(); s6.clear(); s7.clear();
			v1.clear(); v2.clear(); v3.clear(); v4.clear(); v5.clear(); v6.clear(); v7.clear();
			a1.clear(); a2.clear(); a3.clear(); a4.clear(); a5.clear(); a6.clear(); a7.clear();
			n1 = ceil(T1 / PLC_Sync);
			for (int i = 0; i < n1 + 1; i++)
			{
				t1.push_back(double(i) / n1 * T1);
			}
			t = T1;
			nerr = SProfileT1(InitS, Jerk, InitV, t1, s1, v1, a1);

			n3 = ceil(T1 / PLC_Sync);
			for (int i = 0; i < n3 + 1; i++)
			{
				t3.push_back(double(i) / n3 * T3);
			}
			nerr = SProfileT3(T1, -Jerk, GoalV, t3, S[4] / 2 + InitS, 0, s3, v3, a3);

			//[St{ 3 }, Vt{ 3 }, At{ 3 }] = SProfileT32(At{ 1 }(n), -Jerk, Vt{ 1 }(n), t3 - t, St{ 1 }(n));
			t = 2 * t;

			T4 = abs(S[4] - abs(GoalS - InitS)) / GoalV;
			n4 = ceil(T4 / PLC_Sync);
			for (int i = 0; i < n4 + 1; i++)
			{
				t4.push_back(double(i) / n4 * T4);
			}
			nerr = SProfileT4(*(s3.end()-1), GoalV, t4, s4, v4, a4);
			t = t + T4;

			n5 = ceil(T1 / PLC_Sync);
			for (int i = 0; i < n5 + 1; i++)
			{
				t5.push_back(double(i) / n5 * T1);
			}
			nerr = SProfileT5(-Jerk, GoalV, t5, *(s4.end()-1), *(a4.end() - 1), s5, v5, a5);
			t = t + T1;

			n7 = ceil(T1 / PLC_Sync);
			for (int i = 0; i < n7 + 1; i++)
			{
				t7.push_back(double(i) / n7 * T1);
			}
			nerr = SProfileT7(T1, Jerk, InitV, t7, GoalS, s7, v7, a7);

			//[St{ 7 }, Vt{ 7 }, At{ 7 }] = SProfileT72(At{ 5 }(n), J, Vt{ 5 }(n), t7 - t, St{ 5 }(n));
			t = t + T1;
		}
		else
		{
			t1.clear(); t2.clear(); t3.clear(); t4.clear(); t5.clear(); t6.clear(); t7.clear();
			s1.clear(); s2.clear(); s3.clear(); s4.clear(); s5.clear(); s6.clear(); s7.clear();
			v1.clear(); v2.clear(); v3.clear(); v4.clear(); v5.clear(); v6.clear(); v7.clear();
			a1.clear(); a2.clear(); a3.clear(); a4.clear(); a5.clear(); a6.clear(); a7.clear();
			double sc = abs(GoalS - InitS);
			J = Jerk;
			double T = NewtonDownMethod(sc, InitV, J, 0.1);

			Vs = InitV;
			J = Jerk;

			n1 = ceil(T / PLC_Sync);
			for (int i = 0; i < n1 + 1; i++)
			{
				t1.push_back(double(i) / n1 * T);
			}
			t = T;
			nerr = SProfileT1(InitS, Jerk, Vs, t1, s1, v1, a1);

			J = -Jerk;

			////////////////////////////////////////

			n3 = ceil(T / PLC_Sync);
			for (int i = 0; i < n3 + 1; i++)
			{
				t3.push_back(double(i) / n3 * T);
			}
			nerr = SProfileT32(*(a1.end() - 1), J, *(v1.end() - 1), t3, *(s1.end() - 1), s3, v3, a3);
			t = T + T;

			J = -Jerk;

			n5 = ceil(T / PLC_Sync);
			for (int i = 0; i < n5 + 1; i++)
			{
				t5.push_back(double(i) / n5 * T);
			}
			nerr = SProfileT5(J, *(v3.end() - 1), t5, *(s3.end() - 1), *(a3.end() - 1), s5, v5, a5);
			t = t + T;

			J = Jerk;

			n7 = ceil(T / PLC_Sync);
			for (int i = 0; i < n7 + 1; i++)
			{
				t7.push_back(double(i) / n7 * T);
			}
			nerr = SProfileT72(*(a5.end() - 1), J, *(v5.end() - 1), t7, *(s5.end() - 1), s7, v7, a7);
			t = t + T;
		}
	}
	else
	{
		t1.clear(); t2.clear(); t3.clear(); t4.clear(); t5.clear(); t6.clear(); t7.clear();
		s1.clear(); s2.clear(); s3.clear(); s4.clear(); s5.clear(); s6.clear(); s7.clear();
		v1.clear(); v2.clear(); v3.clear(); v4.clear(); v5.clear(); v6.clear(); v7.clear();
		a1.clear(); a2.clear(); a3.clear(); a4.clear(); a5.clear(); a6.clear(); a7.clear();
		if (S[4] < abs(GoalS - InitS)) //可分为六段和七段大于四段的位移量了
			//先计算六段的位移总量，采用的时间间隔都是一样
		{
			double s1_00 = { 0 }; double s2_00 = { 0 }; double s3_00 = { 0 }; double s5_00 = { 0 }; double s6_00 = { 0 }; double s7_00 = { 0 };
			double v1_00 = { 0 }; double v2_00 = { 0 }; double v3_00 = { 0 }; double v5_00 = { 0 }; double v6_00 = { 0 }; double v7_00 = { 0 };
			double a1_00 = { 0 }; double a2_00 = { 0 }; double a3_00 = { 0 }; double a5_00 = { 0 }; double a6_00 = { 0 }; double a7_00 = { 0 };
			t = T1;
			J = Jerk;
			s1_00 = 0 + (double(1) / 6)*J*pow(t, 3) + InitV * t;
			v1_00 = (double(1) / 2)*J*pow(T1, 2) + Vs;
			a1_00 = Jerk * T1;
			s2_00 = 0 + v1_00 * t + (double(1) / 2)*J*T1*pow(t, 2);
			v2_00 = v1_00 + J * T1*t;
			a2_00 = J * T1 + 0 * t;
			J = -Jerk;

			a3_00 = a2_00 + J * T1;
			v3_00 = v2_00 + a2_00 * T1 + (double(1) / 2)*J*pow(T1, 2);
			s3_00 = 0 + (double(1) / 6)*J*pow(T1, 3) + (double(1) / 2)*a2_00*pow(T1, 2) + v2_00 * T1;

			v5_00 = v3_00 + (double(1) / 2)*J*pow(T1, 2) + 0 * T1;
			s5_00 = 0 + v3_00 * T1 + (double(1) / 6)*J*pow(T1, 3) + (double(1) / 2) * 0 * pow(T1, 2);
			a5_00 = 0 + J * T1;

			v6_00 = v5_00 + J * T1*T1;
			s6_00 = 0 + v5_00 * T1 + (double(1) / 2)*J*T1*pow(T1, 2);
			a6_00 = J * T1 + 0 * T1;

			J = Jerk;

			a7_00 = a6_00 + J * T1;
			v7_00 = v6_00 + a6_00 * T1 + (double(1) / 2)*J*pow(T1, 2);
			s7_00 = 0 + (double(1) / 6)*J*pow(T1, 3) + (double(1) / 2)*a6_00*pow(T1, 2) + v6_00 * T1;

			S[6] = s1_00 + s2_00 + s3_00 + s5_00 + s6_00 + s7_00;

			if (S[6] <= abs(GoalS - InitS)) //大于六段的时候的位移
			{
				J = Jerk;
				n1 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n1 + 1; i++)
				{
					t1.push_back(double(i) / n1 * T1);
				}
				nerr = SProfileT1(InitS, J, InitV, t1, s1, v1, a1);
				t = T1;

				n2 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n2 + 1; i++)
				{
					t2.push_back(double(i) / n2 * T1);
				}
				nerr = SProfileT2(T1, J, *(v1.end()-1), t2, *(s1.end()-1), s2, v2, a2);
				t = t + T1;

				J = -Jerk;
				n3 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n3 + 1; i++)
				{
					t3.push_back(double(i) / n3 * T1);
				}
				nerr = SProfileT32(*(a2.end()-1), J, *(v2.end()-1), t3, *(s2.end()-1), s3, v3, a3);
				t = t + T1;

				T4 = abs(S[6] - abs(GoalS - InitS)) / *(v3.end()-1);
				n4 = ceil(T4 / PLC_Sync);
				for (int i = 0; i < n4 + 1; i++)
				{
					t4.push_back(double(i) / n4 * T4);
				}
				nerr = SProfileT4(*(s3.end()-1), *(v3.end()-1), t4, s4, v4, a4);
				t = t + T4;

				n5 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n5 + 1; i++)
				{
					t5.push_back(double(i) / n5 * T1);
				}
				nerr = SProfileT5(J, *(v4.end()-1), t5, *(s4.end()-1), 0, s5, v5, a5);
				t = t + T1;

				n6 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n6 + 1; i++)
				{
					t6.push_back(double(i) / n6 * T1);
				}
				nerr = SProfileT6(T1, J, *(v5.end()-1), t6, *(s5.end()-1), s6, v6, a6);
				t = t + T1;

				n7 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n7 + 1; i++)
				{
					t7.push_back(double(i) / n7 * T1);
				}
				J = Jerk;
				nerr = SProfileT72(*(a6.end()-1), J, *(v6.end()-1), t7, *(s6.end()-1), s7, v7, a7);

				t = t + T1;
			}

			else
			{
				double st = abs(GoalS - InitS) / 2;

				T1 = Acc / Jerk;
				J = Jerk;
				n1 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n1 + 1; i++)
				{
					t1.push_back(double(i) / n1 * T1);
				}
				nerr = SProfileT1(InitS, J, InitV, t1, s1, v1, a1);
				t = T1;

				T2 = NewtonDownMethod(st, InitV, J, 0.1, T1, *(v1.end() - 1));

				n2 = ceil(T2 / PLC_Sync);
				for (int i = 0; i < n2 + 1; i++)
				{
					t2.push_back(double(i) / n2 * T2);
				}
				nerr = SProfileT2(T1, J, *(v1.end() - 1), t2, *(s1.end() - 1), s2, v2, a2);
				t = t + T2;

				J = -Jerk;
				n3 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n3 + 1; i++)
				{
					t3.push_back(double(i) / n3 * T1);
				}
				nerr = SProfileT32(*(a2.end() - 1), J, *(v2.end() - 1), t3, *(s2.end() - 1), s3, v3, a3);
				t = t + T1;

				n5 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n5 + 1; i++)
				{
					t5.push_back(double(i) / n5 * T1);
				}
				nerr = SProfileT5(J, *(v3.end() - 1), t5, *(s3.end() - 1), 0, s5, v5, a5);
				t = t + T1;

				n6 = ceil(T2 / PLC_Sync);
				for (int i = 0; i < n6 + 1; i++)
				{
					t6.push_back(double(i) / n6 * T2);
				}
				nerr = SProfileT6(T1, J, *(v5.end() - 1), t6, *(s5.end() - 1), s6, v6, a6);
				t = t + T2;

				n7 = ceil(T1 / PLC_Sync);
				for (int i = 0; i < n7 + 1; i++)
				{
					t7.push_back(double(i) / n7 * T1);
				}
				J = Jerk;
				nerr = SProfileT72(*(a6.end() - 1), J, *(v6.end() - 1), t7, *(s6.end() - 1), s7, v7, a7);

				t = t + T1;

			}

		}
		else
		{
			double sc = abs(GoalS - InitS);
			J = Jerk;
			double T = NewtonDownMethod(sc, InitV, J, 0.1);

			Vs = InitV;
			J = Jerk;

			n1 = ceil(T / PLC_Sync);
			for (int i = 0; i < n1 + 1; i++)
			{
				t1.push_back(double(i) / n1 * T);
			}
			t = T;
			nerr = SProfileT1(InitS, Jerk, Vs, t1, s1, v1, a1);

			J = -Jerk;

			////////////////////////////////////////

			n3 = ceil(T / PLC_Sync);
			for (int i = 0; i < n3 + 1; i++)
			{
				t3.push_back(double(i) / n3 * T);
			}
			nerr = SProfileT32(*(a1.end() - 1), J, *(v1.end() - 1), t3, *(s1.end() - 1), s3, v3, a3);
			t = T + T;

			J = -Jerk;

			n5 = ceil(T / PLC_Sync);
			for (int i = 0; i < n5 + 1; i++)
			{
				t5.push_back(double(i) / n5 * T);
			}
			nerr = SProfileT5(J, *(v3.end() - 1), t5, *(s3.end() - 1), *(a3.end() - 1), s5, v5, a5);
			t = t + T;

			J = Jerk;

			n7 = ceil(T / PLC_Sync);
			for (int i = 0; i < n7 + 1; i++)
			{
				t7.push_back(double(i) / n7 * T);
			}
			nerr = SProfileT72(*(a5.end() - 1), J, *(v5.end() - 1), t7, *(s5.end() - 1), s7, v7, a7);
			t = t + T;

		}
	}

	for (std::vector<double>::iterator it = s1.begin(); it != s1.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s2.begin(); it != s2.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s3.begin(); it != s3.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s4.begin(); it != s4.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s5.begin(); it != s5.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s6.begin(); it != s6.end(); it++) {
		std::cout << *it << std::endl;
	}
	for (std::vector<double>::iterator it = s7.begin(); it != s7.end(); it++) {
		std::cout << *it << std::endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//vector<double> x; vector<double> s; vector<double> v; vector<double> a;
	//for (int i = 0; i < 20; ++i)
	//	x.push_back(i);
	//SProfileT1(10, 200, 20, x, s, v, a);
	//int i = 0;
	//for (std::vector<double>::iterator it = s.begin(); it != s.end(); it++) {
	//	std::cout << *it << std::endl;
	//	std::cout << *(v.begin()+i) << std::endl;
	//	std::cout << *(a.begin() + i) << std::endl;
	//	i++;
	//}
	//dichotomy(0, 1);//用二分法求两个方程的解
	//NewtonMethod(0.1);//用牛顿法求两个方程的解
	//NewtonDownMethod(0.1);//用牛顿下降法求两个方程的解
	//SecantMethod(-10, 1);//用弦割法求两个方程的解
	//double xx = NewtonDownMethod(500,0,240,0.1, 4.1667e-01,20);
	//std::cout << xx << std::endl;
	scurve();
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
