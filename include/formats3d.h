#ifndef format_3d
#define  format_3d
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void raw2vlf(char * doc);
int findVertex(float x , float y , float z);
int findEdge(int v1, int v2);

#endif
