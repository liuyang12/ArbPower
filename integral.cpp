// integral.h
// 数值积分方法求解 ln(x)
// ln(x) = Integ{1, x}(dt/t)
#include "integral.h"
#include "Taylor.h"

#define MAX_K 100
#define f(x) (1.0/(x))      // x的倒数，注意x == 0 情形

double T[MAX_K][MAX_K] = {0};   // 龙贝格算法预存一张表

inline double d_abs(double x)
{
    return ((x>=0) ? x :(-x));
}

// 数值积分方法求解 ln(x)
double ln_integral(double x, bool MID)
{
    double t = x - 1.0;    // t = x - 1
    /// double 精度受限
    if(FABS(t) < ZERO)  // x == 1，ln(x) = 0
        return 0.0;
    if(t < 0)       // x < 1，ln(x) = -ln(1/x)，1/x > 1
    {
        if(x < ZERO)
            return -999999.0;
        return (-ln_integral(1.0/x));
    }
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

    // 数值积分方法求取 ln(u) = Integ{1, u}(dt/t)
    // f(t) = 1/t
    // 利用龙贝格算法做外推加速
    double h = u - 1.0;
    double N = (u - 1.0)/h;
    T[0][0] = h/2.0*(f(1.0) + f(u));
    double sum;
    double pow4;
    int k = 1;
    for(k = 1; ; k++)
    {
        sum = 0.0;
        for(int i = 0; i < N; i++)
        {
            sum += 1.0/(1.0+(2*i+1.0)/2.0*h);  // 取中点
        }
        T[0][k] = 1.0/2*T[0][k-1] + h/2.0*sum;
        h = h/2.0;
        N = N*2.0;
        pow4 = 4.0;
        for(int j = 1; j <= k; j++)
        {
            T[j][k-j] = pow4/(pow4-1.0)*T[j-1][k+1-j] - 1.0/(pow4-1.0)*T[j-1][k-j];
            pow4 = pow4 * 4.0;      // pow4 = 4^j;
        }
        double error;
        if(MID)
            error = T[(k+1)/2][(k/2)] - T[k/2][(k-1)/2];
        else
            error = T[k][0] - T[k-1][0];
        if(FABS(error) < ERROR_ANS)   // 小于给定的误差限度
            break;
    }
    // 结果T[k][0]
    return (T[k][0] + K*LN_TWO);    // ln(x) = ln(u) + K*ln(2)
}

double log10_integral(double x)
{
    return (ln_integral(x) / LN_TEN);
}

double power_integral(double x, double y)
{
    return exp_taylor(y*ln_integral(x));
}

