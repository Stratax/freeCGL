#include<myGraphics.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

    int rot = atoi(argv[2]);
    color c;
    model m = loadModel(argv[1],100);

    pushRotateZ(180+rot);
    pushRotateX(90+rot);
    //pushTranslate(0,0,-300);
    //pushTranslate(0,0,-120);
    loadTransformation(m);
    //projectModel(m,-200);
    //projectModel(m,-50);


    if(rot <= 90)
        c = newColor(rot+100, 0, 0);
    if(rot <= 180 && rot > 90)
        c = newColor(190,rot-90,0);
    if(rot <=270 && rot > 180)
        c = newColor(190,90,rot-180);
    if(rot > 270)
        c = newColor(260-rot,360-rot,360-rot);

    rasterModel(m,QVGA,c);
    printPPM(QVGA);
    freeModel(m);
    return 0;
}
