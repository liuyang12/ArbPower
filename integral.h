// integral.h
// 数值积分方法求解 ln(x)
// ln(x) = Integ{1, x}(dt/t)
#ifndef INTEGRAL_H
#define INTEGRAL_H
#include "functions.h"
// 数值积分方法求解 ln(x)
double ln_integral(double x, bool MID = false); // MID 是否为中间值相比较误差，默认为 T[k][0]
double log10_integral(double x);
double power_integral(double x, double y);

#endif // INTEGRAL_H
