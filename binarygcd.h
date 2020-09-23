#include<NTL/ZZ.h>
using namespace NTL;
typedef ZZ num;
// euclides normall !!
num gcd(num a, num b){
  while (a!=b){
    if (a>b)
      a=a-b;
    else
      b=b-a;
  }
  return a;
}

ZZ mov_vit(ZZ a){
    return a >> 1;
}

// uso para validar  si es coprimo la clave publica con el phi(N);
ZZ binaryGCD(ZZ x, ZZ y){
    int g=1;
    ZZ a;
    ZZ t;
    ZZ resultx,resulty;
    t=1;
    a=2;
    while (x!=0){
            bit_and(resultx,x,t);
            bit_and(resulty,y,t);

        if( (resultx==0) && (resulty==0)){
          x=mov_vit(x); y=mov_vit(y); g=g*2;
        }
        if ((resultx==0) && (resulty==1)){
            x=mov_vit(x);
        }
        if ((resultx==1) && (resulty==0)){
            y=mov_vit(y);
        }
        if ((resultx==1)&&(resulty==1)) {
            if (x>=y){
                x=mov_vit(x-y);
            }
            else{
                    //div2
                y=y-x;//div2(y-x);
            }
        }
    }
    return g*y;
}
