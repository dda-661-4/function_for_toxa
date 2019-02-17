#include "function.cpp"
#include <iostream>

using namespace std;

int main()
{
 Size m;

 int t=100;
 float alpha=0.2;
 float nu=0.0709;
 float pg= 1553; // плотность жидкого опасного вещества +

 float Cp=960; // темплоемкость жидкого опасного вещества +
 float Tkip=-34.1;
 Tkip=273.15+Tkip;
 float dHkip=288000;
 float Tv=273.15+20;
 float Tp=273.15+20;
 float cp=840;
 float pp=1380;
 float lp=0.97;
 int v=1;
 m=function_size(t,alpha,nu,pg,Cp,Tkip,Tv,Tp,cp,pp,lp,v,dHkip);
 
 cout<<m.X_1;
 cout<<m.Y_1;
 
return 0;
}
