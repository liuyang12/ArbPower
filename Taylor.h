/// Taylor.h
/// Taylor 展开方法求取 ln(x) e^x
/// 从而利用 x^y = e^(y*ln(x)) 进行求解
#ifndef TAYLOR_H
#define TAYLOR_H
#include "functions.h"

// ln(x) 的 Taylor 展开方法计算
// 基本的 Taylor 展开的方法 ln(x) = sigma{n=1:∞}-(-1)^n / n * (x-1)^n, 0<x<2
double ln_taylor0(double x);

// ln(x) 的 Taylor 展开方法计算
// x 的范围以及一般范围
double ln_taylor(double x);
// log10(x) = ln(x) / ln(10)
double log10_taylor(double x);
// exp(x) 的 Taylor 展开方法的计算
// x 的范围以及保证精度的范围 0 - ln(10) 用于计算 10^x = e^(x*ln(10)) 0<=x<1
double exp_taylor(double x);
// power(x, y) 利用 x^y = e^(y*ln(x)) 求解
double power_taylor(double x, double y);

#endif // TAYLOR_H
