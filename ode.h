// ode.h
// 常微分方程方法求解 exp(x), ln(x)
#ifndef ODE_H
#define ODE_H
#include "functions.h"

// exp(x) 的常微分方程求解 - 步长一定
// 计算范围 x∈[0, 1], y = exp(x)
// y(n+1) = [1+h+(h^2)/2+(h^3)/6+(h^4)/24]*y(n)
double exp_ode(double x);
// ln(x) 的常微分方程的求解 - 步长一定
// 实际需要计算的 x = u * 2^K，其中 1<=u<2
// y(n+1) = y(n) + h/6*[1/x(n)+4/(x(n)+h/2)+1/(x(n)+h)] 相当于复化辛普生公式
double ln_ode(double x);
double power_ode(double x, double y);
double log10_ode(double x);
#endif // ODE_H
