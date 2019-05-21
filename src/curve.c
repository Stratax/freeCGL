#include <myGraphics.h>

int main(int argc, char *argv[]) {

    //The numbers of points is given in the arguments
    vecI v1,v2;
    line l;
    color white = newColor(255,255,255);
    int i,times = atoi(argv[1]);
    float t,x,y,param[4][3] ={{-3,0,0},{3,4,0},{-1,1,0},{-4,3,0}};
    float part = 1.0/times;

    x = (30*param[3][0])-50;
    y = (30*param[3][1])-50;
    v2 = newVecI(x,y,0);

    for(i = 0 ; i <= times ; i++){

        t=i*part;
        x = (t*t*t*param[0][0]) + (t*t*param[1][0]) + t*param[2][0] + param[3][0];
        y = (t*t*t*param[0][1]) + (t*t*param[1][1]) + t*param[2][1] + param[3][1];

        //scaling
        x*=30;
        y*=30;
        x-=50;
        y-=50;

        v1 = newVecI(x,y,0);
        l = newLine(v1,v2);
        // l is a line from v1 to v2
        rasterLine(l,FHD,white,0);
        //Puts in a FHD raster a line 'l' of color white with no Z-buffer (0)
        v2 = v1;
        freeLine(l);
        //printVector(v1);
    }
    printPPM(FHD);
    //print the FHD raster in PPM format
    //Other formats QVGA & HD
    return 0;
}
