#include<myGraphics.h>


int main(int argc, char const *argv[]) {

    color red = newColor(255,0,0);
    color white = newColor(255,255,255);
    model m = loadModel("3dModels/cube.vlf",300);

    pushRotateX(45);
    pushRotateY(45);
    loadTransformation(m);
    resetMatrix();
    initZBuffer();
    rasterModel(m,FHD,white,1);
    rasterNormals(m,FHD,red);

    printPPM(FHD);
    //printModel(m);
    freeModel(m);
    return 0;
}
