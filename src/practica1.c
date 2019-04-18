#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<myGraphics.h>

int main(int argc, char const *argv[]) {

    int i = 0;
    vector p1,p2;
    line l;
    color c,c1;
    c1 = newColor(20,20,20);
    clearRaster(FHD,c1);
    srand(time(NULL));
    for(i = 0 ; i < 1000; i++ ){
        p1 = newVector((rand()%1920)-960,(rand()%1080)-540,0);
        p2 = newVector((rand()%1920)-960,(rand()%1080)-540,0);
        c = newColor(rand()%255,rand()%255,rand()%255);
        l = newLine(p1,p2);
        rasterLine(l,FHD,c);
        freeLine(l);
    }
    printPPM(FHD);
    return 0;
}
