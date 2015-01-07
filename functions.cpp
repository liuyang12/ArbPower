/// functions.cpp
/// 各种函数的实现
///
///
///
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include <QStringList>
#include "functions.h"

/// 科学计数法与字符串之间的转化
// 已通过 setValidator 限定 str 为双精度数
SciNumber StringtoSci(QString str)
{
    // 在 'e' 前后作分割
    QStringList strlist = str.split('e');
    if(strlist.size() < 2)  // 不是科学计数法
        return DoubletoSci(str.toDouble()); // 先转化为 double 型在再进行运算转化为科学计数法，其中 str 支持科学计数法 0.1234e3
    else    // 是科学计数法 strlist[0] strlist[1] 分别是浮点数和指数
        return SciNumber(strlist[0].toDouble(), strlist[1].toInt());
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

#endif // FUNCTIONS_CPP
