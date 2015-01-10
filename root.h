// 方程求根
// a^b = x 即求ln(x)/b = ln(a)的根
#ifndef ROOT_H
#define ROOT_H
#include "functions.h"

// 方程求根方法求解 ln(y) = x即y= e^x
double exp_root(double x, METHOD method = TAYLOR);       // method 表示 ln(x)求解的算法
double power_root(double x, double y, METHOD method = TAYLOR);
#endif // ROOT_H
