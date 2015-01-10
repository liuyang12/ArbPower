// ode.cpp
// 常微分方程方法求解 exp(x), ln(x)
#include "ode.h"
#include "Taylor.h"

// exp(x) 的常微分方程求解 - 步长一定
// 计算范围 x∈[0, 1], y = exp(x)
// y(n+1) = [1+h+(h^2)/2+(h^3)/6+(h^4)/24]*y(n)
double exp_ode(double x)
{
    if(x < 0)
    {
        if(x < -99999.0)
            return 0.0;

        return (1.0/exp_ode(-x));
    }
    // x >= 0
    int k = int(x);     // k = [x]
    double u = x - k;       // u = x - [x]
    double y0 = 1.0;        // y(0) = 1.0
    double h = STEP;    // 初始步长 h = 1.0e-4
    int N = int(u/h);     // 只计算 N+1 步 N*h<=u<(N+1)*h
//    if(0 == N)      // 避免分母为零
//        return 1.0;
    // N >= 1
    double alpha = u/h - N; // 0<=alpha<1
    double y = 0;         // 当前值
    double y_prev;        // 前一值
    for(int n = 0; n < N+1; n++) // 计算到y((N+1)*h)
    {
        y = (1.0+h+h*h/2+h*h*h/6+h*h*h*h/24)*y0;
        y_prev = y0;
        y0 = y;           // y0 保留前一时刻的值
    }
    double exp_u = (1-alpha)*y_prev + alpha*y;  // e^u = (1-alpha)*y(N) + alpha*y(N+1)
    for(int i = 0; i < k; i++)  // e^x = e^([x]) * e^(x-[x])
        exp_u = E * exp_u;
    return(exp_u);
}
// ln(x) 的常微分方程的求解 - 步长一定
// 实际需要计算的 x = u * 2^K，其中 1<=u<2
// y(n+1) = y(n) + h/6*[1/x(n)+4/(x(n)+h/2)+1/(x(n)+h)] 相当于复化辛普生公式
double ln_ode(double x)
{
    double t = x - 1.0;    // t = x - 1
    /// double 精度受限
    if(FABS(t) < ZERO)  // x == 1，ln(x) = 0
        return 0.0;
    if(t < 0)       // x < 1，ln(x) = -ln(1/x)，1/x > 1
    {
        if(x < ZERO)
            return -999999.0;
        return (-ln_ode(1.0/x));
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

    // 常微分方程求解 ln(u)
    double h = STEP;        // 步长 h = 1.0e-4
    int N = int((u-1.0)/h);
//    if(0 == N)
//        return (K*LN_TWO);
    double alpha = (u-1.0)/h - N;   // 0 <= alpha < 1
    double y0 = 0.0;
    double y = y0;
    double y_prev;        // 前一值
    double xn = 1.0-h;
    for(int i = 0; i < N+1; i++)    // 计算到 y(N+1) = y, y(N) = y0
    {
        xn = h+xn;
        y = y0 + h/6*(1/xn+4/(xn+h/2)+1/(xn+h));
        y_prev = y0;
        y0 = y;
    }
    double ln_u = (1-alpha)*y_prev + alpha*y;   // ln(u) = (1-alpha)*y(N) + alpha*y(N+1)
    return (ln_u + K*LN_TWO);
}

double power_ode(double x, double y)
{
    return exp_ode(y*ln_ode(x));
}

double log10_ode(double x)
{
    return (ln_ode(x) / LN_TEN);
}
