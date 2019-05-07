#include<myGraphics.h>

typedef struct{
    int n_specular;
    color c;
}material;


typedef struct {
    color col;
    float a,b,c,attenuation;
    vector position;

}radial;
radial newRadial(vector pos, color col, float a,float b,float c);

void addAmbientLight(color c1,model m);
//void addSpotLight(spot sp);
void addRadialLight(radial rd,model m,resolution res);

int main(int argc, char *argv[]) {
    color gray =newColor(50,50,50);
    clearRaster(FHD,gray);
    vector o = newVector(0,0,1500);
    vector l = newVector(0,0,600);
    camera cam = newCamera(o,-1500,0,0,0);
    color c1= newColor(100,100,255);
    color c2= newColor(255,0,255);
    color lig= newColor(255,255,255);
    model m = loadModel(argv[1],c1,300);
    radial r = newRadial(l,lig,0.001,0.001,0.001);
    pushRotateX(-90);
    //pushRotateY(45);
    //pushRotateZ(45);
    loadTransformation(m);

    //resetMatrix();

    //addAmbientLight(lig,m);
    initZBuffer();

    //takePhoto(cam,m,FHD,c2,'s');
    //rasterSolidModel(m,FHD,1);
    //rasterSolidModelRandom(m,FHD,1);
    //rasterModel(m,FHD,0);
    //rasterModelNormal(m,FHD);
    addRadialLight(r,m,FHD);
    printPPM(FHD);
    //printModel(m);
    freeModel(m);
    freeCamera(cam);
    return 0;
}

void addAmbientLight(color c , model m){
    m->col.r = (c.r * m->col.r)/255;
    m->col.g = (c.g * m->col.g)/255;
    m->col.b = (c.b * m->col.b)/255;
}
radial newRadial(vector pos, color col, float a,float b,float c){
    radial rd;
    rd.col = col;
    rd.position = pos;
    rd.a = a;
    rd.b = b;
    rd.c = c;
    return rd;
}
float cosVect(vector v1, vector v2){

    int dot = dotProduct(v1,v2);
    return (dot/(magnitudVector(v1)*magnitudVector(v2)));
}
void addRadialLight(radial rd,model m,resolution res){
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
        for(j = 0 ; j < l1->nPoints ; j++ ){listPoints[j] = l1->points[j];}
        for(j = l1->nPoints ; j < l2->nPoints+l1->nPoints ; j++ ){listPoints[j] = l2->points[j-l1->nPoints];}
        for(j = l1->nPoints+l2->nPoints ; j < sumPoints ; j++ ){listPoints[j] = l3->points[j-l1->nPoints-l2->nPoints];}

        maxY = -30000; minY = listPoints[0].y;
        for(j = 0 ; j < sumPoints ; j++){
            maxY = (listPoints[j].y > maxY) ? listPoints[j].y : maxY;
            minY = (listPoints[j].y < minY) ? listPoints[j].y : minY;
        }

        for(j = minY ; j < maxY ; j++){
            int maxX = -900000, minX = 1000000;
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

            vector pixel,N,L,R;
            float unit,cosA,d;
            color totalColor,diffuse;
            line dot;
            N = m->normals[i];

            unit = magnitudVector(N);

            for(k = 0 ; k < lf->nPoints ; k++){
                L = rd.position;
                pixel = lf->points[k];
                dot = newLine(pixel,pixel);
                pushTranslate(-pixel.x,-pixel.y,-pixel.z);
                loadTransformationVector(&L);
                resetMatrix();
                d = magnitudVector(L);
                L.x = (unit*L.x)/d;
                L.y = (unit*L.y)/d;
                L.z = (unit*L.z)/d;
                R = newVector(2*N.x ,2*N.y, 2*N.z);
                R = restVector(R,L);

                rd.attenuation = (unit/((rd.a*d*d) + (rd.b * d) + rd.c));
                cosA = cosVect(N,R);
                if(dotProduct(N,L) > 0){
                    diffuse.r = rd.col.r*cosA*rd.attenuation;
                    diffuse.g = rd.col.g*cosA*rd.attenuation;
                    diffuse.b = rd.col.b*cosA*rd.attenuation;
                }else{
                    diffuse = newColor(0,0,0);
                }
                totalColor.r = (m->col.r*diffuse.r)/255;
                totalColor.g = (m->col.g*diffuse.g)/255;
                totalColor.b = (m->col.b*diffuse.b)/255;
                rasterLine(dot,res,totalColor,1);
                freeLine(dot);

            }
            freeLine(lf);

        }
        freeLine(l1);
        freeLine(l2);
        freeLine(l3);
        free(listPoints);

    }
}
