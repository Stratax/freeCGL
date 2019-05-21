#include<myGraphics.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

    int rot = atoi(argv[2]);
    initZBuffer(-100000);
    color white;
    white = newColor(255,255,255);

    material mat = newMaterial(white,2);
    model m1 = loadModel(argv[1],mat,200);
    model m2 = loadModel(argv[1],mat,200);

    vecI o1 = newVecI(50,0,700);
    vecI o2 = newVecI(-50,0,700);
    camera cam1 = newCamera(o1,550,0,0,0);
    camera cam2 = newCamera(o2,550,0,0,0);

    pushRotateX(-90+rot);
    pushRotateZ(rot);
    loadTransformation(m1);
    loadTransformation(m2);
    resetMatrix();

    takePhoto(cam1,m1);
    takePhoto(cam2,m2);

    pushTranslate((960/4),0,0);
    loadTransformation(m1);
    resetMatrix();

    pushTranslate(-(960/4),0,0);
    loadTransformation(m2);
    resetMatrix();


    rasterModel(m1,VR,'r',1);
    rasterModel(m2,VR,'r',1);
    printPPM(VR);

    freeModel(m1);
    freeModel(m2);
    freeCamera(cam1);
    freeCamera(cam2);
    return 0;
}
