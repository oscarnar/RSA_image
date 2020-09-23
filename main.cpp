#include "CImg.h"
#include <iostream>
#include "tools_int.h"
#include <string>
#include "rsa.h"
#include "math.h"

using namespace cimg_library;
using namespace std;
//rgb funcion para sacar pixeles de la imagen foter for img(i,j,0) 0r 1g 2b
string rellenar(int numero){
  string valor=my_to_string(numero);
  string temp;
  int i=valor.size();
  for(;i<3;i++) temp+="0";
  temp+=valor;
  return temp;
}
string sacarpixel(CImg<unsigned char> imagen,int ancho,int alto){
  string pixeles,temp;
  unsigned int r,g,b,promedio;
  for(int i=0;i<ancho;i++){
    for(int j=0;j<alto;j++){
      r=imagen(i,j,0);
      g=imagen(i,j,1);
      b=imagen(i,j,2);
      promedio=(r+g+b)/3;//3;
      temp=rellenar(promedio);//promedio);
      pixeles+=temp;
      /*temp=rellenar(g);
      pixeles+=temp;
      temp=rellenar(b);
      pixeles+=temp;*/
    }
  }
  return pixeles;
}
int rgb(string imagen,int &inicio){
  int i=1,p;
  if(inicio+i>=imagen.size()) return 0;
  else  p=string_to_int(imagen.substr(inicio,i));
  while(taman(p)<=2){//p<256
    i++;
    if(inicio+i>=imagen.size()) break;
    else  p=string_to_int(imagen.substr(inicio,i));
  }
  inicio+=i;
  return p;
}
int rgb_armar(string imagen,int &inicio){
  if(inicio+3>=imagen.size()) return 0;
  int p=string_to_int(imagen.substr(inicio,3));
  if(p>256){
    if(inicio+2>=imagen.size()) return 0;
    p=string_to_int(imagen.substr(inicio,2));
    inicio+=2;
  }
  inicio+=3;
  return p;
}
int rgb_(string imagen,int &inicio){
  int i=1,p;
  if(inicio+i>=imagen.size()) return 0;
  else  p=string_to_int(imagen.substr(inicio,i));
  while(p<256 || taman(p)<3){
    i++;
    if(inicio+i>=imagen.size()) break;
    else  p=string_to_int(imagen.substr(inicio,i));
  }
  inicio+=i;
  return p;
}
//armar imagen cifrada pero cuadrada
CImg<unsigned int> imagencifrada(string imagen,int &v_max){
/*int minimo=v_max;
  int tam=minimo*minimo;
  while(tam<= (imagen.size())){
    minimo++;
    tam=minimo*minimo;
  }*/
  int minimo=v_max;
  int total=imagen.size();
  int inicio=0,temp;
  CImg<unsigned int> imag(minimo,minimo,1,1);
  for(int i=0;i<minimo;i++){
    for(int j=0;j<minimo;j++){
      temp=rgb(imagen,inicio);
      imag(i,j)=temp;
      if(inicio>=total) break;
    }
  }
  v_max=minimo;
  return imag;
}
CImg<unsigned int> armar(string imagen,int ancho,int alto){
  CImg<unsigned int> imag(ancho,alto,1,1);
  int inicio=0,temp;
  for(int i=0;i<ancho;i++){
    for(int j=0;j<alto;j++){
      temp=rgb_armar(imagen,inicio);
      imag(i,j)=temp;
      /*temp=rgb_armar(imagen,inicio);
      imag(i,j,1)=temp;
      temp=rgb_armar(imagen,inicio);
      imag(i,j,2)=temp;*/
    }
  }
  return imag;
}

int main() {
    //string name;
    //cout<<"Ingrese nombre: ";
    //cin>>name;
  CImg<unsigned int> img("lena.png");//img(256,256,1,3);
  int ancho,alto;
  alto=img.height();
  ancho=img.width();
  /*string x=sacarpixel(img,ancho,alto);
  for(int i=0;i<x.size();i++){
    x[i]=x[i]+50;
  }
  CImg<unsigned int> y=armar(x,ancho,alto);
  y.display();
  x=sacarpixel(y,ancho,alto);
  y=armar(x,ancho,alto);
  y.display();*/

  //cifrado
  string pixeles=sacarpixel(img,ancho,alto);
  CImg<unsigned int> nuevo;//(ancho,alto,1,3,0);
  img.display();
  cout<<"tam original: "<<pixeles.size()<<endl;
  RSA a(20);
	string cifrado= a.cifrar(pixeles);
  cout<<"tam cifrado: "<<cifrado.size()<<endl;
  int max=ancho;
  if(ancho<alto)  max=alto;
  max=max;

  nuevo=imagencifrada(cifrado,max);
  nuevo.display();
  max=nuevo.height();

  //descifrar
  string pixdes=sacarpixel(nuevo,max,max);
  cout<<"tam imagen cifra: "<<pixdes.size()<<endl;

	string descifrado=a.descifra_mensaje(cifrado);
  cout<<"tam desci: "<<descifrado.size()<<endl;
  CImg<unsigned int> d;
  d=armar(descifrado,ancho,alto);
  d.display();

  ///////////////////////
}
