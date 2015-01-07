#include "arbpower.h"
#include <QApplication>
#include <QDebug>
//#include "functions.cpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string multiWithChar(string a,char b);
string multiWithString(string a,string b);
string addWithString(string a,string b);
int getPointNum(string a,int r);
string deletePoint(string);
string deleteInsignificant(string);
string Exponentiation(string,int);
string recoverPoint(string,int);
string solve(string,int);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArbPower w;
    w.show();

    string s;
    int n;
//    cout << "please input:";
//    cin >> s >> n;
    s = "101.1";
    n = 2.37;
    cout << solve(s, n) << endl;
//    while(cin>>s>>n)
//    {
//        cout<<solve(s,n)<<endl;

//    }
//    system("pause");
//    return 0;
    return a.exec();
}

string solve(string a, int r)
{

    int pointnum=getPointNum(a,r);
    return deleteInsignificant(recoverPoint(Exponentiation(deletePoint(a),r),pointnum));
}
string multiWithChar(string a,char b_)
{
    int len=a.length();
    int up=0;
    int b=b_-'0';
    string ret="";
    for (int i=len-1;i>=0;i--)
    {
        int w=(a.at(i)-'0')*b;
        ret.append(1,(up+w)%10+'0');
        up=(w+up)/10;
    }
    if(up!=0)
    ret.append(1,up+'0');
    std::reverse(ret.begin(),ret.end());
    return ret;
}
string multiWithString(string a,string b)
{

    string ret="";
    int appnum=0;
    for (int i=b.length()-1;i>=0;i--)
    {
        string temp=multiWithChar(a,b.at(i));
        temp.append(appnum++,'0');
        ret=addWithString(ret,temp);

    }
    return ret;
}
string addWithString(string a,string b)
{

    if(a=="")return b;
    if(b=="")return a;
    string temp;
    if(a.length()<b.length()){
        temp=a;
        a=b;
        b=temp;
    }
    int maxlen=a.length();
    int minlen=b.length();
    int up=0;
    string ret="";
    for (int i=maxlen-1,j=minlen-1;i>=0;i--,j--)
    {

        int w=((j<0)?0:(b.at(j)-'0'))+(a.at(i)-'0');
        ret.append(1,(up+w)%10+'0');
        up=(w+up)/10;
    }

    if(up!=0)
    ret.append(1,up+'0');
    std::reverse(ret.begin(),ret.end());
    return ret;
}
int getPointNum(string a,int r)
{
    int pos=a.find('.');
    if(pos==-1)return 0;
    return (a.length()-1-pos)*r;

}
string deletePoint(string s)
{
    int pos=s.find('.');
    if(-1==pos)return s;
    return s.substr(0,pos).append(s.substr(pos+1));
}
string deleteInsignificant(string s)
{
    if(s.find('.')==-1)return s;
    int i=s.length();

    while (s.at(i-1)=='0')
    {
        i--;

    }
    if(s.at(i-1)=='.')i--;
    if(s.at(0)=='0')s=s.substr(1,i);
    return s.substr(0,i);
}
string Exponentiation(string r,int n)
{
    string ret="";
    if(n==1)return r;
    if(n==2)
    {
        return multiWithString(r,r);
    }
    else if(n%2==0)
    {
        return Exponentiation(Exponentiation(r,2),n/2);
    }
    else
    {
        return multiWithString(r,Exponentiation(r,n-1));
    }


}
string recoverPoint(string s,int pointnums)
{
    if(!pointnums)return s;
    s=s.insert(s.length()-pointnums,".");
    return s;
}
