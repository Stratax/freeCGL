#include<myGraphics.h>

int main(int argc, char *argv[]) {

    color c, c1,c2;
    c = newColor(0,255,0);

    c1 = newColor(255,0,0);

    c2 = newColor(0,0,100);

    model m = loadModel(argv[1],300);
    pushRotateX(-90);
    //pushTranslate(0,0,-300);
    loadTransformation(m);
    //projectModel(m,100);
    rasterSolidModel(m,FHD,c2);
    rasterModel(m,FHD,c);
    rasterReference(FHD,c1);

    printPPM(FHD);

    return 0;
}
