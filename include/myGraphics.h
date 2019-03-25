#ifndef graphics_b
#define graphics_b

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define PI 3.14159265
    /****************************************/
    /***  Intituto Ploitécnico Nacional  ****/
    /***   Escuela Superior de Cómputo   ****/
    /***        Computer Graphics        ****/
    /***  López Calderón Adrián Alberto  ****/
    /****************************************/


//vector//
typedef struct {
    int x,y,z;
}vector;
vector newVector(int x, int y, int z);

//Color
typedef struct{
    unsigned char r,g,b;
}color;
color newColor(unsigned char r, unsigned char g , unsigned char b);

//Raster//
unsigned char rasterQVGA[320][240][3];
unsigned char rasterHD[1280][720][3];
unsigned char rasterFHD[1920][1080][3];

typedef enum Resolution{QVGA, HD, FHD}resolution;


void printPPM(resolution res);
void clearRaster(resolution res, color c);

// Transformations
void pushTranslate(int tx, int ty, int tz);
void pushScale(float sx, float sy, float sz);
void pushRotateX(int ang);
void pushRotateY(int ang);
void pushRotateZ(int ang);
void resetMatrix();

//Line//
typedef struct{
    vector *points;
    int dx,dy;
    int nPoints;
}Line;

typedef Line *line;

line newLine(vector v1, vector v2);
void rasterLine(line l,resolution res,color c);
void freeLine(line l);

//Model
typedef struct{
    vector *vertex;
    int edges[10000][2];
    int faces[10000][3];
    int nVertex,nEdges,nFaces;
}Model; //VLF fortmat

typedef Model *model;

model loadModel(char* fileName, int scale);
void rasterModel(model m,resolution res, color c);
void rasterSolidModel(model m,resolution res, color c);
void loadTransformation(model m);
void projectModel(model m, int f);
void freeModel(model m);

//Miscellaneous//
void swap(int *a, int *b);


//Testing tools//
void printVector(vector v);
void printLine(line l);
void printModel(model m);
void printTrans();
void rasterReference(resolution res, color c);

#endif
