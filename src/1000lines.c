#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<myGraphics.h>

int main(int argc, char const *argv[]) {

    int i = 0;
    vecI p1,p2;
    line l;
    color c,c1;
    c1 = newColor(20,20,20);
    clearRaster(FHD,c1);
    c1 = newColor(120,120,200);
    srand(time(NULL));
    for(i = 0 ; i < 1000; i++ ){
        p1 = newVecI((rand()%1920)-960,(rand()%1080)-540,0);
        p2 = newVecI((rand()%1920)-960,(rand()%1080)-540,0);
        c = randomBaseColor(c1);
        l = newLine(p1,p2);
        rasterLine(l,FHD,c,0);
        freeLine(l);
    }
    printPPM(FHD);
    return 0;
}
