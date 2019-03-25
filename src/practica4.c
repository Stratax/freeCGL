#include<myGraphics.h>

int main(int argc, char *argv[]) {
    model m = loadModel(argv[1],300);

    color red, white,black;

    black = newColor(0,0,0);
    red = newColor(255,0,0);
    white = newColor(255,255,255);

    clearRaster(FHD,white);
    pushRotateX(-90);
    pushRotateY(180);
    pushTranslate(0,0,-400);
    loadTransformation(m);
    projectModel(m,200);
    rasterReference(FHD,red);

    rasterModel(m,FHD,black);

    printPPM(FHD);

    freeModel(m);
    return 0;
}
