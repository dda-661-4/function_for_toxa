//#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Size
{
    int X_1;
    int Y_1;
};

float Qg(float alpha,float nu,int P3,float T3,float Rgp,float V3);
float Q_liquid(float V3,float pg);
float Q_GmassaGazaVoborud(float Q_LIQUID,float Cp,float T3,float Tkip,float dHkip);
float S_PROLIVA(float Q_LIQUID,float QG3,float pg,float Qg3);
float Pn(float dHkip,float Tkip,float Tpriv,float Rgp,float nu);
float t_kip(float Tp,float Tkip,float dHkip,float lp,float cp,float pp,float F,int v,float nu,float PN);
float Qi3(float Tp,float Tkip,float dHkip,float lp,float cp,float pp,float F,float Q_LIQUID,float Qg3,float QG3,float T_KIP);
float PI3(float nu,float Rgp,float Tkip,int P0);
float Pvib3(float pi3,float Qg3,float QI3,float QG,float Q3);
float R3(float Q3,float pvib3);
float SIGMA_X(float C3,int X);
float GX(float A1,float A2,float B1,float B2,int X);
float FX(float C1,int X,float D1,float C2,float D2);
float G3(int X,int v,float sigmaX,int Y,float sigmaZ,int t);
float CL(float r3,float sigmaX,float sigmaZ,float g3,float Q3);

Size function_size(int t,float alpha,float nu,float pg,float Cp,float Tkip,float Tv,float Tp,float cp,float pp,float lp,int v,float dHkip)
{
 //int t=100; // время после выброса

 //float alpha;//=0.2; // % газа в емкости   +
 //float nu=0.0709; // мол. масса газа    +
 int P3=8*101325; // давление в емкости
 float T3=20; // t хлора 
 T3=20+273.15;
 float Rgp=8.3144; // универсальная газовая постоянная
 float V3=0.1; // объем 

 //float pg= 1553; // плотность жидкого опасного вещества +

 //float Cp=960; // темплоемкость жидкого опасного вещества +
 //float Tkip=-34.1; //температура кипения +
 //Tkip=273.15+Tkip;
 //float dHkip;//=288000; // теплота испарения жидкого опасного вещества +

 //float Tv=273.15+20; // t водуха +
 //Tv=Tv+273.15;
 float Tproliv=Tkip;

 //float Tp=273.15+20; // t почвы +
// Tp=Tp+273.15;
 //float cp=840; // теплоемкость подстилающей поверхности +
 //float pp=1380; // плотность материала подстилающей поверхности +
 //float lp=0.97; // коэффициент теплопроводности подстилающей поверхности +
 //int v=10; // скорость ветра +

 int P0=101325; // нормальное давление

 // ////////////////////////////////////////
 float C3=0.06;
 float C1=1.56;
 float C2=0.000625;

 float A1=0.0609;
 float A2=0.00196;

 float B1=0.895;
 float B2=0.684;

 float D1=0.048;
 float D2=0.45;

 int X=0; // coord +
 int Y=0; // coord +
 float cl = 0;
 // ///////////////////////////////////////
 do
 {
    X = X + 1;
    float QG=Qg(alpha,nu,P3,T3,Rgp,V3); // расчет массы газа(фаза)    Qг
    float Q_LIQUID=Q_liquid(V3,pg); // QЖ
    float Qg3=Q_GmassaGazaVoborud(Q_LIQUID,Cp,T3,Tkip,dHkip); //Qг3
    float QG3=min(Qg3,Q_LIQUID-Qg3); // масса переход в газ фазу Qж3
    float F=S_PROLIVA(Q_LIQUID,QG3,pg,Qg3); // S площадь пролива
    float Tpriv=max(Tv,Tproliv);
    float PN=Pn(dHkip,Tkip,Tpriv,Rgp, nu); // давление насыщен. пара опасн. вещ. при t возд.
    float T_KIP=t_kip( Tp, Tkip, dHkip, lp, cp, pp, F, v, nu, PN);
    float QI3=Qi3(Tp, Tkip, dHkip, lp, cp, pp, F, Q_LIQUID, Qg3, QG3, T_KIP);// масса испарения за время испарения 0.34???
    float Q3=Qg3+QG3+QI3+QG; // общая масса в облаке
    float pi3=PI3(nu,Rgp,Tkip,P0); // плотность газовой фазы == pkip
    float pvib3=Pvib3(pi3,Qg3,QI3,QG,Q3);
    float r3=R3(Q3,pvib3); // radius prime cloud
    float sigmaX=SIGMA_X(C3,X); // ДИСПЕРСИЯ В ДОЛЬ ОСИ X sigmax==sigmay
    float gX=GX(A1,A2,B1,B2,X); //
    float fX=FX(C1,X,D1,C2,D2); //
    float sigmaZ=fX*gX; //

    float g3=G3(X,v,sigmaX,Y,sigmaZ,t);

    cl=CL(r3,sigmaX,sigmaZ,g3,Q3);

 }
 while (cl<0.0000001);
 int x1=X;
 //cout<<cl<<" "<<x1;
 do
 {
    X=X + 1;
    float QG=Qg(alpha,nu,P3,T3,Rgp,V3); // расчет массы газа(фаза)    Qг
    float Q_LIQUID=Q_liquid(V3,pg); // QЖ
    float Qg3=Q_GmassaGazaVoborud(Q_LIQUID,Cp,T3,Tkip,dHkip); //Qг3
    float QG3=min(Qg3,Q_LIQUID-Qg3); // масса переход в газ фазу Qж3
    float F=S_PROLIVA(Q_LIQUID,QG3,pg,Qg3); // S площадь пролива
    float Tpriv=max(Tv,Tproliv);
    float PN=Pn(dHkip,Tkip,Tpriv,Rgp, nu); // давление насыщен. пара опасн. вещ. при t возд.
    float T_KIP=t_kip( Tp, Tkip, dHkip, lp, cp, pp, F, v, nu, PN);
    float QI3=Qi3(Tp, Tkip, dHkip, lp, cp, pp, F, Q_LIQUID, Qg3, QG3, T_KIP);// масса испарения за время испарения 0.34???
    float Q3=Qg3+QG3+QI3+QG; // общая масса в облаке
    float pi3=PI3(nu,Rgp,Tkip,P0); // плотность газовой фазы == pkip
    float pvib3=Pvib3(pi3,Qg3,QI3,QG,Q3);
    float r3=R3(Q3,pvib3); // radius prime cloud
    float sigmaX=SIGMA_X(C3,X); // ДИСПЕРСИЯ В ДОЛЬ ОСИ X sigmax==sigmay
    float gX=GX(A1,A2,B1,B2,X); //
    float fX=FX(C1,X,D1,C2,D2); //
    float sigmaZ=fX*gX; //

    float g3=G3(X,v,sigmaX,Y,sigmaZ,t);

    cl=CL(r3,sigmaX,sigmaZ,g3,Q3);

 }
 while (cl>=0.0000001);
 int x2=X;
 //cout<<" "<<cl<<" "<<x2;
 int lenght=x2-x1;
 X=lenght/2+x1;
 do
 {
    Y = Y + 1;
    float QG=Qg(alpha,nu,P3,T3,Rgp,V3); // расчет массы газа(фаза)    Qг
    float Q_LIQUID=Q_liquid(V3,pg); // QЖ
    float Qg3=Q_GmassaGazaVoborud(Q_LIQUID,Cp,T3,Tkip,dHkip); //Qг3
    float QG3=min(Qg3,Q_LIQUID-Qg3); // масса переход в газ фазу Qж3
    float F=S_PROLIVA(Q_LIQUID,QG3,pg,Qg3); // S площадь пролива
    float Tpriv=max(Tv,Tproliv);
    float PN=Pn(dHkip,Tkip,Tpriv,Rgp, nu); // давление насыщен. пара опасн. вещ. при t возд.
    float T_KIP=t_kip( Tp, Tkip, dHkip, lp, cp, pp, F, v, nu, PN);
    float QI3=Qi3(Tp, Tkip, dHkip, lp, cp, pp, F, Q_LIQUID, Qg3, QG3, T_KIP);// масса испарения за время испарения 0.34???
    float Q3=Qg3+QG3+QI3+QG; // общая масса в облаке
    float pi3=PI3(nu,Rgp,Tkip,P0); // плотность газовой фазы == pkip
    float pvib3=Pvib3(pi3,Qg3,QI3,QG,Q3);
    float r3=R3(Q3,pvib3); // radius prime cloud
    float sigmaX=SIGMA_X(C3,X); // ДИСПЕРСИЯ В ДОЛЬ ОСИ X sigmax==sigmay
    float gX=GX(A1,A2,B1,B2,X); //
    float fX=FX(C1,X,D1,C2,D2); //
    float sigmaZ=fX*gX; //

    float g3=G3(X,v,sigmaX,Y,sigmaZ,t);

    cl=CL(r3,sigmaX,sigmaZ,g3,Q3);

 }
 while (cl>=0.0000001);
    int height=Y;
    //cout<<" "<<cl<<" "<<height;

 Size m;
    m.X_1=lenght;
    m.Y_1=height*2;
    
 //cout<<QG<<endl<<Q_LIQUID<<endl<<Qg3<<endl<<Q3<<endl<<QI3;
    return m;
}

float Qg(float alpha, float nu, int P3, float T3, float Rgp, float V3)
{
    float a=alpha*nu*V3*P3;
    a=a/Rgp;
    a=a/T3;
    return a;
}
float Q_liquid(float V3, float pg)
{
    float a=V3*pg*0.8;
    return a;
}
float Q_GmassaGazaVoborud(float Q_LIQUID, float Cp, float T3, float Tkip, float dHkip)
{
   float a= T3-Tkip;
   float b=fabs(T3-Tkip);
   a=a+b;
   a=a*Cp;
   a=a/dHkip;
   a=a/-2;
   a=exp(a);
   a=1-a;
   a=Q_LIQUID*a;
   return a;
}
float S_PROLIVA(float Q_LIQUID, float QG3, float pg, float Qg3)
{
   float a=Q_LIQUID-Qg3-QG3;

    a=a/0.05;
    a=a/pg;
    return a;
}
float Pn(float dHkip, float Tkip, float Tpriv, float Rgp, float nu)
{
    float a=1/Tkip;
    float b=1/Tpriv;
    a=a-b;
    a=a/Rgp;
    a=nu*a;
    a=a*dHkip;
    a=exp(a);
    a=a*760;
    return a;
}
float t_kip(float Tp, float Tkip, float dHkip, float lp, float cp, float pp, float F, int v, float nu, float PN)
{
    float b=sqrt(F);
    b=b*2;
    b=b/v;
    b=sqrt(b);

    float a=Tp-Tkip;
    float c=fabs(Tp-Tkip);
    a=a+c;
    a=a/2;
    a=a/dHkip;

    c=lp*cp*pp/3.14;
    c=sqrt(c);
    a=a*c;

    c=1000000/sqrt(nu);
    c=c/PN;
    float d=4.1*v;
    d=d+5.83;
    c=c/d;
    a=a*c;

    c=F/F;
    a=a*c;

    float e=min(a,b);
   // cout<<e;
    return e;
}
float Qi3(float Tp, float Tkip, float dHkip, float lp, float cp, float pp, float F, float Q_LIQUID, float Qg3, float QG3,float T_KIP)
{
    float b=Q_LIQUID-Qg3-QG3;
    float a=Tp-Tkip;
    float c=fabs(Tp-Tkip);
    a=a+c;
    a=a/dHkip;
    c=lp*cp*pp;
    c=c/3.14342342;
    c=sqrt(c);
    a=a*c;
    c=F*F;
    c=c/F;
    c=c*T_KIP;
    a=a*c;

    float e=min(a,b);

    return e;
}
float PI3(float nu, float Rgp, float Tkip, int P0)
{
    float a= nu*P0;
    a=a/Rgp;
    a=a/Tkip;
    return a;
}
float Pvib3(float pi3, float Qg3, float QI3, float QG, float Q3)
{
    float a=pi3*Q3;
    float b=Qg3+QI3+QG;
    a=a/b;
    return a;
}
float R3(float Q3, float pvib3)
{
    float a= 3*Q3;
    a=a/4;
    a=a/3.14;
    a=a/pvib3;
    a=pow(a,0.3333);
    return a;
}
float SIGMA_X(float C3, int X)
{
    float a=C3*X;
    float b=0.0001*X;
    b=b+1;
    b=pow(b,0.5);
    a=a/b;
    return a;
}
float GX(float A1, float A2, float B1, float B2, int X)
{
    float a=A1*pow(X,B1);
    float b=A2*pow(X,B2);
    b=b+1;
    a=a/b;
    return a;
}
float FX(float C1, int X, float D1, float C2, float D2)
{
    float a= C1 * pow(X,D1);
    float b= C2 * pow(X,D2);
    b=b+1;
    a=a/b;
    a=log(a);
    return a;
}
float G3(int X, int v, float sigmaX, int Y, float sigmaZ,int t)
{
   float a=v*t;
    a=X-a;
    a=a*a;
    a=a/-2;
    a=a/(sigmaX*sigmaX);
    float b=Y*Y;
    b=b/-2;
    b=b/(sigmaX*sigmaX);
    a=a+b;
    a=exp(a);
    b=-2/(sigmaZ*sigmaZ);
    b=exp(b);
    b=1+b;
    a=a*b;
     //cout<<a;
    return a;
}
float CL(float r3, float sigmaX, float sigmaZ, float g3, float Q3)
{
 float a=8/3;
 a=a*3.14;
 a=a*r3*r3*r3;

 float b=2*3.14;
 b=pow(b,1.5);
 b=b*sigmaX*sigmaX*sigmaZ;
 a=a+b;
 a=Q3/a;
 a=a*g3;

 return a;
}
