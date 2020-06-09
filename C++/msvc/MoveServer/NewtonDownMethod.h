#pragma once
#include <cmath> // Needed for the pow function
#include <iostream>

#define percise 0.000000001

double func1(double sc, double InitV, double J, double v);
double func1_dot(double sc, double InitV, double J, double v);
double func2(double sc, double InitV, double J, double v1, double T1, double v);
double func2_dot(double sc, double InitV, double J, double v1, double T1, double v);
double NewtonDownMethod(double sc, double InitV, double J, double x);
double NewtonDownMethod(double sc, double InitV, double J, double x, double T1, double v);