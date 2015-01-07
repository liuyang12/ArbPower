//////////////////////////////////////////////////////////////////////
//                用自己写的函数实现c++的pow()的功能                //
//                        制作 初学者蒲骏逸                         //
//           水平有限，错漏在所难免，欢迎交流，如有任何意见，       //
//              请email到：pjy.studio@gmail.com  Thank you!         //
////////////////////////////////////////////////////////////////////// 
#include<iostream>
#include<cmath>
using namespace std;
double pow_i(double num,int n);//计算num的n次幂，其中n为整数
double pow_f(double num,double m);//计算num的m次幂，num和m可为双精度，num大于零小于2 
double pow_ff(double num,double m);//调用pow_f()和pow_i(),计算num的m次幂,是计算幂的入口
;
//int main()
//{
//  double num,m;
//  cout<<"输入底数num和指数m:"<<endl;
//  cin>>num>>m;
//  cout<<"c++ 's answer:"<<pow(num,m)<<endl;
//  cout<<"my     answer:"<<pow_ff(num,m)<<endl;
//  }

double pow_i(double num,int n)//计算num的n次幂，其中n为整数 
{
   double powint=1;
   int i;
   for(i=1;i<=n;i++) powint*=num;
   return powint;
}
double pow_f(double num,double m)//计算num的m次幂，num和m可为双精度，num大于零 
{
    int i,j;
    double powf=0,x,tmpm=1;
    x=num-1;
    for(i=1;tmpm>1e-12 || tmpm<-1e-12;i++)//当tmpm不在次范围时，停止循环,范围可改 
           {
	       for(j=1,tmpm=1;j<=i;j++) 
	            tmpm*=(m-j+1)*x/j;
	            powf+=tmpm;
           }
    return powf+1;
}
double pow_ff(double num,double m)//调用pow_f()和pow_i(),计算num的m次幂,是计算幂的入口
{
    if(num==0 && m!=0) return 0;//若num为0，则返回0
	else if(num==0 && m==0) return 1;// 若num和m都为0，则返回1
    else if(num<0 && m-int(m)!=0) return 0;//若num为负，且m不为整数数，则出错，返回0 
    if(num>2)//把底数大于2的情况转为(1/num)^-m计算
	{
	    num=1/num;
		m=-m;
		}
	if(m<0) return 1/pow_ff(num,-m);//把指数小于0的情况转为1/num^-m计算
    if(m-int(m)==0) return pow_i(num,m);/*当指数为浮点数是，分成整数和小数分别求
	                                    幂，这是因为但底数较小式，用pow_f直接求幂
										误差大，所以分为指数的整数部分用pow_i,小
										数部分用pow_f求.*/ 
    else return pow_f(num,m-int(m))*pow_i(num,int(m));
    return pow_f(num,m);
}
