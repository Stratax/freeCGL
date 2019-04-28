#include<myGraphics.h>

int main(int argc, char *argv[]) {

    //color c1,c2;
    //c1 = newColor(255,0,0);
    //c2 = newColor(0,0,100);

    model m = loadModel(argv[1],300);
    pushRotateX(-90);
    loadTransformation(m);
    initZBuffer();
    rasterSolidModelRandom(m,FHD,1);
    //rasterReference(FHD,c1,10);

    printPPM(FHD);

    return 0;
}
