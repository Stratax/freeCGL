#include<myGraphics.h>


int main(int argc, char const *argv[]) {

    color c = newColor(255,255,255);
    //color c1 = newColor(255,0,0);
    model m = loadModel("3dModels/ape.vlf",400);
    vector o = newVector(0,-1500,0);
    camera cam1 =newCamera(o,-1500,90,0,0);
    //pushTranslate(0,0,0);
    //pushRotateX(-90);
    //pushRotateY(180);
    loadTransformation(m);
    resetMatrix();
    initZBuffer();
    takePhoto(cam1,m,FHD,c,'r');
    //rasterModel(m,FHD,c1,1);
    rasterSolidModelRandom(m,FHD,1);
    //rasterModel(m,FHD,c1,1);

    printPPM(FHD);
    freeModel(m);
    return 0;
}
