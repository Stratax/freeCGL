#include<myGraphics.h>

//------------------------------------Transformations------------------------------------------//

float generalMT[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
float normalsMT[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

void pushTranslate(int tx, int ty, int tz){
    int i,j;
    float r[4][4];
    float m[4][4] = {{1,0,0,tx},
                     {0,1,0,ty},
                     {0,0,1,tz},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];

        }
    }
}
void pushScale(float sx, float sy, float sz){
    int i,j;
    float r[4][4];
    float m[4][4] = {{sx,0,0,0},
                     {0,sy,0,0},
                     {0,0,sz,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];

        }
    }
}
void pushRotateX(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4],rn[4][4];
    float m[4][4] = {{1,0,0,0},
                     {0,c,-s,0},
                     {0,s,c,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
            rn[i][j] = (m[i][0]*normalsMT[0][j])+ (m[i][1]*normalsMT[1][j])+ (m[i][2]*normalsMT[2][j])+ (m[i][3]*normalsMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];
            normalsMT[i][j] = rn[i][j];

        }
    }

}
void pushRotateY(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4],rn[4][4];
    float m[4][4] = {{c,0,s,0},
                     {0,1,0,0},
                     {-s,0,c,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
            rn[i][j] = (m[i][0]*normalsMT[0][j])+ (m[i][1]*normalsMT[1][j])+ (m[i][2]*normalsMT[2][j])+ (m[i][3]*normalsMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];
            normalsMT[i][j] = rn[i][j];
        }
    }

}
void pushRotateZ(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4],rn[4][4];
    float m[4][4] = {{c,-s,0,0},
                     {s,c,0,0},
                     {0,0,1,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
            rn[i][j] = (m[i][0]*normalsMT[0][j])+ (m[i][1]*normalsMT[1][j])+ (m[i][2]*normalsMT[2][j])+ (m[i][3]*normalsMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];
            normalsMT[i][j] = rn[i][j];
        }
    }

}
void projection(int focus){
    int i,j;
    float r[4][4];
    float m[4][4] = {{1,0,0,0},
                     {0,1,0,0},
                     {0,0,1,0},
                     {0,0,-(1.0/focus),0}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*generalMT[0][j])+ (m[i][1]*generalMT[1][j])+ (m[i][2]*generalMT[2][j])+ (m[i][3]*generalMT[3][j]);
        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            generalMT[i][j] = r[i][j];

        }
    }

}
void resetMatrix(){
    int i,j;
    for(i = 0 ; i < 4 ; i++)
        for(j = 0 ; j < 4 ; j++)
            generalMT[i][j] = (i == j) ? 1 : 0;

    for(i = 0 ; i < 4 ; i++)
        for(j = 0 ; j < 4 ; j++)
            normalsMT[i][j] = (i == j) ? 1 : 0;

}
//Testing:
void printTrans(){
    int i,j;
    for (i = 0; i < 4; i++) {
        for(j = 0 ; j < 4 ; j++){
            printf(" | %f",generalMT[i][j]);
        }
        printf(" | \n");
    }
}
//---------------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------Vectors--------------------------------------------//

vecI newVecI(int x, int y, int z){
    vecI v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
vecF newVecF(float x, float y, float z){
    vecF v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
vecI newStrVecI(char * str){
    vecI v;
    v.x = atoi(strtok(str," "));
    v.y = atoi(strtok(NULL," "));
    v.z = atoi(strtok(NULL," "));
    return v;
}
vecF newStrVecF(char * str){
    vecF v;
    v.x = atof(strtok(str," "));
    v.y = atof(strtok(NULL," "));
    v.z = atof(strtok(NULL," "));
    return v;
}
vecI roundVecF(vecF v){
    vecI vr;
    vr.x = round(v.x);
    vr.y = round(v.y);
    vr.z = round(v.z);
    return vr;
}
vecF presicionVecI(vecI v){
    vecF vr;
    vr.x = (float)v.x;
    vr.y = (float)v.y;
    vr.z = (float)v.z;
    return vr;
}
float lengthVecI(vecI v){
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
float lengthVecF(vecF v){
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
vecF normalizeVecI(vecI v){
    vecF unit;
    unit.x = v.x/lengthVecI(v);
    unit.y = v.y/lengthVecI(v);
    unit.z = v.z/lengthVecI(v);
    return unit;
}
vecF normalizeVecF(vecF v){
    vecF unit;
    unit.x = v.x/lengthVecF(v);
    unit.y = v.y/lengthVecF(v);
    unit.z = v.z/lengthVecF(v);
    return unit;
}
vecI crossVecI(vecI v1, vecI v2){
    vecI vr;

    vr.x = (v1.y * v2.z) - (v1.z * v2.y);
    vr.y = -((v1.x*v2.z) - (v1.z*v2.x));
    vr.z = (v1.x * v2.y) - (v1.y * v2.x);

    return vr;
}
vecF crossVecF(vecF v1, vecF v2){
    vecF vr;

    vr.x = (v1.y * v2.z) - (v1.z * v2.y);
    vr.y = -((v1.x*v2.z) - (v1.z*v2.x));
    vr.z = (v1.x * v2.y) - (v1.y * v2.x);

    return vr;
}
int dotVecI(vecI v1, vecI v2){
    return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}
float dotVecF(vecF v1, vecF v2){
    return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}
vecI addVecI(vecI v1, vecI v2){
    vecI vr;
    vr.x = v1.x + v2.x;
    vr.y = v1.y + v2.y;
    vr.z = v1.z + v2.z;

    return vr;
}
vecF addVecF(vecF v1, vecF v2){
    vecF vr;
    vr.x = v1.x + v2.x;
    vr.y = v1.y + v2.y;
    vr.z = v1.z + v2.z;

    return vr;
}
vecI restVecI(vecI v1, vecI v2){
    vecI vr;
    vr.x = v1.x - v2.x;
    vr.y = v1.y - v2.y;
    vr.z = v1.z - v2.z;

    return vr;
}
vecF restVecF(vecF v1, vecF v2){
    vecF vr;
    vr.x = v1.x - v2.x;
    vr.y = v1.y - v2.y;
    vr.z = v1.z - v2.z;

    return vr;
}
void resizeVecI(vecI * v, float scale){
        v->x *= scale;
        v->y *= scale;
        v->z *= scale;
}
void resizeVecF(vecF * v, float scale){
        v->x *= scale;
        v->y *= scale;
        v->z *= scale;
}
int isSameVecI(vecI v1, vecI v2){

    if((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
        return 1;
    else
        return 0;

    return 0;
}
int isSameVecF(vecF v1, vecF v2){

    if((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
        return 1;
    else
        return 0;

    return 0;
}
void loadTransformationVecI(vecI *v){
    vecI aux = *v;
    int w;
    v->x = (generalMT[0][0]*aux.x)+(generalMT[0][1]*aux.y)+(generalMT[0][2]*aux.z)+(generalMT[0][3]);
    v->y = (generalMT[1][0]*aux.x)+(generalMT[1][1]*aux.y)+(generalMT[1][2]*aux.z)+(generalMT[1][3]);
    v->z = (generalMT[2][0]*aux.x)+(generalMT[2][1]*aux.y)+(generalMT[2][2]*aux.z)+(generalMT[2][3]);
    w = (generalMT[3][0]*aux.x)+(generalMT[3][1]*aux.y)+(generalMT[3][2]*aux.z)+(generalMT[3][3]);
    v->x /=w;
    v->y /=w;
    //v->z /=w;

}
void loadTransformationVecF(vecF *v){
    vecF aux = *v;
    float w;
    v->x = (generalMT[0][0]*aux.x)+(generalMT[0][1]*aux.y)+(generalMT[0][2]*aux.z)+(generalMT[0][3]);
    v->y = (generalMT[1][0]*aux.x)+(generalMT[1][1]*aux.y)+(generalMT[1][2]*aux.z)+(generalMT[1][3]);
    v->z = (generalMT[2][0]*aux.x)+(generalMT[2][1]*aux.y)+(generalMT[2][2]*aux.z)+(generalMT[2][3]);
    w = (generalMT[3][0]*aux.x)+(generalMT[3][1]*aux.y)+(generalMT[3][2]*aux.z)+(generalMT[3][3]);
    v->x /=w;
    v->y /=w;
    //v->z /=w;
}
void loadTransformationVecFN(vecF *v){
    vecF aux = *v;
    v->x = (normalsMT[0][0]*aux.x)+(normalsMT[0][1]*aux.y)+(normalsMT[0][2]*aux.z)+(normalsMT[0][3]);
    v->y = (normalsMT[1][0]*aux.x)+(normalsMT[1][1]*aux.y)+(normalsMT[1][2]*aux.z)+(normalsMT[1][3]);
    v->z = (normalsMT[2][0]*aux.x)+(normalsMT[2][1]*aux.y)+(normalsMT[2][2]*aux.z)+(normalsMT[2][3]);
}
//Testing:
void printVecI(char * label,vecI v){
    printf("%s %d | %d | %d\n",label,v.x,v.y,v.z);

}
void printVecF(char * label,vecF v){
    printf("%s %f | %f | %f\n",label,v.x,v.y,v.z);
}

//------------------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------Color--------------------------------------------------//
color newColor(unsigned char r, unsigned char g , unsigned char b){
    color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}
color addColor(color c1, color c2){
    color cr;
    cr.r = (c1.r + c2.r) > 255 ? 255:(c1.r + c2.r);
    cr.g = (c1.g + c2.g) > 255 ? 255:(c1.g + c2.g);
    cr.b = (c1.b + c2.b) > 255 ? 255:(c1.b + c2.b);
    return cr;
}
color randomColor(){
    color cr;
    cr = newColor(rand()%255,rand()%255,rand()%255);
    return cr;
}
color randomBaseColor(color c){
    color cr;
    int ran = rand()%255;
    cr = newColor(c.r*(ran)/255,c.g*(ran)/255,c.b*(ran)/255);
    return cr;
}
//Testing:
void printColor(char * label ,color c){
    printf("%s | R: %d | G: %d | B: %d\n",label,c.r,c.g,c.b);
}
//-----------------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------Raster------------------------------------------------//
void printPPM(resolution res){
    int i,j;
    switch (res) {
        case QVGA:
            printf("P3\n320 240\n255\n");
            for(i = 0 ; i<240 ; i++){
                for(j = 0 ; j<320 ; j++)
                    printf("%d %d %d\t",rasterQVGA[j][i][0],rasterQVGA[j][i][1],rasterQVGA[j][i][2]);
                printf("\n");
            }
        break;
        case HD:
            printf("P3\n1280 720\n255\n");
            for(i = 0 ; i<720 ; i++){
                for(j = 0 ; j<1280 ; j++)
                    printf("%d %d %d\t",rasterHD[j][i][0],rasterHD[j][i][1],rasterHD[j][i][2]);
                printf("\n");
            }
        break;
        case FHD:
            printf("P3\n1920 1080\n255\n");
            for(i = 0 ; i<1080 ; i++){
                for(j = 0 ; j<1920 ; j++)
                    printf("%d %d %d\t",rasterFHD[j][i][0],rasterFHD[j][i][1],rasterFHD[j][i][2]);
                printf("\n");
            }
        break;
        case VR:
            printf("P3\n960 540\n255\n");
            for(i = 0 ; i<540 ; i++){
                for(j = 0 ; j<960 ; j++)
                    printf("%d %d %d\t",rasterVR[j][i][0],rasterVR[j][i][1],rasterVR[j][i][2]);
                printf("\n");
            }
        break;
    }

}
void clearRaster(resolution res, color c){
    int i,j;
    switch (res) {
        case QVGA:
            for(i = 0 ; i < 360 ; i++ ){
                for(j = 0 ; j < 240 ; j++){
                    rasterQVGA[i][j][0] = c.r;
                    rasterQVGA[i][j][1] = c.g;
                    rasterQVGA[i][j][2] = c.b;
                }
            }
        break;
        case HD:
            for(i = 0 ; i < 1280 ; i++ ){
                for(j = 0 ; j < 720 ; j++){
                    rasterHD[i][j][0] = c.r;
                    rasterHD[i][j][1] = c.g;
                    rasterHD[i][j][2] = c.b;
                }
            }
        break;
        case FHD:
            for(i = 0 ; i < 1920 ; i++ ){
                for(j = 0 ; j < 1080 ; j++){
                    rasterFHD[i][j][0] = c.r;
                    rasterFHD[i][j][1] = c.g;
                    rasterFHD[i][j][2] = c.b;
                }
            }
        break;
        case VR:
            for(i = 0 ; i < 960 ; i++ ){
                for(j = 0 ; j < 540 ; j++){
                    rasterVR[i][j][0] = c.r;
                    rasterVR[i][j][1] = c.g;
                    rasterVR[i][j][2] = c.b;
                }
            }
        break;
    }
}
void initZBuffer(int depth){
    int i,j;
    for(i = 0 ; i < 1920 ; i++)
        for(j = 0 ; j < 1080 ; j++)
            zBuffer[i][j] = depth;
}
//----------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------Line------------------------------------------------//
line newLine(vecI v1, vecI v2){

    line l = (line)malloc(sizeof(Line));
    l->dx = v2.x - v1.x;
    l->dy = v2.y - v1.y;
    l->dz = v2.z - v1.z;

    int dx=l->dx,dy=l->dy,dz=l->dz,flag=0;

    if(dx < 0){
        swap(&v1.x,&v2.x);
        flag+=1;
        dx = v2.x-v1.x;
    }
    if(dy < 0){
        swap(&v1.y,&v2.y);
        flag+=2;
        dy = v2.y-v1.y;
    }
    if(dz < 0){
        swap(&v1.z,&v2.z);
        flag+=4;
        dz = v2.z-v1.z;
    }
    if(dy > dx){
        swap(&v1.x,&v1.y);
        swap(&v2.x,&v2.y);
        dx = v2.x-v1.x;
        dy = v2.y-v1.y;
        flag+=8;
    }
    if(dz > dx){
        swap(&v1.x,&v1.z);
        swap(&v2.x,&v2.z);
        dx = v2.x-v1.x;
        dz = v2.z-v1.z;
        flag+=16;
    }

    l->points = (vecI*)malloc(sizeof(vecI)*(dx+1));
    l->nPoints = dx+1;

    int X = v1.x, Y = v1.y, Z = v1.z;
    int deltaY = (2*dy)-dx, incEy = 2*dy, incNEy = 2*(dy-dx),i,j,k,incI,incJ,incK;
    int deltaZ = (2*dz)-dx, incEz = 2*dz, incNEz = 2*(dz-dx);
    if((flag&1)==1)
        i = dx,incI = -1;
    else
        i = 0,incI = 1;

    if((flag&2)==2)
        j = dx,incJ = -1;
    else
        j = 0,incJ = 1;

    if((flag&4)==4)
        k = dx,incK = -1;
    else
        k = 0,incK = 1;
    while(X <= v2.x){
        if((flag&8)==8){
            if((flag&16)==16){
                l->points[i].x = Y;
                l->points[j].y = Z;
                l->points[k].z = X;
                i+=incI;
                j+=incJ;
                k+=incK;

            }else{
                l->points[i].x = Y;
                l->points[j].y = X;
                l->points[k].z = Z;
                i+=incI;
                j+=incJ;
                k+=incK;
            }
        }else{
            if((flag&16)==16){
                l->points[i].x = Z;
                l->points[j].y = Y;
                l->points[k].z = X;
                i+=incI;
                j+=incJ;
                k+=incK;

            }else{
                l->points[i].x = X;
                l->points[j].y = Y;
                l->points[k].z = Z;
                i+=incI;
                j+=incJ;
                k+=incK;
            }
        }
        if(deltaY > 0){
            deltaY += incNEy;
            Y++;
        }else{
            deltaY += incEy;
        }
        if(deltaZ > 0){
            deltaZ += incNEz;
            Z++;
        }else{
            deltaZ += incEz;
        }
        X++;
    }
    return l;
}
void rasterLine(line l,resolution res, color c,int buffering){
    int i,x,y,z;
    switch (res) {
        case QVGA:
        for(i = 0 ; i<l->nPoints ; i++){
            x = l->points[i].x + (320/2);
            y = -(l->points[i].y) + (240/2);
            z = l->points[i].z;
            if(x < 320 && y < 240 && x >= 0 && y >= 0){
                if(zBuffer[x][y] < z || !buffering){
                    rasterQVGA[x][y][0] = c.r;
                    rasterQVGA[x][y][1] = c.g;
                    rasterQVGA[x][y][2] = c.b;
                    zBuffer[x][y] = z;
                }
            }
        }
        break;
        case HD:
        for(i = 0 ; i<l->nPoints ; i++){
            x = l->points[i].x + (1280/2);
            y = -(l->points[i].y) + (720/2);
            z = l->points[i].z;
            if(x < 1280 && y < 720 && x >= 0 && y >= 0){
                if(zBuffer[x][y] < z || !buffering){
                    rasterHD[x][y][0] = c.r;
                    rasterHD[x][y][1] = c.g;
                    rasterHD[x][y][2] = c.b;
                    zBuffer[x][y] = z;
                }
            }
        }
        break;
        case FHD:
        for(i = 0 ; i<l->nPoints ; i++){
            x = l->points[i].x + (1920/2);
            y = -(l->points[i].y) + (1080/2);
            z = l->points[i].z;
            if(x < 1920 && y < 1080 && x >= 0 && y >= 0){
                if(zBuffer[x][y] < z || !buffering){
                    rasterFHD[x][y][0] = c.r;
                    rasterFHD[x][y][1] = c.g;
                    rasterFHD[x][y][2] = c.b;
                    zBuffer[x][y] = z;
                }
            }


        }
        break;
        case VR:
            for(i = 0 ; i<l->nPoints ; i++){
                x = l->points[i].x + 480;
                y = -(l->points[i].y) + 280;
                z = l->points[i].z;
                if(x < 960 && y < 560 && x >= 0 && y >= 0){
                    if(zBuffer[x][y] < z || !buffering){
                        rasterVR[x][y][0] = c.r;
                        rasterVR[x][y][1] = c.g;
                        rasterVR[x][y][2] = c.b;
                        zBuffer[x][y] = z;
                    }
                }


            }
        break;
    }
}
void freeLine(line l){
    free(l->points);
    free(l);
}
//Testing:
void printLine(line l){
    int i = 0;
    printf("dx: %d\n", l->dx);
    printf("dy: %d\n", l->dy);
    printf("dy: %d\n", l->dz);
    printf("x\ty\tz\n-----------\n");
    for(i = 0 ; i < l->nPoints ; i++){
        printf("%d\t%d\t%d\n",l->points[i].x,l->points[i].y,l->points[i].z );
    }

}
//-----------------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------3DModel------------------------------------------------//
material newMaterial(color c ,int n){
    material m;
    m.c = c;
    m.n_specular = n;
    return m;
}
model loadModel(char * fileName ,material mat,int scale){
    int i=0;
    model m = (model)malloc(sizeof(Model));
    FILE *doc;
    char chain[100];

    doc = fopen(fileName,"r");
    m->m = mat;
    m->scale = scale;

    fgets(chain,100,doc);
    m->nVertex = atoi(chain);
    m->vertex = (vecF*)malloc(sizeof(vecF)*m->nVertex);
    while(i<m->nVertex){
        fgets(chain,100,doc);
        m->vertex[i] = newStrVecF(chain);
        resizeVecF(&m->vertex[i],scale);
        i++;
    }
    fgets(chain,100,doc);
    m->nEdges = atoi(chain);
    i=0;
    while(i<m->nEdges){
        fgets(chain,100,doc);
        m->edges[i][0] = atoi(strtok(chain, " "));
        m->edges[i][1] = atoi(strtok(NULL, " "));
        i++;
    }

    fgets(chain,100,doc);
    m->nFaces = atoi(chain);
    i=0;
    while(i<m->nFaces){
        fgets(chain,100,doc);
        m->faces[i][0] = atoi(strtok(chain, " "));
        m->faces[i][1] = atoi(strtok(NULL, " "));
        m->faces[i][2] = atoi(strtok(NULL, " "));
        i++;
    }

    fgets(chain,100,doc);
    m->nNormals = atoi(chain);
    m->normals = (vecF*)malloc(sizeof(vecF)*m->nNormals);
    i=0;

    while(i<m->nNormals){
        fgets(chain,100,doc);
        m->normals[i] = newStrVecF(chain);
        //resizeVecF(&m->normals[i],scale/2);
        i++;
    }
    fclose(doc);
    return m;
}
void rasterModel(model m,resolution res,char type,int buffering){
    int i,j,k,sumPoints,maxY,minY,minZ,maxZ;;
    int e1,e2,e3;
    line l1,l2,l3,lf;
    vecI v1,v2,*listPoints;
    color random;
    if(type == 'w' || type == 'W'){
        for(i = 0 ; i < m->nEdges ; i++){

            v1 = roundVecF(m->vertex[m->edges[i][0]]);
            v2 = roundVecF(m->vertex[m->edges[i][1]]);
            lf = newLine(v1,v2);
            rasterLine(lf,res,m->m.c,buffering);
            freeLine(lf);
        }
    }else{
        if(type == 's' || type == 'S' || type == 'r' || type == 'R'){
            srand(time(NULL));
            for(i = 0 ; i < m->nFaces ; i++){
                random = randomBaseColor(m->m.c);

                e1 = m->faces[i][0];
                e2 = m->faces[i][1];
                e3 = m->faces[i][2];

                v1 = roundVecF(m->vertex[m->edges[e1][0]]);
                v2 = roundVecF(m->vertex[m->edges[e1][1]]);
                l1 = newLine(v1,v2);

                v1 = roundVecF(m->vertex[m->edges[e2][0]]);
                v2 = roundVecF(m->vertex[m->edges[e2][1]]);
                l2 = newLine(v1,v2);

                v1 = roundVecF(m->vertex[m->edges[e3][0]]);
                v2 = roundVecF(m->vertex[m->edges[e3][1]]);
                l3 = newLine(v1,v2);

                sumPoints = l1->nPoints + l2->nPoints + l3->nPoints;
                listPoints = (vecI*)malloc(sizeof(vecI)*sumPoints);

                for(j = 0 ; j < l1->nPoints ; j++ )
                    listPoints[j] = l1->points[j];

                for(j = 0 ; j < l2->nPoints; j++ )
                    listPoints[j+l1->nPoints] = l2->points[j];

                for(j = 0 ; j < l3->nPoints ; j++ )
                    listPoints[j+l1->nPoints+l2->nPoints] = l3->points[j];


                maxY = -3000; minY = listPoints[0].y;
                for(j = 0 ; j < sumPoints ; j++){
                    maxY = (listPoints[j].y > maxY) ? listPoints[j].y : maxY;
                    minY = (listPoints[j].y < minY) ? listPoints[j].y : minY;
                }



                for(j = minY ; j < maxY ; j++){
                    int maxX = -10000, minX = 10000;
                    for(k = 0 ; k < sumPoints ; k++){
                        if(listPoints[k].y == j){
                            if(listPoints[k].x > maxX){
                                maxX = listPoints[k].x;
                                maxZ = listPoints[k].z;
                            }
                            if(listPoints[k].x < minX){
                                minX = listPoints[k].x;
                                minZ = listPoints[k].z;
                            }
                        }
                    }
                    v1 = newVecI(minX,j,minZ);
                    v2 = newVecI(maxX,j,maxZ);
                    lf = newLine(v1, v2);
                    if(type == 's' || type == 'S')
                        rasterLine(lf,res,m->m.c,buffering);
                    else{

                        rasterLine(lf,res,random,buffering);
                    }
                    freeLine(lf);

                }
                freeLine(l1);
                freeLine(l2);
                freeLine(l3);
                free(listPoints);

            }
        }else{
            printf("Wrong param type\n");
            printf("use w or W for  wire moldel\n");
            printf("use s or S for  solid moldel\n");
            printf("use r or R for a solid moldel with random Color\n");
        }
    }

}
void loadTransformation(model m){
    int i;
    for(i = 0 ; i < m->nVertex ; i++){
        loadTransformationVecF(&m->vertex[i]);
    }
    for(i = 0 ; i < m->nNormals ; i++){
        loadTransformationVecFN(&m->normals[i]);
    }


}
void freeModel(model m){
    free(m->vertex);
    free(m->normals);
    free(m);
}
//Testing:
void rasterNormals(model m,resolution res){
    color red = newColor(255,0,0);
    color light_blue = newColor(100,100,255);
    int i;
    line l;
    vecF norm;
    vecI n,o = newVecI(0,0,0);
    for(i = 0 ; i < m->nFaces ; i++){
        norm = m->normals[i];
        resizeVecF(&norm,100);
        n = roundVecF(norm);
        l = newLine(n,o);
        rasterLine(l,res,red,1);
        freeLine(l);
    }
    for(i = 0 ; i < m->nEdges ; i++){
        norm = m->normals[i+m->nFaces];
        resizeVecF(&norm,100);
        n = roundVecF(norm);
        l = newLine(n,o);
        rasterLine(l,res,light_blue,1);
        freeLine(l);
    }}//Not Working at all
void printModel(model m){

    int i;
    for(i = 0 ; i < m->nVertex ; i++)
        printVecF("V: ",m->vertex[i]);
    for(i = 0 ; i < m->nEdges ; i++)
        printf("E: %d %d\n",m->edges[i][0],m->edges[i][1]);
    for(i = 0 ; i < m->nFaces ; i++)
        printf("F: %d %d %d \n",m->faces[i][0],m->faces[i][1],m->faces[i][2]);
    for(i = 0 ; i < m->nNormals ; i++)
        printVecF("N: ",m->normals[i]);
}
//---------------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------Camera------------------------------------------------//
camera newCamera(vecI origin , int focus, int ang_x, int ang_y, int ang_z){

    camera c = (camera)malloc(sizeof(Camera));
    vecI dir = newVecI(0,0,focus);

    pushRotateX(ang_x);
    pushRotateY(ang_y);
    pushRotateZ(ang_z);
    pushTranslate(origin.x,origin.y,origin.z);
    loadTransformationVecI(&dir);
    resetMatrix();

    c->ang_x = ang_x;
    c->ang_y = ang_y;
    c->ang_z = ang_z;

    c->origin = origin;
    c->direction = dir;
    c->focus = focus;

    return c;
}
void takePhoto(camera cam,model m){
    pushTranslate(-(cam->origin.x),-(cam->origin.y),-(cam->origin.z));
    pushRotateZ(-(cam->ang_z));
    pushRotateY(-(cam->ang_y));
    pushRotateX(-(cam->ang_x));
    projection(cam->focus);
    loadTransformation(m);
    resetMatrix();
}
void freeCamera(camera c){
    free(c);

}
//---------------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------Light--------------------------------------------------//
//need improvement
void setAmbientLight(color c){
    ambient = c;
}

radial newRadial(vecI position,color c, vecF abc){
    radial rd;
    rd.position = position;
    rd.c = c;
    rd.abc = abc;
    return rd;
}
listLRad startListLRad(radial rd){
    listLRad l = (listLRad)malloc(sizeof(ListLRad));
    l->rd = rd;
    l->index =0;
    l->length = 1;
    l->next = NULL;
    return l;
}
void addListLRad(listLRad l , radial rd){
    if(l->next == NULL){
        l->next = startListLRad(rd);
        l->next->index = l->index +1;
        l->length++;

    }else{
        l->length++;
        addListLRad(l->next,rd);
    }
}
void putsListRad(listLRad l , radial rd, int index){
    if(l->index == index){
        l->rd = rd  ;
    }else{
        putsListRad(l->next,rd,index);
    }
}
radial getListLRad(listLRad l , int index){
    if(l->index == index)
        return l->rd;
    else{
        if(l->next == NULL){
            return l->next->rd;
        }else{
            return getListLRad(l->next,index);
        }
    }
}
void freeListLRad(listLRad l){
    if(l->next == NULL){
        free(l);
    }else{
        freeListLRad(l->next);
        free(l);
    }
}

spot newSpot(vecI position,color c, vecF abc, int ang,int ang_x,int ang_y,int ang_z){
    spot sp;
    sp.norm =newVecF(0,-1,0);
    pushRotateX(ang_x);
    pushRotateY(ang_y);
    pushRotateZ(ang_z);
    loadTransformationVecF(&sp.norm);
    resetMatrix();
    sp.position = position;

    sp.c = c;
    sp.abc = abc;
    sp.ang = ang;

    return sp;
}
listLSpot startListLSpot(spot sp){
    listLSpot l = (listLSpot)malloc(sizeof(ListLSpot));
    l->sp = sp;
    l->index =0;
    l->length = 1;
    l->next = NULL;
    return l;
}
void addListLSpot(listLSpot l , spot sp){
    if(l->next == NULL){
        l->next = startListLSpot(sp);
        l->next->index = l->index +1;
        l->length++;

    }else{
        l->length++;
        addListLSpot(l->next,sp);
    }
}
void putsListSpot(listLSpot l , spot sp, int index){
    if(l->index == index){
        l->sp = sp  ;
    }else{
        putsListSpot(l->next,sp,index);
    }
}
spot getListLSpot(listLSpot l , int index){
    if(l->index == index)
        return l->sp;
    else{
        if(l->next == NULL){
            return l->next->sp;
        }else{
            return getListLSpot(l->next,index);
        }
    }
}
void freeListLSpot(listLSpot l){
    if(l->next == NULL){
        free(l);
    }else{
        freeListLSpot(l->next);
        free(l);
    }
}



color diffuseLightPoint(listLRad rd,listLSpot sp, vecI point,vecF n){
    int i;
    vecF l,r;
    float d,cosA,cosL,cosN;
    color c1 = newColor(0,0,0);
    radial lr;
    spot ls;
    pushTranslate(-point.x,-point.y,-point.z);
    for(i = 0 ; i < rd->length ; i++){
        lr = getListLRad(rd,i);
        l = presicionVecI(lr.position);

        loadTransformationVecF(&l);

        l = normalizeVecF(l);
        r = calculateReflected(l,n);
        d = lengthVecI(lr.position);
        lr.at = 1/((lr.abc.x*d*d)+(lr.abc.y*d)+lr.abc.z);

        cosA = dotVecF(n,r);

        if(cosA >= 0)
            c1=addColor(c1,newColor(lr.at*cosA*lr.c.r,lr.at*cosA*lr.c.g,lr.at*cosA*lr.c.b));
        else
            c1=addColor(c1,newColor(0,0,0));

    }
    for(i = 0 ; i < sp->length ; i++){
        ls = getListLSpot(sp,i);
        r = ls.norm;
        resizeVecF(&r,-1);
        r = normalizeVecF(r);
        l = presicionVecI(ls.position);
        loadTransformationVecF(&l);
        l = normalizeVecF(l);
        d = lengthVecI(ls.position);
        ls.at = 1/((ls.abc.x*d*d)+(ls.abc.y*d)+ls.abc.z);

        cosA = dotVecF(n,r);
        cosN = dotVecF(r,l);
        cosL = cos(ls.ang*PI/180.0);
        if(!(dotVecF(n,r)>0 && cosN > 0 && cosN < cosL))
            c1=addColor(c1,newColor(ls.at*cosA*ls.c.r,ls.at*cosA*ls.c.g,ls.at*cosA*ls.c.b));
        else
            c1=addColor(c1,newColor(0,0,0));

    }

    resetMatrix();
    return c1;
}
color specularLightPoint(int n_s,listLRad rd, listLSpot sp,vecI point,vecF n){
    int i;
    vecF l,r,nl;
    vecF camera = newVecF(0,0,1.0);
    float d,cosA,cosB,cosL,cosN;
    color c1 = newColor(0,0,0);
    radial lr;
    spot ls;
    pushTranslate(-point.x,-point.y,-point.z);
    for(i = 0 ; i < rd->length ; i++){
        lr = getListLRad(rd,i);
        l = presicionVecI(lr.position);
        loadTransformationVecF(&l);
        l = normalizeVecF(l);
        d = lengthVecI(lr.position);
        lr.at = 1/((lr.abc.x*d*d)+(lr.abc.y*d)+lr.abc.z);

        cosA = dotVecF(n,r);
        cosB = dotVecF(camera,r);

        if(cosB >= 0){
            cosB = pow(cosB,n_s);
            c1=addColor(c1,newColor(lr.at*cosB*lr.c.r,lr.at*cosB*lr.c.g,lr.at*cosB*lr.c.b));
        }else
            c1=addColor(c1,newColor(0,0,0));

    }
    for(i = 0 ; i < sp->length ; i++){
        ls = getListLSpot(sp,i);
        nl = ls.norm;
        resizeVecF(&nl,-1);
        nl = normalizeVecF(nl);
        l = presicionVecI(ls.position);
        loadTransformationVecF(&l);
        l = normalizeVecF(l);
        r = calculateReflected(l,n);
        d = lengthVecI(ls.position);
        ls.at = 1/((ls.abc.x*d*d)+(ls.abc.y*d)+ls.abc.z);

        cosA = dotVecF(n,nl);
        cosB = dotVecF(camera,r);
        cosN = dotVecF(nl,l);
        cosL = cos(ls.ang*PI/180.0);
        if(!(dotVecF(nl,r)>0 && cosN > 0 && cosN < cosL))
            c1=addColor(c1,newColor(ls.at*cosB*ls.c.r,ls.at*cosB*ls.c.g,ls.at*cosB*ls.c.b));
        else
            c1=addColor(c1,newColor(0,0,0));

    }
    resetMatrix();
    return c1;
}

void takePhotoScene(camera cam,model m,listLRad rLights, listLSpot sLights){
    int i;
    radial rd;
    spot sp;
    pushTranslate(-(cam->origin.x),-(cam->origin.y),-(cam->origin.z));
    pushRotateZ(-(cam->ang_z));
    pushRotateY(-(cam->ang_y));
    pushRotateX(-(cam->ang_x));
    for(i = 0 ; i < rLights->length ; i++){
        rd = getListLRad(rLights , i);
        //printf("LoadLight\n");
        loadTransformationVecI(&rd.position);
        putsListRad(rLights,rd,i);
    }


    for(i = 0 ; i < sLights->length ; i++){

        sp = getListLSpot(sLights , i);
        //printf("LoadLight\n");

        loadTransformationVecI(&sp.position);
        loadTransformationVecFN(&sp.norm);
        putsListSpot(sLights,sp,i);
    }
    projection(cam->focus);
    loadTransformation(m);
    resetMatrix();
}
void rasterModelLight(model m,resolution res,camera c1,listLRad rd,listLSpot sp){
    int i,j,k,sumPoints,maxY,minY,minZ,maxZ;;
    int e1,e2,e3;
    line l1,l2,l3,lf;
    vecI v1,v2,*listPoints;
    for(i = 0 ; i < m->nFaces ; i++){
        //printf("Face:%d\n",i);
        e1 = m->faces[i][0];
        e2 = m->faces[i][1];
        e3 = m->faces[i][2];

        v1 = roundVecF(m->vertex[m->edges[e1][0]]);
        v2 = roundVecF(m->vertex[m->edges[e1][1]]);
        l1 = newLine(v1,v2);

        v1 = roundVecF(m->vertex[m->edges[e2][0]]);
        v2 = roundVecF(m->vertex[m->edges[e2][1]]);
        l2 = newLine(v1,v2);

        v1 = roundVecF(m->vertex[m->edges[e3][0]]);
        v2 = roundVecF(m->vertex[m->edges[e3][1]]);
        l3 = newLine(v1,v2);

        sumPoints = l1->nPoints + l2->nPoints + l3->nPoints;
        listPoints = (vecI*)malloc(sizeof(vecI)*sumPoints);

        for(j = 0 ; j < l1->nPoints ; j++ )
            listPoints[j] = l1->points[j];

        for(j = 0 ; j < l2->nPoints; j++ )
            listPoints[j+l1->nPoints] = l2->points[j];

        for(j = 0 ; j < l3->nPoints ; j++ )
            listPoints[j+l1->nPoints+l2->nPoints] = l3->points[j];


        maxY = -3000; minY = listPoints[0].y;
        for(j = 0 ; j < sumPoints ; j++){
            maxY = (listPoints[j].y > maxY) ? listPoints[j].y : maxY;
            minY = (listPoints[j].y < minY) ? listPoints[j].y : minY;
        }
        for(j = minY ; j < maxY ; j++){
            int maxX = -10000, minX = 10000;
            for(k = 0 ; k < sumPoints ; k++){
                if(listPoints[k].y == j){
                    if(listPoints[k].x > maxX){
                        maxX = listPoints[k].x;
                        maxZ = listPoints[k].z;
                    }
                    if(listPoints[k].x < minX){
                        minX = listPoints[k].x;
                        minZ = listPoints[k].z;
                    }
                }
            }
            v1 = newVecI(minX,j,minZ);
            v2 = newVecI(maxX,j,maxZ);
            lf = newLine(v1, v2);

            vecF n = m->normals[i];
            color diffuse,specular,total = newColor(0,0,0);
            vecI point;
            line lp;

            //printf("%d\n",i);
            for(k = 0 ; k < lf->nPoints ; k++){
                point = lf->points[k];
                lp = newLine(point,point);
                diffuse = diffuseLightPoint(rd,sp,point,n);
                specular = specularLightPoint(m->m.n_specular,rd,sp,point,n);
                total = addColor(total,diffuse);
                total = addColor(total,specular);
                total = addColor(total,ambient);
                //printColor("t:", t);
                total.r *= ((m->m.c.r)/255.0);
                total.g *= ((m->m.c.g)/255.0);
                total.b *= ((m->m.c.b)/255.0);
                //printColor("t1:", t);
                rasterLine(lp,res,total,1);
                total = newColor(0,0,0);
                freeLine(lp);
            }

            freeLine(lf);
        }
        freeLine(l1);
        freeLine(l2);
        freeLine(l3);
        free(listPoints);
    }
}

//Testing:
void printRadial(radial rd){
    printf("Radial Light:\n");
    printVecI("position: ", rd.position);
    printColor("Color: ", rd.c);
    printVecF("AteValues: ", rd.abc);
}
void printSpot(spot sp){
    printf("Spot Light:\n");
    printVecI("position: ", sp.position);
    printVecF("Normal: ", sp.norm);
    printColor("Color: ", sp.c);
    printVecF("AteValues: ", sp.abc);
    printf("Angulo: %d\n", sp.ang);
}
//---------------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------Curve--------------------------------------------------//
float hermiteMT[4][4]={{2,-2,1,1},{-3,3,-2,-1},{0,0,1,0},{1,0,0,0}};

//--------------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------Miscellaneous--------------------------------------------//
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
vecI findVertexFace(model m,int face){
    int e1,e2,e3;
    vecI verx;
    e1 = m->faces[face][0];
    e2 = m->faces[face][1];
    e3 = m->faces[face][2];
    verx.x = m->edges[e1][0];
    verx.y = m->edges[e1][1];
    if(m->edges[e2][0] == verx.x || m->edges[e2][0] == verx.x)
        if(m->edges[e2][1] == verx.x || m->edges[e2][1] == verx.x)
            if(m->edges[e3][0] == verx.x || m->edges[e3][0] == verx.x)
                verx.z = m->edges[e3][1];
            else
                verx.z = m->edges[e3][0];
        else
            verx.z = m->edges[e2][1];
    else
        verx.z = m->edges[e2][0];

    return verx;
}
vecF calculateReflected(vecF l, vecF n){
    //r = 2(l.n)n-l with n & l normalized
    vecF r;
    float comp = 2*dotVecF(l,n);
    r = n;
    resizeVecF(&r,comp);
    resizeVecF(&l,-1);
    r = addVecF(r,l);
    return r;
}
