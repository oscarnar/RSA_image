// gcc -o qr_test qrtest.c -lgd -lqrencode
// para q debuges gcc -g -Wall -o qr_test qrtest.c -lgd -lqrencode
// gdb ./qr_test
//

#include <gd.h>
#include <qrencode.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


gdImagePtr qrcode_png(QRcode *code, int black[3], int white[3], int size, int margen){
    int qr_size = size / code->width;
    qr_size = (qr_size == 0)  ? 1 : qr_size;
    int img_width = code->width * qr_size + 2 * margen;
    gdImagePtr img = gdImageCreate (img_width,img_width);
    int img_black =  gdImageColorAllocate(img,black[0],black[1],black[2]);
    int img_white = gdImageColorAllocate(img,white[0],white[1],white[2]);
    gdImageFill(img,0,0,img_white);
    u_char *p = code->data;
    int x,y ,posx,posy;
    for (y = 0 ; y < code->width ; y++){
        for (x = 0 ; x < code->width ; x++){
            if (*p & 1){
                posx = x * qr_size + margen;
                posy = y * qr_size + margen;
                gdImageFilledRectangle(img,posx,posy,posx + qr_size,posy + qr_size,img_black);
            }
            p++;
        }
    }
    return img;
}

int main (void){
    char * encoded_content = "Hi stranger my name is Oscar Rosas and my CUI is 20162010. Soy estudiante de la Universidad Nacional de San Agustin.";
    int version = 1;
    QRecLevel level = 2;
    QRencodeMode hint = QR_MODE_8;
    int casesensitive =1;
    int white_256 [3] = {255,255,255} ;
    int black_256 [3] = {0,0,0};
    int size = 200;
    int margen = 2;
    FILE * out = fopen("qr_test.png","w+");
    QRcode * code = QRcode_encodeString (encoded_content,version,level,hint,casesensitive);
    gdImagePtr im = qrcode_png(code,black_256,white_256,size,margen) ;
    gdImagePng(im,out);
    QRcode_free (code);
    gdImageDestroy(im);
    fclose(out);
    return 0;
}
