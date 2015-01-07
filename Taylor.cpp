/// Taylor.cpp
/// Taylor 展开方法求取 ln(x) e^x
/// 从而利用 x^y = e^(y*ln(x)) 进行求解
#ifndef TAYLOR_METHOD
#define TAYLOR_METHOD
#include "Taylor.h"

// ln(x) 的 Taylor 展开方法计算
// 基本的 Taylor 展开的方法 ln(x) = sigma{n=1:∞}-(-1)^n / n * (x-1)^n, 0<x<2
double ln_taylor0(double x)
{

}

// ln(x) 的 Taylor 展开方法计算
// x 的范围以及一般范围 ZERO < x < ZERO^(-1)
double ln_taylor(double x)
{
    double t = x - 1.0;    // t = x - 1
    /// double 精度受限
    if(FABS(t) < ZERO)  // x == 1，ln(x) = 0
        return 0.0;
    if(t < 0)       // x < 1，ln(x) = -ln(1/x)，1/x > 1
        return (-ln_taylor(1.0/x));
    // t > 0
    int K = 0;
    double powK = 2;   // powK = 2^(K+1);
    double u = x;
    while(x >= powK)
    {
        powK = powK * 2;
        u = u / 2;
        K++;
    }
    // 2^K <= x < 2^(K+1), u = x/2^K
    // ln(x) = ln(u) + K*ln(2), 1 <= u < 2

    // Taylor 展开求取 ln(u) = sum
    double a = (u-1.0) / (u+1.0);
    double sum = 0.0;
    double temp = 0.0;
    double times = a;
    for(int n = 0; ; n++)
    {
        temp = 2.0/(2*n+1)*times;
        sum += temp;
        if(temp < ERROR_STORE)  // 小于给定的误差限度，小数点后14位
            break;
        times = times*a*a;
    }
    return (sum + K*LN_TWO);    // ln(x) = ln(u) + K*ln(2)
}
// exp(x) 的 Taylor 展开方法的计算
// x 的范围以及保证精度的范围 0 - ln(10) 用于计算 10^x = e^(x*ln(10)) 0<=x<1
double exp_taylor(double x)
{
    if(x < 0)
        return (1.0/exp_taylor(-x));
    // x >= 0
    double sum = 0.0;
    double temp = 1.0;
    for (int n = 0;; n++)
    {
        sum += temp;
        if( temp < ERROR_ANS )    // 小于给定的误差限度，小数点后15位
            break;
        temp = 1.0 * temp * x / (n+1);
    }
    return sum;
}
// power(x, y) 利用 x^y = e^(y*ln(x)) 求解
double power_taylor(double x, double y)
{
    return exp_taylor(y*ln_taylor(x));
}

// 浮点数的 10 次幂
SciNumber exp10_tosci(double x)
{
    int n = FLOOR(x);       // 向下取整
    double a = exp_taylor(LN_TEN * (x - n));    // a = 10^(x-n) = e^(ln(10)*(x-n))
    return SciNumber(a, n);
}

// 科学计数法 ln(x) 运算
double ln_sci(SciNumber sn)     // 返回值为 浮点数而不是科学计数法，因为 ln(sn) 不会越界
{
    return (LN_TEN * 1.0 * sn.n + ln_taylor(sn.a));
}

#endif // TAYLOR_METHOD
