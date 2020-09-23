#ifndef TOOLS_INCLUDED
#define TOOLS_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
//#include <NTL/ZZ.h>
//using namespace NTL;
int euclides(int a,int b){
  int r1=a,r2=b;
  while(r2>0){
    int q=r1/r2;
    int r=r1-q*r2;
    r1=r2;
    r2=r;
  }
  return r1;
}
void euclides_extendido(int &r1,int r2,int &s1,int &t1){
   int q , r;
   int s,s2, t, t2;
   s1 = 1;
   s2 = 0;
   t1 = 0;
   t2 = 1;

   while(r2 > 0){
      q = r1/r2;

      r = r1 - ((r2 < 0)? --q:q) * r2;
      r1 = r2;
      r2 = r;

      s = s1 - q * s2;
      s1 = s2;
      s2 = s;

      t = t1 - q * t2;
      t1 = t2;
      t2 = t;
   }
}
int mod(int a,int b){
    if(b<0){
        //cout<<"B no puede ser negativo.";
        return -1;
    }
    if(a==0)    return 0;
    if(a<b && a>0){
        return a;
    }
    /*if(a<2*b-1 && a>=b){
        return a-b;
    }*/
    if(a>=b){
        int temp=a-b;
        while(temp>=b){
            temp-=b;
        }
        return temp;
    }
    if(a<0){
        int temp=(a*(-1));
        if(temp<b){
            return a+b;
        }
        while(temp>=b){
            temp-=b;
        }
        if(temp==0){
            return 0;
        }
        return b-temp;
    }
};
int inversa(int x,int y){
    int a,b;
    euclides_extendido(x,y,a,b);
    if(a<0){
        a=mod(a,y);
    }
    return a;
}

int exp_mod(long x, int k, int n){
    int acumulador=1;
    while(k!=0){
        if(mod(k,2)==1){
            acumulador=acumulador*x;
            acumulador=mod(acumulador,n);
        }
        x=mod(x*x,n);
        k=k/2;
    }
    return acumulador;
}
int chino(int *a, int *p, int n) {
  int P=1;
  for (int i = 0; i < n; ++i)
    P *= p[i];
  int inv_temp, p_temp, final_sol=0;
  for (int i = 0; i < n; ++i) {
    p_temp = P/p[i];
    inv_temp = inversa(p_temp, p[i]);
    final_sol += mod(a[i] * inv_temp * p_temp, P);
  }
  return mod(final_sol, P);
}
int resto(vector<int> a, vector<int> p){
    int x=0;
    int ptotal=1;
    for(int i=0;i<p.size();i++){
        ptotal=ptotal*p[i];
    }
    for(int i=0;i<p.size();i++){
        int xo,q,p1;
        p1=ptotal/p[i];
        q=inversa(p1,p[i]);
        xo=a[i]*p1*q;
        xo=mod(xo,ptotal);
        x+=xo;
    }
    return mod(x,ptotal);
}
int taman(int n){
  stringstream temp;
  temp<<n;
  string s=temp.str();
  return s.size();
}
//convierte un entero a string
string my_to_string(int n){
  stringstream temp;
  temp<<n;
  string s=temp.str();
  return s;
}

//n es el tamaño del alfabeto
string convertir(vector<int> cade,int n){
  string cadena,temp;
  //int tam=taman(n);
  for(int i=0;i<cade.size();i++){
    stringstream s;
    s<<cade[i];
    int falta=n-taman(cade[i]);
    for(int i=0;i<falta;i++){
      cadena+="0";
    }
    cadena+=s.str();
  }
  return cadena;
}
//str.substr(0,2)
vector<int> div(string cade,int n){
  vector<int> v;
  for(int i=0;i<cade.size();i+=n){
    string temp=cade.substr(i,n);
    while(temp.size()<n){
      temp+="9";
    }
    v.push_back(atoi(temp.c_str()));
  }
  return v;
}
int string_to_int(string n){
    stringstream s;
    s<<n;
    string temp=s.str();
    return atoi(temp.c_str());
}
#endif // TOOLS_INCLUDED
