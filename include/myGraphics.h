#ifndef graphics_b
#define graphics_b

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define PI 3.14159265
    /****************************************/
    /***  Instituto Politécnico Nacional  ****/
    /***   Escuela Superior de Cómputo   ****/
    /***        Computer Graphics        ****/
    /***  López Calderón Adrián Alberto  ****/
    /****************************************/


//vector//
typedef struct {
    int x,y,z;
}vector;

vector newVector(int x, int y, int z);
float magnitudVector(vector v1);
vector crossProduct(vector v1, vector v2);
int dotProduct(vector v1, vector v2);
vector addVector(vector v1, vector v2);
vector restVector(vector v1, vector v2);
void resizeVector(vector * v1, int scale);


//Color
typedef struct{
    unsigned char r,g,b;
}color;
color newColor(unsigned char r, unsigned char g , unsigned char b);

//Raster//
unsigned char rasterQVGA[320][240][3];
unsigned char rasterHD[1280][720][3];
unsigned char rasterFHD[1920][1080][3];
int zBuffer[1920][1080];

typedef enum Resolution{QVGA, HD, FHD}resolution;


void printPPM(resolution res);
void clearRaster(resolution res, color c);
void initZBuffer();

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
    int dx,dy,dz;
    int nPoints;
}Line;

typedef Line *line;

line newLine(vector v1, vector v2);
void rasterLine(line l,resolution res,color c,int buffering);
void freeLine(line l);

//Model
typedef struct{
    vector *vertex;
    vector *normals;
    int edges[10000][2];
    int faces[10000][3];
    int nVertex,nEdges,nFaces,nNormals;
}Model; //VLF fortmat

typedef Model *model;

model newModel(int nVertex);
model loadModel(char* fileName, int scale);
void calculateNormals(model m);
void rasterModel(model m,resolution res, color c, int buffering);
void rasterSolidModel(model m,resolution res,color c,int buffering);
void rasterSolidModelRandom(model m,resolution res,int buffering);
void projectModel(model m, int f);
void freeModel(model m);



void loadTransformation(model m);
void loadTransformationVector(vector *v1);

//Camera
typedef struct{
    vector origin,direction;
    int focus,ang_x,ang_y,ang_z;
    model mC;
}Camera;
typedef Camera * camera;

camera newCamera(vector origin , int focus, int ang_x, int ang_y, int ang_z);
void takePhoto(camera cam,model m,resolution res, color c, char t);
void freeCamera(camera c);


//Miscellaneous//
void swap(int *a, int *b);
int isSameVector(vector v1, vector v2);
vector findFaceVectors(int face, model m);
int findEdge(int v1, int v2,model m);
int findFace(int edge,int face, model m);
int findThe3erVector(int v1,int v2,int face,model m);

//Testing tools//
void printVector(vector v);
void printLine(line l);
void printModel(model m);
void printTrans();
void rasterReference(resolution res, color c, int scale);
void printCamera(camera c);
void rasterCamera(camera c , resolution res);
void rasterNormals(model m,resolution res,color c);

#endif
