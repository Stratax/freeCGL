#include<myGraphics.h>

int main(int argc, char *argv[]) {
    color c=newColor(120,18,40);;
    material m1 = newMaterial(c,2);
    model m = loadModel(argv[1],m1,300);
    pushRotateX(-90);
    loadTransformation(m);
    rasterModel(m,FHD,'w',0);
    printPPM(FHD);
    freeModel(m);
    return 0;
}
