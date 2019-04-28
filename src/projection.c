#include<myGraphics.h>

int main(int argc, char *argv[]) {
    model m = loadModel(argv[1],400);

    vector o = newVector(0,0,1500);
    camera cam1 = newCamera(o,1500,0,0,0);
    color white,black;

    black = newColor(0,0,0);
    white = newColor(255,255,255);

    clearRaster(FHD,white);

    pushRotateX(-90);
    loadTransformation(m);
    resetMatrix();

    takePhoto(cam1,m,FHD,black,'s');
    rasterModel(m,FHD,black,0);

    printPPM(FHD);

    freeModel(m);
    freeCamera(cam1);

    return 0;
}
