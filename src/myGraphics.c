#include<myGraphics.h>
//TODO
// create function vector normal(vector pivot,vector from, vector to);
// and implements on calculateNormals.

//Vector
vector newVector(int x, int y, int z){
    vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
float magnitudVector(vector v1){
    return sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}
vector crossProduct(vector v1, vector v2){
    vector vr;

    vr.x = (v1.y * v2.z) - (v1.z * v2.y);
    vr.y = -((v1.x*v2.z) - (v1.z*v2.x));
    vr.z = (v1.x * v2.y) - (v1.y * v2.x);

    return vr;
}
int dotProduct(vector v1, vector v2){
    return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}
vector addVector(vector v1, vector v2){
    vector vr;
    vr.x = v1.x + v2.x;
    vr.y = v1.y + v2.y;
    vr.z = v1.z + v2.z;

    return vr;
}
vector restVector(vector v1, vector v2){
    vector vr;
    vr.x = v1.x - v2.x;
    vr.y = v1.y - v2.y;
    vr.z = v1.z - v2.z;

    return vr;
}
void resizeVector(vector * v1, int scale){
        v1->x *= scale;
        v1->y *= scale;
        v1->z *= scale;
}


//Color
color newColor(unsigned char r, unsigned char g , unsigned char b){
    color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

//raster
void printPPM(resolution res){
    int i,j;
    switch (res) {
        case QVGA:
        printf("P3\n320 240\n255\n");
        for(i = 0 ; i<240 ; i++){
            for(j = 0 ; j<320 ; j++){
                printf("%d %d %d\t",rasterQVGA[j][i][0],rasterQVGA[j][i][1],rasterQVGA[j][i][2]);
            }
            printf("\n");
        }
        break;
        case HD:
        printf("P3\n1280 720\n255\n");
        for(i = 0 ; i<720 ; i++){
            for(j = 0 ; j<1280 ; j++){
                printf("%d %d %d\t",rasterHD[j][i][0],rasterHD[j][i][1],rasterHD[j][i][2]);
            }
            printf("\n");
        }
        break;
        case FHD:
        printf("P3\n1920 1080\n255\n");
        for(i = 0 ; i<1080 ; i++){
            for(j = 0 ; j<1920 ; j++){
                printf("%d %d %d\t",rasterFHD[j][i][0],rasterFHD[j][i][1],rasterFHD[j][i][2]);
            }
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
    }
}
void initZBuffer(){
    int i,j;
    for(i = 0 ; i < 1920 ; i++)
        for(j = 0 ; j < 1080 ; j++)
            zBuffer[i][j] = -100000;
}

//Transformations
float transM[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
void pushTranslate(int tx, int ty, int tz){
    int i,j;
    float r[4][4];
    float m[4][4] = {{1,0,0,tx},
                     {0,1,0,ty},
                     {0,0,1,tz},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*transM[0][j])+ (m[i][1]*transM[1][j])+ (m[i][2]*transM[2][j])+ (m[i][3]*transM[3][j]);

        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            transM[i][j] = r[i][j];

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
            r[i][j] = (m[i][0]*transM[0][j])+ (m[i][1]*transM[1][j])+ (m[i][2]*transM[2][j])+ (m[i][3]*transM[3][j]);

        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            transM[i][j] = r[i][j];

        }
    }
}
void pushRotateX(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4];
    float m[4][4] = {{1,0,0,0},
                     {0,c,-s,0},
                     {0,s,c,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*transM[0][j])+ (m[i][1]*transM[1][j])+ (m[i][2]*transM[2][j])+ (m[i][3]*transM[3][j]);

        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            transM[i][j] = r[i][j];

        }
    }

}
void pushRotateY(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4];
    float m[4][4] = {{c,0,s,0},
                     {0,1,0,0},
                     {-s,0,c,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*transM[0][j])+ (m[i][1]*transM[1][j])+ (m[i][2]*transM[2][j])+ (m[i][3]*transM[3][j]);

        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            transM[i][j] = r[i][j];

        }
    }

}
void pushRotateZ(int ang){
    float rad = (PI * ang)/180;
    float c = cos(rad);
    float s = sin(rad);
    int i,j;
    float r[4][4];
    float m[4][4] = {{c,-s,0,0},
                     {s,c,0,0},
                     {0,0,1,0},
                     {0,0,0,1}};
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            r[i][j] = (m[i][0]*transM[0][j])+ (m[i][1]*transM[1][j])+ (m[i][2]*transM[2][j])+ (m[i][3]*transM[3][j]);

        }
    }
    for(i = 0 ; i < 4 ; i++){
        for(j = 0 ; j < 4; j++){
            transM[i][j] = r[i][j];

        }
    }

}
void resetMatrix(){
    int i,j;
    for(i = 0 ; i < 4 ; i++)
        for(j = 0 ; j < 4 ; j++)
            transM[i][j] = (i == j) ? 1 : 0;

}

//Line
line newLine(vector v1, vector v2){

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

    l->points = (vector*)malloc(sizeof(vector)*(dx+1));
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
    }
}
void freeLine(line l){
    free(l->points);
    free(l);
}

//Model
model newModel(int nVertex){
    model m = (model)malloc(sizeof(Model));
    m->nVertex = nVertex;
    m->vertex = (vector*)malloc(sizeof(vector)*m->nVertex);
    return m;
}
model loadModel(char * fileName ,int scale){
    int i=0;
    model m = (model)malloc(sizeof(Model));
    FILE *doc;
    doc = fopen(fileName,"r");
    char chain[100];

    fgets(chain,100,doc);
    m->nVertex = atoi(chain);
    m->vertex = (vector*)malloc(sizeof(vector)*m->nVertex);
    while(i<m->nVertex){
        fgets(chain,100,doc);
        m->vertex[i].x = (atof(strtok(chain, " "))*scale);
        m->vertex[i].y = (atof(strtok(NULL, " "))*scale);
        m->vertex[i].z = (atof(strtok(NULL, " "))*scale);
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

    m->nNormals = m->nVertex + m->nEdges + m->nFaces;
    m->normals = (vector*)malloc(sizeof(vector)*m->nNormals);
    calculateNormals(m);
    return m;
}

void calculateNormals(model m){

    int i,theFace,v1,v2,v3,ang,flag=1,e;
    vector norm,index;
    float average, maxAverage=-100000;

    //Find the most z faces
    for(i = 0 ; i < m->nFaces ; i++){
        index = findFaceVectors(i,m);
        average = (m->vertex[index.x].z+m->vertex[index.y].z+m->vertex[index.z].z)/3;
        if(average > maxAverage){
            theFace = i;
            maxAverage = average;
            v1 = index.x;
            v2 = index.y;
            v3 = index.z;
        }
    }

    vector pivot,from,to;
    pivot = m->vertex[v1];
    from = m->vertex[v2];
    to = m->vertex[v3];

    pushTranslate(-pivot.x,-pivot.y,-pivot.z);
    loadTransformationVector(&from);
    loadTransformationVector(&to);
    resetMatrix();
    norm = crossProduct(from,to);
    ang = dotProduct(newVector(0,0,-10),norm);
    if(ang > 0){
        norm = crossProduct(to,from);
        swap(&v2,&v3);
    }

    m->normals[theFace] = newVector(5*norm.x/magnitudVector(norm),5*norm.y/magnitudVector(norm),5*norm.z/magnitudVector(norm));

    int preFace;

    while(flag){
        e = findEdge(v3,v2,m);
        preFace = theFace;
        theFace = findFace(e,theFace,m);
        if(magnitudVector(m->normals[theFace])){
            e = findEdge(v3,v1,m);
            theFace = findFace(e,preFace,m);
            if(magnitudVector(m->normals[theFace])){
                for(i = 0 ; i < m->nFaces ; i++){
                    if(magnitudVector(m->normals[i])){
                        flag=0;
                    }else{
                        index = findFaceVectors(i,m);
                        e = findEdge(index.x,index.y,m);
                        theFace = findFace(e,i,m);
                        v3 = findThe3erVector(index.x,index.y,theFace,m);
                        if(magnitudVector(m->normals[theFace])){
                            pivot = m->vertex[index.y];
                            from = m->vertex[index.x];
                            to = m->vertex[v3];
                            pushTranslate(-pivot.x,-pivot.y,-pivot.z);
                            loadTransformationVector(&from);
                            loadTransformationVector(&to);
                            resetMatrix();
                            norm = crossProduct(from,to);
                            if(dotProduct(norm,m->normals[theFace]) > 0){
                                v1 = index.x;
                                v2 = index.y;
                                v3 = findThe3erVector(v1,v2,i,m);

                            }else{
                                printf("Inverse\n");
                                v1 = index.y;
                                v2 = index.x;
                                v3 = findThe3erVector(v1,v2,i,m);

                            }

                        }else{
                            e = findEdge(index.y,index.z,m);
                            theFace = findFace(e,i,m);
                            v3 = findThe3erVector(index.y,index.z,theFace,m);
                            if(magnitudVector(m->normals[theFace])){
                            pivot = m->vertex[index.z];
                            from = m->vertex[index.y];
                            to = m->vertex[v3];
                            pushTranslate(-pivot.x,-pivot.y,-pivot.z);
                            loadTransformationVector(&from);
                            loadTransformationVector(&to);
                            resetMatrix();
                            norm = crossProduct(from,to);
                            if(dotProduct(norm,m->normals[theFace]) > 0){
                                v1 = index.y;
                                v2 = index.z;
                                v3 = findThe3erVector(v1,v2,i,m);

                            }else{
                                printf("Inverse\n");
                                v1 = index.z;
                                v2 = index.y;
                                v3 = findThe3erVector(v1,v2,i,m);

                            }
                            }else{
                                e = findEdge(index.z,index.x,m);
                                theFace = findFace(e,i,m);
                                v3 = findThe3erVector(index.z,index.x,theFace,m);
                                if(magnitudVector(m->normals[theFace])){
                                    pivot = m->vertex[index.x];
                                    from = m->vertex[index.z];
                                    to = m->vertex[v3];
                                    pushTranslate(-pivot.x,-pivot.y,-pivot.z);
                                    loadTransformationVector(&from);
                                    loadTransformationVector(&to);
                                    resetMatrix();
                                    norm = crossProduct(from,to);
                                    if(dotProduct(norm,m->normals[theFace]) > 0){
                                        v1 = index.z;
                                        v2 = index.x;
                                        v3 = findThe3erVector(v1,v2,i,m);

                                    }else{
                                        printf("Inverse\n");
                                        v1 = index.x;
                                        v2 = index.z;
                                        v3 = findThe3erVector(v1,v2,i,m);

                                    }
                                }
                            }
                        }

                        pivot = m->vertex[v1];
                        from = m->vertex[v2];
                        to = m->vertex[v3];
                        theFace = i;
                        pushTranslate(-pivot.x,-pivot.y,-pivot.z);
                        loadTransformationVector(&from);
                        loadTransformationVector(&to);
                        resetMatrix();
                        norm = crossProduct(from,to);
                        m->normals[theFace]=newVector(5*norm.x/magnitudVector(norm),5*norm.y/magnitudVector(norm),5*norm.z/magnitudVector(norm));
                        break;
                    }
                }

                flag =0;
            }else{
                v2 = v3;
                v3 = findThe3erVector(v1,v2,theFace,m);
                pivot = m->vertex[v1];
                from = m->vertex[v2];
                to = m->vertex[v3];
                pushTranslate(-pivot.x,-pivot.y,-pivot.z);
                loadTransformationVector(&from);
                loadTransformationVector(&to);
                resetMatrix();
                norm = crossProduct(from,to);
                m->normals[theFace]=newVector(5*norm.x/magnitudVector(norm),5*norm.y/magnitudVector(norm),5*norm.z/magnitudVector(norm));
            }


        }else{
            v1 = v3;
            v3 = findThe3erVector(v1,v2,theFace,m);
            pivot = m->vertex[v1];
            from = m->vertex[v2];
            to = m->vertex[v3];
            pushTranslate(-pivot.x,-pivot.y,-pivot.z);
            loadTransformationVector(&from);
            loadTransformationVector(&to);
            resetMatrix();
            norm = crossProduct(from,to);
            m->normals[theFace]=newVector(5*norm.x/magnitudVector(norm),5*norm.y/magnitudVector(norm),5*norm.z/magnitudVector(norm));

        }
        //flag = 0;
    }
}

void rasterModel(model m,resolution res, color c,int buffering){
    int i;
    line l;

    for(i = 0 ; i < m->nEdges ; i++){
        l = newLine(m->vertex[m->edges[i][0]],m->vertex[m->edges[i][1]]);
        rasterLine(l,res,c,buffering);
        freeLine(l);
    }
}

void rasterSolidModel(model m,resolution res, color c,int buffering){
    int i,j,k,sumPoints,maxY,minY,minZ,maxZ;
    line l1,l2,l3,lf;
    int e1,e2,e3;
    vector *listPoints, aux1,aux2;

    for(i = 0 ; i < m->nFaces ; i++){
        e1 = m->faces[i][0];
        e2 = m->faces[i][1];
        e3 = m->faces[i][2];
        l1 = newLine(m->vertex[m->edges[e1][0]],m->vertex[m->edges[e1][1]]);
        l2 = newLine(m->vertex[m->edges[e2][0]],m->vertex[m->edges[e2][1]]);
        l3 = newLine(m->vertex[m->edges[e3][0]],m->vertex[m->edges[e3][1]]);
        sumPoints = l1->nPoints + l2->nPoints + l3->nPoints;
        listPoints = (vector*)malloc(sizeof(vector)*sumPoints);
        for(j = 0 ; j < l1->nPoints ; j++ ){
            listPoints[j] = l1->points[j];
        }
        for(j = l1->nPoints ; j < l2->nPoints+l1->nPoints ; j++ ){
            listPoints[j] = l2->points[j-l1->nPoints];
        }
        for(j = l1->nPoints+l2->nPoints ; j < sumPoints ; j++ ){
            listPoints[j] = l3->points[j-l1->nPoints-l2->nPoints];
        }

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
            aux1 = newVector(minX,j,minZ);
            aux2 = newVector(maxX,j,maxZ);
            lf = newLine(aux1, aux2);
            rasterLine(lf,res,c,buffering);
            freeLine(lf);

        }
        freeLine(l1);
        freeLine(l2);
        freeLine(l3);
        free(listPoints);

    }
}
void rasterSolidModelRandom(model m,resolution res,int buffering){
    int i,j,k,sumPoints,maxY,minY,maxZ,minZ;
    line l1,l2,l3,lf;
    int e1,e2,e3;
    vector *listPoints, aux1,aux2;
    color c;
    srand(time(NULL));

    for(i = 0 ; i < m->nFaces ; i++){
        c = newColor(30,rand()%255,30);
        e1 = m->faces[i][0];
        e2 = m->faces[i][1];
        e3 = m->faces[i][2];
        l1 = newLine(m->vertex[m->edges[e1][0]],m->vertex[m->edges[e1][1]]);
        l2 = newLine(m->vertex[m->edges[e2][0]],m->vertex[m->edges[e2][1]]);
        l3 = newLine(m->vertex[m->edges[e3][0]],m->vertex[m->edges[e3][1]]);
        sumPoints = l1->nPoints + l2->nPoints + l3->nPoints;
        listPoints = (vector*)malloc(sizeof(vector)*sumPoints);
        for(j = 0 ; j < l1->nPoints ; j++ ){
            listPoints[j] = l1->points[j];
        }
        for(j = l1->nPoints ; j < l2->nPoints+l1->nPoints ; j++ ){
            listPoints[j] = l2->points[j-l1->nPoints];
        }
        for(j = l1->nPoints+l2->nPoints ; j < sumPoints ; j++ ){
            listPoints[j] = l3->points[j-l1->nPoints-l2->nPoints];
        }

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
            aux1 = newVector(minX,j,minZ);
            aux2 = newVector(maxX,j,maxZ);
            lf = newLine(aux1, aux2);
            rasterLine(lf,res,c,buffering);
            freeLine(lf);

        }
        freeLine(l1);
        freeLine(l2);
        freeLine(l3);
        free(listPoints);

    }
}
void projectModel(model m , int f){
    vector aux;
    int i;
    for(i = 0 ; i < m->nVertex ; i++){
        aux = m->vertex[i];
        m->vertex[i].x = ((float)f * aux.x / (float)aux.z);
        m->vertex[i].y = ((float)f * aux.y / (float)aux.z);
        //m->vertex[i].z = f;
    }

}
void freeModel(model m){
    free(m->vertex);
    free(m->normals);
    free(m);
}

void loadTransformation(model m){
    vector aux;
    int i;
    for(i = 0 ; i < m->nVertex ; i++){
        aux = m->vertex[i];
        m->vertex[i].x = (transM[0][0]*aux.x)+(transM[0][1]*aux.y)+(transM[0][2]*aux.z)+(transM[0][3]);
        m->vertex[i].y = (transM[1][0]*aux.x)+(transM[1][1]*aux.y)+(transM[1][2]*aux.z)+(transM[1][3]);
        m->vertex[i].z = (transM[2][0]*aux.x)+(transM[2][1]*aux.y)+(transM[2][2]*aux.z)+(transM[2][3]);
    }
    for(i = 0 ; i < m->nFaces ; i++){
        aux = m->normals[i];
        m->normals[i].x = (transM[0][0]*aux.x)+(transM[0][1]*aux.y)+(transM[0][2]*aux.z)+(transM[0][3]);
        m->normals[i].y = (transM[1][0]*aux.x)+(transM[1][1]*aux.y)+(transM[1][2]*aux.z)+(transM[1][3]);
        m->normals[i].z = (transM[2][0]*aux.x)+(transM[2][1]*aux.y)+(transM[2][2]*aux.z)+(transM[2][3]);
    }

}

void loadTransformationVector(vector *v1){
    vector aux = *v1;

    v1->x = (transM[0][0]*aux.x)+(transM[0][1]*aux.y)+(transM[0][2]*aux.z)+(transM[0][3]);
    v1->y = (transM[1][0]*aux.x)+(transM[1][1]*aux.y)+(transM[1][2]*aux.z)+(transM[1][3]);
    v1->z = (transM[2][0]*aux.x)+(transM[2][1]*aux.y)+(transM[2][2]*aux.z)+(transM[2][3]);

}

//Camera
camera newCamera(vector origin , int focus, int ang_x, int ang_y, int ang_z){

    pushRotateX(ang_x);
    pushRotateY(ang_y);
    pushRotateZ(ang_z);
    pushTranslate(origin.x,origin.y,origin.z);

    camera c = (camera)malloc(sizeof(Camera));
    c->ang_x = ang_x;
    c->ang_y = ang_y;
    c->ang_z = ang_z;

    c->origin = newVector(0,0,0);
    c->direction = newVector(0,0,focus);
    c->focus = focus;


    c->mC = newModel(6);
    c->mC->vertex[0] = c->origin;
    c->mC->vertex[1] = c->direction;
    c->mC->vertex[2] = newVector(135,75,c->direction.z);
    c->mC->vertex[3] = newVector(135,-75,c->direction.z);
    c->mC->vertex[4] = newVector(-135,-75,c->direction.z);
    c->mC->vertex[5] = newVector(-135,75,c->direction.z);
    c->mC->nEdges = 9;
    c->mC->edges[0][0] = 0;
    c->mC->edges[0][1] = 2;
    c->mC->edges[1][0] = 0;
    c->mC->edges[1][1] = 3;
    c->mC->edges[2][0] = 0;
    c->mC->edges[2][1] = 4;
    c->mC->edges[3][0] = 0;
    c->mC->edges[3][1] = 5;
    c->mC->edges[4][0] = 2;
    c->mC->edges[4][1] = 3;
    c->mC->edges[5][0] = 3;
    c->mC->edges[5][1] = 4;
    c->mC->edges[6][0] = 4;
    c->mC->edges[6][1] = 5;
    c->mC->edges[7][0] = 5;
    c->mC->edges[7][1] = 2;
    c->mC->edges[8][0] = 2;
    c->mC->edges[8][1] = 4;
    c->mC->nFaces = 6;
    c->mC->faces[0][0] = 0;
    c->mC->faces[0][1] = 3;
    c->mC->faces[0][2] = 7;
    c->mC->faces[1][0] = 0;
    c->mC->faces[1][1] = 1;
    c->mC->faces[1][2] = 4;
    c->mC->faces[2][0] = 1;
    c->mC->faces[2][1] = 2;
    c->mC->faces[2][2] = 5;
    c->mC->faces[3][0] = 2;
    c->mC->faces[3][1] = 3;
    c->mC->faces[3][2] = 6;
    c->mC->faces[4][0] = 6;
    c->mC->faces[4][1] = 7;
    c->mC->faces[4][2] = 8;
    c->mC->faces[5][0] = 4;
    c->mC->faces[5][1] = 5;
    c->mC->faces[5][2] = 8;
    //}
    loadTransformation(c->mC);
    loadTransformationVector(&c->origin);
    loadTransformationVector(&c->direction);
    resetMatrix();
    return c;
}
void takePhoto(camera cam,model m,resolution res, color c,char t){
    pushTranslate(-(cam->origin.x),-(cam->origin.y),-(cam->origin.z));
    pushRotateZ(-(cam->ang_z));
    pushRotateY(-(cam->ang_y));
    pushRotateX(-(cam->ang_x));

    loadTransformation(m);
    projectModel(m,cam->focus);

    /*if(t == 's')
        rasterSolidModel(m,res,c,1);
    if(t == 'w')
        rasterModel(m,res,c,1);
    if(t == 'r')
        rasterSolidModelRandom(m,res,1);*/
    resetMatrix();
}
void freeCamera(camera c){
    free(c);
    freeModel(c->mC);
}



//Miscellaneous
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int isSameVector(vector v1, vector v2){

    if((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
        return 1;
    else
        return 0;

    return 0;
}
vector findFaceVectors(int face,model m){
    vector index;


    int e1 = m->faces[face][0];
    int e2 = m->faces[face][1];
    int e3 = m->faces[face][2];
    index.x = m->edges[e1][0];
    index.y = m->edges[e1][1];

    if(!isSameVector(m->vertex[index.x],m->vertex[m->edges[e2][0]]) && !isSameVector(m->vertex[index.y],m->vertex[m->edges[e2][0]]))
        index.z = m->edges[e2][0];
    else
        if(!isSameVector(m->vertex[index.x],m->vertex[m->edges[e2][1]]) && !isSameVector(m->vertex[index.y],m->vertex[m->edges[e2][1]]))
            index.z =m->edges[e2][1];
        else
            if(!isSameVector(m->vertex[index.x],m->vertex[m->edges[e3][0]]) && !isSameVector(m->vertex[index.y],m->vertex[m->edges[e3][0]]))
                index.z = m->edges[e3][0];
            else
                index.z = m->edges[e3][1];

    return index;
}
int findEdge(int v1, int v2, model m){
    int i;
    for(i = 0 ; i < m->nEdges; i++){
        if((v1 == m->edges[i][0] && v2== m->edges[i][1]) || (v1 == m->edges[i][1] && v2== m->edges[i][0]))
            return i;
    }
    return -1;
}
int findFace(int edge, int face, model m){
    int i;
    for(i = 0 ; i < m->nFaces; i++){
        if((edge == m->faces[i][0] || edge== m->faces[i][1] || edge == m->faces[i][2]) && face != i)
            return i;
    }
    return -1;
}
int findThe3erVector(int v1, int v2,int face,model m){
    int r;

    int e1 = m->faces[face][0];
    int e2 = m->faces[face][1];
    int e3 = m->faces[face][2];
    if(v1 == m->edges[e1][0] || v2 == m->edges[e1][0]){
        if(v1 == m->edges[e1][1] || v2 == m->edges[e1][1]){
            if(v1 == m->edges[e2][0] || v2 == m->edges[e2][0]){
                if(v1 == m->edges[e2][1] || v2 == m->edges[e2][1]){
                    if(v1 == m->edges[e3][0] || v2 == m->edges[e3][0]){
                        r = m->edges[e3][1];
                    }else{
                        r = m->edges[e3][0];
                    }
                }else{
                    r = m->edges[e2][1];
                }
            }else{
                r = m->edges[e2][0];
            }
        }else{
            r = m->edges[e1][1];
        }
    }else{
        r = m->edges[e1][0];
    }
    return r;
}
//Testing tools
void printVector(vector v){
    printf("p(%d,%d,%d)\n",v.x,v.y,v.z);
}
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
void printModel(model m){

    int i;
    for(i = 0 ; i < m->nVertex ; i++){
        printf("%d %d %d\n",m->vertex[i].x,m->vertex[i].y,m->vertex[i].z);
    }
    for(i = 0 ; i < m->nEdges ; i++){
        printf("%d %d\n",m->edges[i][0],m->edges[i][1]);
    }
    for(i = 0 ; i < m->nFaces ; i++){
        printf("%d %d %d \n",m->faces[i][0],m->faces[i][1],m->faces[i][2]);
    }
    for(i = 0 ; i < m->nNormals ; i++){
        printVector(m->normals[i]);
    }

}
void printTrans(){
    int i,j;
    for (i = 0; i < 4; i++) {
        for(j = 0 ; j < 4 ; j++){
            printf(" | %f",transM[i][j]);
        }
        printf(" | \n");
    }
}
void rasterReference(resolution res,color c, int scale){
    vector x1,x2,y1,y2;
    line lx, ly,lm;
    int height,width,i=0,j=0;
    switch (res) {
        case QVGA:
            x1 = newVector(-160,0,0);
            x2 = newVector(160,0,0);
            y1 = newVector(0,-120,0);
            y2 = newVector(0,120,0);
            height = 240;
            width = 320;
        break;
        case HD:
            x1 = newVector(-640,0,0);
            x2 = newVector(640,0,0);
            y1 = newVector(0,-360,0);
            y2 = newVector(0,360,0);
            height = 720;
            width = 1280;
        break;
        case FHD:
            x1 = newVector(-960,0,0);
            x2 = newVector(960,0,0);
            y1 = newVector(0,-540,0);
            y2 = newVector(0,540,0);
            height = 1080;

            width = 1920;

        break;
    }
    lx = newLine(x1,x2);
    ly = newLine(y1,y2);
    i+=scale;
    j+=scale;

    while(i < height/2){
        x1 = newVector(-10,i,0);
        x2 = newVector(10,i,0);
        y1 = newVector(-10,-(i),0);
        y2 = newVector(10,-(i),0);
        lm = newLine(x1,x2);
        rasterLine(lm,res,c,0);
        freeLine(lm);
        lm = newLine(y1,y2);
        rasterLine(lm,res,c,0);
        freeLine(lm);

        i+=scale;
    }
    while(j < width/2){
        x1 = newVector(j,-10,0);
        x2 = newVector(j,10,0);
        y1 = newVector(-j,-10,0);
        y2 = newVector(-j,10,0);
        lm = newLine(x1,x2);
        rasterLine(lm,res,c,0);
        freeLine(lm);
        lm = newLine(y1,y2);
        rasterLine(lm,res,c,0);
        freeLine(lm);

        j+=scale;
    }
    rasterLine(lx,res,c,0);
    rasterLine(ly,res,c,0);
    freeLine(lx);
    freeLine(ly);
}
void printCamera(camera c){
    printf("\tCamera: \n");
    printf("Origin: \n");
    printVector(c->origin);
    printf("Direction: \n");
    printVector(c->direction);
    printf("Focus: \n %d",c->focus);

}
void rasterCamera(camera c , resolution res){
    color green = newColor(0,255,0);
    color red = newColor(255,0,0);

    line fd = newLine(c->origin, c->direction);
    rasterModel(c->mC,res,green,0);
    rasterLine(fd,res,red,0);
    freeLine(fd);
}
void rasterNormals(model m,resolution res, color c){

        int i;
        line l;
        vector v = newVector(0,0,0);
        for(i = 0 ; i < m->nFaces ; i++){
            l = newLine(m->normals[i],v);
            rasterLine(l,res,c,0);
            freeLine(l);
        }

}
