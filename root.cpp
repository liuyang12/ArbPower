// 方程求根
// a^b = x 即求ln(x)/b = ln(a)的根
#include "root.h"
#include "Taylor.h"
#include "ode.h"
#include "integral.h"

//#include ""

// 方程求根方法求解 ln(y) = x即y= e^x
// f(x) = ln(x) - b*ln(a)
// y(k+1) = y(k)*(1+x-ln(y(k)))
double exp_root(double x, METHOD method)
{
    if(x < 0)
    {
        if(x < -99999.0)
            return 0.0;
        return (1.0/exp_root(-x));
    }
    // x >= 0
    double y0 = 1.0;
    double y, y_prev;
    double err = 1.0;
    while(FABS(err >= ERROR_ANS))
    {
        switch (method) {
        case TAYLOR:
            y = y0*(1.0+x-ln_taylor(y0));
            break;
        case ODE:
            y = y0*(1.0+x-ln_ode(y0));
            break;
        case INTEGRAL:
            y = y0*(1.0+x-ln_integral(y0));
            break;
        default:
            y = y0*(1.0+x-ln_taylor(y0));
            break;
        }
        y_prev = y0;
        y0 = y;
        err = (y - y_prev)/y;   // 相对误差
    }
    return y;
}

double power_root(double x, double y, METHOD method)
{
    switch (method) {
    case TAYLOR:
        return exp_root(y*ln_taylor(x), method);
        break;
    case ODE:
        return exp_root(y*ln_ode(x), method);
        break;
    case INTEGRAL:
        return exp_root(y*ln_integral(x), method);
        break;
    default:
        return exp_root(y*ln_taylor(x), method);
        break;
    }
}
