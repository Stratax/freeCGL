#ifndef format_3d
#define  format_3d
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void raw2vlf(char * doc);
int findVertex(float x , float y , float z);
int findEdge(int v1, int v2);
void findVertexsFace(int theFace, int v[3]);
int findThe3erdVertex(int theFace,int v1,int v2);
void calculateNormal(float* n ,float* o , float* from, float* to);
int findFaceByEdge(int theFace,int e);
#endif
