#include "function.cpp"
#include <iostream>

using namespace std;

int main()
{
 Size m;

 int r;
 
 
 int t=100;
 float alpha=0.2;
 float nu=0.0709; // table
 float pg= 1553; // плотность жидкого опасного вещества + table

 float Cp=960; // темплоемкость жидкого опасного вещества + table
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


/* table for different gases!!!!!!!!!!!!!!!!!!!
 * ammiak 
 *     nu   17*10-3 kg/mol`
 *     pg   681 kg/m3
 *     Cp   4590 Dg/kg
 *     Tkip -33.4
 *     dHkip 1360000 Dg/kg
 * fosgen
 *     nu   98.9 *10-3
 *     pg   1420 
 *     Cp   1020  Dg/kg
 *     Tkip 8.2
 *     dHkip 158000
 * xlor
 *     nu 70.9*10-3
 *     pg 1553
 *     Cp  960
 *     Tkip -34.1
 *     dHkip 288000
 * serovodorod
 *     nu 34.1 *10-3
 *     pg 964
 *     Cp 2010
 *     Tkip -60.4
 *     dHkip 310000
 */

/* table for different surfaces
 * 
 *  asphalt
 *      cp = 920
 *      pp = 1100
 *      lp = 0.72
 *  pesok
 *      cp = 840
 *      pp = 1380
 *      lp = 0.97
 *  led
 *      cp = 2080
 *      pp = 920
 *      lp = 2.23
 * beton na kmenom shebne
 *      cp = 1000
 *      pp = 2300
 *      lp = 1.3
 * asbest
 *      cp = 800
 *      pp = 1600
 *      lp = 1.76 
 */
