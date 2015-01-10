/// functions.cpp
/// 宏定义以及各种函数的定义

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>

#define LN_TWO      0.69314718055994530941723212145818     // ln(2)
#define LN_TEN      2.3025850929940456840179914546844      // ln(10)
#define E           2.7182818284590452353602874713527      // 自然对数的底 e
#ifndef ZERO
//#define ZERO 1.0e-300     // 定义零 double 的精度最小数2.22507e-308（10^-308）
#define ZERO 2.5e-308       // 1.0e-230 不会出现显示 1.0e-230 = 10e-231 的问题
#endif

#define STEP        1.0e-5      // 常微分方程初值问题解方法步长 h
#define ERROR_STORE 0.5e-14     // 设定计算过程中，存储误差限，小数点后 14 位
#define ERROR_ANS   0.5e-14     // 计算结果误差限，小数点后 15 位

#define FABS(x) ((x >= 0) ? (x) : (-x))      // 取绝对值
#define FLOOR(x) (x >= 0 || (int(x) - x <= ZERO) ? (int(x)) : (int(x) - 1))   // 向下取整函数

enum METHOD{    // 计算方法
    TAYLOR,     // Taylor 展开
    ODE,        // 常微分方程初值问题解方法
    INTEGRAL,    // 数值积分方法
    ROOT        // 方程求根方法
};

//// 向下取整
//inline int FLOOR(double x)
//{
//    if(x >= 0)
//        return int(x);
//    if(int(x) - x <= ZERO)
//        return int(x);
//    return (int(x) - 1);
//}

/// 科学计数法结构体
struct SciNumber{   // 科学计数法
    double a;   // 浮点数（16位有效数字） 1.0 <= a < 10。0（当且仅当 a == 0 时为零）
    int n;      // 整数
    SciNumber(double a0=0.0, int n0=0)
    {
        a = a0;
        n = n0;
    }
};

/// 科学计数法与字符串之间的转化
//
SciNumber StringtoSci(QString str);

/// 浮点数与科学计数法之间的转化
SciNumber DoubletoSci(double x);    // 浮点数转化为科学计数法
double ScitoDouble(SciNumber sn);   // 科学计数法转化为浮点数

/// getSignificants 从字符串中读取浮点数的有效数字
int getSignificants(QString str);    // 已通过 setValidator 限定 str 为双精度数
int getSignificants(double num);    // getSignificants 从双精度数中读取有效数字
// 科学计数法 power 运算，可以处理任意精度 (1^-99999)^3 = ?
SciNumber power_sci(SciNumber sx, SciNumber sy, METHOD method = TAYLOR);
double power_all(double x, double y, METHOD method = TAYLOR);

// 浮点数的 10 次幂
SciNumber exp10_tosci(double x, METHOD method = TAYLOR);

// 科学计数法 ln(x) 运算
double ln_sci(SciNumber sn, METHOD method = TAYLOR);     // 返回值为 浮点数而不是科学计数法，因为 ln(sn) 不会越界


#endif // FUNCTIONS_H
