/// functions.cpp
/// 各种函数的实现
///
///
///
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include <QStringList>
#include "functions.h"
#include "Taylor.h"
#include "ode.h"
#include "integral.h"
#include "root.h"

/// 科学计数法与字符串之间的转化
// 已通过 setValidator 限定 str 为双精度数
SciNumber StringtoSci(QString str)
{
    // 在 'e' 前后作分割
    QStringList strlist = str.split('e');
    if(strlist.size() < 2)  // 不是科学计数法
        return DoubletoSci(str.toDouble()); // 先转化为 double 型在再进行运算转化为科学计数法，其中 str 支持科学计数法 0.1234e3
    else    // 是科学计数法 strlist[0] strlist[1] 分别是浮点数和指数
    {
        SciNumber tempSci = StringtoSci(strlist[0]);                 // 处理用户输入 123.456e-3e-2 = 1.23456e-3（科学计数法的嵌套问题）
        return SciNumber(tempSci.a, tempSci.n + strlist[1].toInt());
    }
}

/// 浮点数与科学计数法之间的转化
// 浮点数转化为科学计数法
SciNumber DoubletoSci(double x)
{
    if(FABS(x) < ZERO)  // 如果是 0，则返回 0
        return (SciNumber(0, 0));
    // 以下非零 > ZERO
    double a;
    int n;
    a = x;  // a 初始化为 x
    n = 0;  // n 设定初值为 0
    while(a < 1.0)
    {
        a = a*10.0;
        n--;
    }
    // a >= 1.0
    while(a >= 10.0)
    {
        a = a/10.0;
        n++;
    }
    // a < 10.0
    return (SciNumber(a, n));
}
// 科学计数法转化为浮点数
double ScitoDouble(SciNumber sn)
{
    double x;
    x = sn.a;   // 初始化 x 为 sn.a
    while(sn.n >= 1)
    {
        x = x * 10.0;
        sn.n --;
    }
    while(sn.n <= -1)
    {
        x = x / 10.0;
        sn.n ++;
    }
    // sn.n = 0;
    return x;
}


// getSignificants 从字符串中读取浮点数的有效数字
// 已通过 setValidator 限定 str 为双精度数
//#ifndef GET_SIGNIFINCANTS
//#define GET_SIGNIFINCANTS
int getSignificants(QString str)
{   // 进行一次遍历获取其精度 计算代价：str.size()
//    bool sci = false;       // 是否为科学计数法输入
    int n = str.size();
    int i = 0;
    while((str[i] == '0' || str[i] == '.') && i < str.size())   // 开头是 '0' 或者小数点 '.'
    {
        n--;
        i++;
    }
    for(; i < str.size(); i++)
    {
        if(str[i] == '.')   // 小数点 '.' 在后面则减去这个小数点
            n--;
        if(str[i] == 'e')   // 科学计数法，截取 'e' 前部作为精度的依据
        {
            return (n+i-str.size());
        }
    }
    return n;
}
// getSignificants 从双精度数中读取有效数字
// num 为双精度数
int getSignificants(double num)
{

}



//#endif // GET_SIGNIFICANTS
// 一般方法，不使用科学计数法，无法处理 x^y 超出 double 范围的情况，此时需要指定结果为 0
double power_all(double x, double y, METHOD method)
{
    SciNumber sx = DoubletoSci(x);
    if(sx.n * y < -307)     // x^y < 1e-307
        return 0.0;
    switch (method) {   // 选择方法
    case TAYLOR:    // Taylor 展开方法
        return power_taylor(x, y);
        break;
    case ODE:       // 常微分方程初值问题解方法
        return power_ode(x, y);
        break;
    case INTEGRAL:
        return power_integral(x, y);
        break;
    case ROOT:
        return power_root(x, y, TAYLOR);
        break;
    default:
        return 0.0;
        break;
    }
}

// 科学计数法 power 运算，可以处理任意精度 (1^-99999999)^3 = ? int 的范围 [-2147483648, 2147483647]，如果 int n 采用 longlong 结果会更加突出
SciNumber power_sci(SciNumber sx, SciNumber sy, METHOD method)
{
    double y = ScitoDouble(sy); // 先将幂次转化为 double 型
    double ex;
    switch (method) {
    case TAYLOR:
        ex = y*(sx.n + log10_taylor(sx.a));
        break;
    case ODE:
        ex = y*(sx.n + log10_ode(sx.a));
        break;
    case INTEGRAL:
        ex = y*(sx.n + log10_ode(sx.a));
        method = TAYLOR;    // 指数采用Taylor展开进行计算
        break;
    case ROOT:
        ex = y*(sx.n + log10_taylor(sx.a));
        break;
    default:
        ex = 0.0;
        break;
    }
    return exp10_tosci(ex, method);
}

// 浮点数的 10 次幂
SciNumber exp10_tosci(double x, METHOD method)
{
    int n = FLOOR(x);       // 向下取整
    double a;
    switch (method) {   // 选择方法
    case TAYLOR:    // Taylor 展开方法
        a = exp_taylor(LN_TEN * (x - n));    // a = 10^(x-n) = e^(ln(10)*(x-n))
        break;
    case ODE:       // 常微分方程初值问题解方法
        a = exp_ode(LN_TEN * (x - n));
        break;
    case ROOT:
        a = exp_root(LN_TEN * (x - n), TAYLOR);
        break;
    default:
        break;
    }
    return SciNumber(a, n);
}

// 科学计数法 ln(x) 运算
double ln_sci(SciNumber sn, METHOD method)     // 返回值为 浮点数而不是科学计数法，因为 ln(sn) 不会越界
{
    switch (method) {
    case TAYLOR:
        return (LN_TEN * 1.0 * sn.n + ln_taylor(sn.a));
        break;
    case ODE:
        return (LN_TEN * 1.0 * sn.n + ln_ode(sn.a));
        break;
    case INTEGRAL:
        return (LN_TEN * 1.0 * sn.n + ln_integral(sn.a));
        break;
    default:
        return 0;
        break;
    }
}

#endif // FUNCTIONS_CPP
