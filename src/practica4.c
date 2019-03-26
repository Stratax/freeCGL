#include<myGraphics.h>

int main(int argc, char *argv[]) {
    model m = loadModel(argv[1],500);

    color red, white,black,blue;

    black = newColor(0,0,0);
    red = newColor(255,0,0);
    white = newColor(255,255,255);
    blue = newColor(0,0,255);

    clearRaster(FHD,white);
    rasterReference(FHD,black);

    pushRotateX(-90);
    //pushRotateY(180);
    pushTranslate(25,0,-2000);
    loadTransformation(m);
    projectModel(m,-1500);
    rasterModel(m,FHD,red);
    resetMatrix();
    pushTranslate(-50,0,0);
    loadTransformation(m);
    rasterModel(m,FHD,blue);

    printPPM(FHD);

    freeModel(m);
    return 0;
}
