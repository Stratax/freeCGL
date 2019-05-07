#include<myGraphics.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

    int rot = atoi(argv[2]);
    color c;


    pushRotateZ(rot);
    pushRotateX(rot);
    initZBuffer();

    if(rot <= 90)
        c = newColor(rot+100, 0, 0);
    if(rot <= 180 && rot > 90)
        c = newColor(190,rot-90,0);
    if(rot <=270 && rot > 180)
        c = newColor(190,90,rot-180);
    if(rot > 270)
        c = newColor(260-rot,360-rot,360-rot);

    model m = loadModel(argv[1],c,75);
    loadTransformation(m);
    rasterSolidModelRandom(m,QVGA,1);
    rasterModelNormal(m,QVGA);
    printPPM(QVGA);
    freeModel(m);
    return 0;
}
