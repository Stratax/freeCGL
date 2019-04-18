#include<myGraphics.h>

int main(int argc, char *argv[]) {
    model m = loadModel(argv[1],400);

    color red,white,black,blue;

    black = newColor(0,0,0);
    red = newColor(255,0,0);
    white = newColor(255,255,255);
    blue = newColor(0,0,255);

    clearRaster(FHD,white);

    pushRotateX(-90);
    pushTranslate(0,0,-3000);
    loadTransformation(m);
    rasterModel(m,FHD,black);

    printPPM(FHD);

    freeModel(m);
    
    return 0;
}
