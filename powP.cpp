//////////////////////////////////////////////////////////////////////
//                ���Լ�д�ĺ���ʵ��c++��pow()�Ĺ���                //
//                        ���� ��ѧ���ѿ���                         //
//           ˮƽ���ޣ���©�������⣬��ӭ�����������κ������       //
//              ��email����pjy.studio@gmail.com  Thank you!         //
////////////////////////////////////////////////////////////////////// 
#include<iostream>
#include<cmath>
using namespace std;
double pow_i(double num,int n);//����num��n���ݣ�����nΪ����
double pow_f(double num,double m);//����num��m���ݣ�num��m��Ϊ˫���ȣ�num������С��2 
double pow_ff(double num,double m);//����pow_f()��pow_i(),����num��m����,�Ǽ����ݵ����
;
//int main()
//{
//  double num,m;
//  cout<<"�������num��ָ��m:"<<endl;
//  cin>>num>>m;
//  cout<<"c++ 's answer:"<<pow(num,m)<<endl;
//  cout<<"my     answer:"<<pow_ff(num,m)<<endl;
//  }

double pow_i(double num,int n)//����num��n���ݣ�����nΪ���� 
{
   double powint=1;
   int i;
   for(i=1;i<=n;i++) powint*=num;
   return powint;
}
double pow_f(double num,double m)//����num��m���ݣ�num��m��Ϊ˫���ȣ�num������ 
{
    int i,j;
    double powf=0,x,tmpm=1;
    x=num-1;
    for(i=1;tmpm>1e-12 || tmpm<-1e-12;i++)//��tmpm���ڴη�Χʱ��ֹͣѭ��,��Χ�ɸ� 
           {
	       for(j=1,tmpm=1;j<=i;j++) 
	            tmpm*=(m-j+1)*x/j;
	            powf+=tmpm;
           }
    return powf+1;
}
double pow_ff(double num,double m)//����pow_f()��pow_i(),����num��m����,�Ǽ����ݵ����
{
    if(num==0 && m!=0) return 0;//��numΪ0���򷵻�0
	else if(num==0 && m==0) return 1;// ��num��m��Ϊ0���򷵻�1
    else if(num<0 && m-int(m)!=0) return 0;//��numΪ������m��Ϊ�����������������0 
    if(num>2)//�ѵ�������2�����תΪ(1/num)^-m����
	{
	    num=1/num;
		m=-m;
		}
	if(m<0) return 1/pow_ff(num,-m);//��ָ��С��0�����תΪ1/num^-m����
    if(m-int(m)==0) return pow_i(num,m);/*��ָ��Ϊ�������ǣ��ֳ�������С���ֱ���
	                                    �ݣ�������Ϊ��������Сʽ����pow_fֱ������
										�������Է�Ϊָ��������������pow_i,С
										��������pow_f��.*/ 
    else return pow_f(num,m-int(m))*pow_i(num,int(m));
    return pow_f(num,m);
}
