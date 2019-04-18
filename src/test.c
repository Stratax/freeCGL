#include<myGraphics.h>

int main(int argc, char const *argv[]) {

    color white = newColor(255,255,255);
    color blue = newColor(0,0,255);
    vector o = newVector(-200,200,300);
    camera c = newCamera(o,1000,30,150,0);
    model m = loadModel("3dModels/ape.vlf",100);
    pushRotateX(-90);
    pushRotateY(180);
    loadTransformation(m);
    resetMatrix();
    //rasterModel(m,FHD,white);
    //seeCamera(c,FHD);
    takePhoto(c,m,FHD,white);
    freeCamera(c);
    freeModel(m);
    //rasterReference(FHD,blue,20);

    printPPM(FHD);
    return 0;
}
