#include<myGraphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[]) {
    color c;
    model m = loadModel(argv[1],300);
    pushRotateX(-90);
    loadTransformation(m);
    c  = newColor(120,18,40);
    rasterModel(m,FHD,c);
    printPPM(FHD);
    freeModel(m);
    return 0;
}
