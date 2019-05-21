#include<myGraphics.h>

int main(int argc, char *argv[]) {

    //color c1,c2;
    color c1 = newColor(255,0,0);
    material m1 = newMaterial(c1,2);
    //c2 = newColor(0,0,100);

    model m = loadModel(argv[1],m1,300);
    pushRotateX(-90);
    loadTransformation(m);
    initZBuffer(-100000);
    rasterModel(m,FHD,'s',1);
    printPPM(FHD);

    return 0;
}
