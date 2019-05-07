#include<formats3d.h>

float vertex[10000][3];
float normals[10000][3];
int edges[10000][2];
int faces[10000][3];
int nVertex=0,nFaces=0,nEdges=0,nNormals=0;

void raw2vlf(char * doc){
    FILE * obj;
    char chain[100];
    float x,y,z;
    int v1,v2,v3,e1,e2,e3;
    int i=0;

    //vertex
    obj = fopen(doc,"r");
    while(fgets(chain,100,obj)){
        x = atof(strtok(chain," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        if(findVertex(x,y,z) == -1){
            vertex[nVertex][0] =x;
            vertex[nVertex][1] =y;
            vertex[nVertex][2] =z;
            nVertex++;
        }
        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        if(findVertex(x,y,z) == -1){
            vertex[nVertex][0] =x;
            vertex[nVertex][1] =y;
            vertex[nVertex][2] =z;
            nVertex++;
        }

        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        if(findVertex(x,y,z) == -1){
            vertex[nVertex][0] =x;
            vertex[nVertex][1] =y;
            vertex[nVertex][2] =z;
            nVertex++;
        }

    }
    fclose(obj);

    //Edges
    obj = fopen(doc,"r");
    while(fgets(chain,100,obj)){

        x = atof(strtok(chain," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v1 = findVertex(x,y,z);

        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v2 = findVertex(x,y,z);

        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v3 = findVertex(x,y,z);
        if(findEdge(v1,v2)== -1){
            edges[nEdges][0] = v1;
            edges[nEdges][1] = v2;
            nEdges++;
        }
        if(findEdge(v2,v3)== -1){
            edges[nEdges][0] = v2;
            edges[nEdges][1] = v3;
            nEdges++;
        }
        if(findEdge(v3,v1)== -1){
            edges[nEdges][0] = v3;
            edges[nEdges][1] = v1;
            nEdges++;
        }

    }
    fclose(obj);

    //Faces
    float average,maxAverage = -9999999;
    int theFace;
    obj = fopen(doc,"r");
    while(fgets(chain,100,obj)){
        average =0;
        x = atof(strtok(chain," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v1 = findVertex(x,y,z);
        average +=z;
        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v2 = findVertex(x,y,z);
        average +=z;
        x = atof(strtok(NULL," "));
        y =  atof(strtok(NULL, " "));
        z =  atof(strtok(NULL, " "));
        v3 = findVertex(x,y,z);
        average +=z;
        e1 = findEdge(v1,v2);
        e2 = findEdge(v2,v3);
        e3 = findEdge(v3,v1);
        faces[nFaces][0] = e1;
        faces[nFaces][1] = e2;
        faces[nFaces][2] = e3;
        average/=3.0f;

        if(average > maxAverage){
                maxAverage = average;
                theFace = nFaces;
        }
        nFaces++;

    }
    fclose(obj);


    //normals

    nNormals = nFaces + nEdges;

    int flag =1,v[3],preFace,counterFaces =0;
    float o[3],from[3],to[3],norm[3];

    findVertexsFace(theFace,v);
    o[0] = vertex[v[0]][0];
    o[1] = vertex[v[0]][1];
    o[2] = vertex[v[0]][2];

    from[0] = vertex[v[1]][0];
    from[1] = vertex[v[1]][1];
    from[2] = vertex[v[1]][2];

    to[0] = vertex[v[2]][0];
    to[1] = vertex[v[2]][1];
    to[2] = vertex[v[2]][2];


    e1 = findEdge(v[0],v[1]);
    e2 = findEdge(v[1],v[2]);
    e3 = findEdge(v[2],v[0]);
    calculateNormal(norm,o,from,to);
    if(norm[2]*(-1) > 0){
        calculateNormal(norm,o,to,from);
        v1 = v[1];
        v[1] = v[2];
        v[2] = v1;
    }

    normals[theFace][0] = norm[0];
    normals[theFace][1] = norm[1];
    normals[theFace][2] = norm[2];
    while(flag){
        e1 = findEdge(v[1],v[2]);
        preFace = theFace;
        theFace = findFaceByEdge(theFace,e1);
        if(normals[theFace][0] || normals[theFace][1] || normals[theFace][2]){

            e1 = findEdge(v[0],v[2]);
            theFace = findFaceByEdge(preFace,e1);
            v[1] = v[2];
            v[2] = findThe3erdVertex(theFace,v[0],v[1]);
            if(normals[theFace][0] || normals[theFace][1] || normals[theFace][2]){
                for(i = 0 ; i < nFaces ; i++){
                    if(normals[i][0] || normals[i][1] || normals[i][2]){
                        counterFaces++;
                    }else{
                        findVertexsFace(i,v);
                        e1 = findEdge(v[0],v[1]);
                        e2 = findEdge(v[1],v[2]);
                        e3 = findEdge(v[2],v[0]);
                        theFace = findFaceByEdge(i,e1);
                        if(normals[theFace][0] || normals[theFace][1] || normals[theFace][2]){
                            v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                            o[0] = vertex[v[0]][0];
                            o[1] = vertex[v[0]][1];
                            o[2] = vertex[v[0]][2];

                            from[0] = vertex[v[1]][0];
                            from[1] = vertex[v[1]][1];
                            from[2] = vertex[v[1]][2];

                            to[0] = vertex[v[2]][0];
                            to[1] = vertex[v[2]][1];
                            to[2] = vertex[v[2]][2];


                            calculateNormal(norm,o,from,to);
                            if(norm[0]*normals[theFace][0] + norm[1]*normals[theFace][1] + norm[2]*normals[theFace][2] > 0){
                                v1 = v[0];
                                v[0] = v[1];
                                v[1] = v1;
                            }

                            theFace = findFaceByEdge(theFace,e1);
                            v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                            o[0] = vertex[v[0]][0];
                            o[1] = vertex[v[0]][1];
                            o[2] = vertex[v[0]][2];

                            from[0] = vertex[v[1]][0];
                            from[1] = vertex[v[1]][1];
                            from[2] = vertex[v[1]][2];

                            to[0] = vertex[v[2]][0];
                            to[1] = vertex[v[2]][1];
                            to[2] = vertex[v[2]][2];
                            calculateNormal(norm,o,from,to);
                            normals[theFace][0] = norm[0];
                            normals[theFace][1] = norm[1];
                            normals[theFace][2] = norm[2];

                            break;
                        }else{
                            theFace = findFaceByEdge(i,e2);
                            if(normals[theFace][0] || normals[theFace][1] || normals[theFace][2]){
                                v[0] = v[2];
                                v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                                o[0] = vertex[v[0]][0];
                                o[1] = vertex[v[0]][1];
                                o[2] = vertex[v[0]][2];

                                from[0] = vertex[v[1]][0];
                                from[1] = vertex[v[1]][1];
                                from[2] = vertex[v[1]][2];

                                to[0] = vertex[v[2]][0];
                                to[1] = vertex[v[2]][1];
                                to[2] = vertex[v[2]][2];


                                calculateNormal(norm,o,from,to);
                                if(norm[0]*normals[theFace][0] + norm[1]*normals[theFace][1] + norm[1]*normals[theFace][1] > 0){
                                    v1 = v[0];
                                    v[0] = v[1];
                                    v[1] = v1;
                                }

                                theFace = findFaceByEdge(theFace,e2);
                                v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                                o[0] = vertex[v[0]][0];
                                o[1] = vertex[v[0]][1];
                                o[2] = vertex[v[0]][2];

                                from[0] = vertex[v[1]][0];
                                from[1] = vertex[v[1]][1];
                                from[2] = vertex[v[1]][2];

                                to[0] = vertex[v[2]][0];
                                to[1] = vertex[v[2]][1];
                                to[2] = vertex[v[2]][2];
                                calculateNormal(norm,o,from,to);
                                normals[theFace][0] = norm[0];
                                normals[theFace][1] = norm[1];
                                normals[theFace][2] = norm[2];

                                break;
                            }else{
                                theFace = findFaceByEdge(i,e3);
                                if(normals[theFace][0] || normals[theFace][1] || normals[theFace][2]){
                                    v[1] = v[2];
                                    v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                                    o[0] = vertex[v[0]][0];
                                    o[1] = vertex[v[0]][1];
                                    o[2] = vertex[v[0]][2];

                                    from[0] = vertex[v[1]][0];
                                    from[1] = vertex[v[1]][1];
                                    from[2] = vertex[v[1]][2];

                                    to[0] = vertex[v[2]][0];
                                    to[1] = vertex[v[2]][1];
                                    to[2] = vertex[v[2]][2];

                                    calculateNormal(norm,o,from,to);
                                    if(norm[0]*normals[theFace][0] + norm[1]*normals[theFace][1] + norm[1]*normals[theFace][1] > 0){
                                        v1 = v[0];
                                        v[0] = v[1];
                                        v[1] = v1;
                                    }

                                    theFace = findFaceByEdge(theFace,e3);
                                    v[2] = findThe3erdVertex(theFace,v[0],v[1]);
                                    o[0] = vertex[v[0]][0];
                                    o[1] = vertex[v[0]][1];
                                    o[2] = vertex[v[0]][2];

                                    from[0] = vertex[v[1]][0];
                                    from[1] = vertex[v[1]][1];
                                    from[2] = vertex[v[1]][2];

                                    to[0] = vertex[v[2]][0];
                                    to[1] = vertex[v[2]][1];
                                    to[2] = vertex[v[2]][2];
                                    calculateNormal(norm,o,from,to);
                                    normals[theFace][0] = norm[0];
                                    normals[theFace][1] = norm[1];
                                    normals[theFace][2] = norm[2];

                                    break;
                                }else{
                                    //flag = 0;
                                    //printf("No neighbord\n");
                                }
                            }

                        }


                    }
                }

                if(counterFaces == nFaces)
                    flag =0;
                else
                    counterFaces = 0;
                //flag =0;
            }else{
                o[0] = vertex[v[0]][0];
                o[1] = vertex[v[0]][1];
                o[2] = vertex[v[0]][2];

                from[0] = vertex[v[1]][0];
                from[1] = vertex[v[1]][1];
                from[2] = vertex[v[1]][2];

                to[0] = vertex[v[2]][0];
                to[1] = vertex[v[2]][1];
                to[2] = vertex[v[2]][2];

                calculateNormal(norm,o,from,to);
                normals[theFace][0] = norm[0];
                normals[theFace][1] = norm[1];
                normals[theFace][2] = norm[2];
            }

        }else{
            v[0] = v[2];
            v[2] = findThe3erdVertex(theFace,v[0],v[1]);
            o[0] = vertex[v[0]][0];
            o[1] = vertex[v[0]][1];
            o[2] = vertex[v[0]][2];

            from[0] = vertex[v[1]][0];
            from[1] = vertex[v[1]][1];
            from[2] = vertex[v[1]][2];

            to[0] = vertex[v[2]][0];
            to[1] = vertex[v[2]][1];
            to[2] = vertex[v[2]][2];

            calculateNormal(norm,o,from,to);
            normals[theFace][0] = norm[0];
            normals[theFace][1] = norm[1];
            normals[theFace][2] = norm[2];

        }
        //flag = 0;
    }

    // Normals edges
    int f1,f2;
    for (i = 0; i < nEdges; i++) {
        f1 = findFaceByEdge(-1,i);
        f2 = findFaceByEdge(f1,i);
        norm[0] = (normals[f1][0] + normals[f2][0])/2;
        norm[1] = (normals[f1][1] + normals[f2][1])/2;
        norm[2] = (normals[f1][2] + normals[f2][2])/2;
        normals[i+nFaces][0] = norm[0];
        normals[i+nFaces][1] = norm[1];
        normals[i+nFaces][2] = norm[2];
    }
    

    printf("%d\n",nVertex);
    for(i = 0 ; i<nVertex ; i++){
        printf("%f %f %f\n",vertex[i][0],vertex[i][1],vertex[i][2]);
    }
    printf("%d\n",nEdges);
    for(i = 0 ; i<nEdges ; i++){
        printf("%d %d\n",edges[i][0],edges[i][1]);
    }
    printf("%d\n",nFaces);
    for(i = 0 ; i<nFaces ; i++){
        printf("%d %d %d\n",faces[i][0],faces[i][1],faces[i][2]);
    }

    printf("%d\n",nNormals);
    for(i = 0 ; i<nNormals ; i++){
        printf("%f %f %f\n",normals[i][0],normals[i][1],normals[i][2]);
    }



}

int findVertex(float x, float y, float z){
    int i=0;
    while(i<nVertex){
        if((vertex[i][0]==x)&&(vertex[i][1]==y)&&(vertex[i][2]==z))
            return i;
        i++;
    }
    return -1;
}

int findEdge(int v1, int v2){
    int i=0;
    while(i<nEdges){
        if((edges[i][0]==v1 && edges[i][1]==v2) || (edges[i][1]==v1 && edges[i][0]==v2))
            return i;

        i++;
    }
    return -1;
}

void findVertexsFace(int theFace, int v[3]){
    int e1 = faces[theFace][0];
    v[0] = edges[e1][0];
    v[1] = edges[e1][1];
    v[2] = findThe3erdVertex(theFace,v[0],v[1]);
}

int findThe3erdVertex(int theFace, int v1, int v2){
    int e1 = faces[theFace][0];
    int e2 = faces[theFace][1];
    int e3 = faces[theFace][2];

    if(edges[e1][0] == v1 || edges[e1][0] == v2){
        if(edges[e1][1] == v1 || edges[e1][1] == v2){
            if(edges[e2][0] == v1 || edges[e2][0] == v2){
                if(edges[e2][1] == v1 || edges[e2][1] == v2){
                    if(edges[e3][0] == v1 || edges[e3][0] == v2){
                        return edges[e3][1];
                    }else{
                        return edges[e3][0];
                    }
                }else{
                    return edges[e2][1];
                }
            }else{
                return edges[e2][0];
            }
        }else{
            return edges[e1][1];
        }
    }else{
        return edges[e1][0];
    }
}

void calculateNormal(float* n ,float* o , float* from, float* to){

    float magnitud;


    from[0]-=o[0];
    from[1]-=o[1];
    from[2]-=o[2];
    to[0]-=o[0];
    to[1]-=o[1];
    to[2]-=o[2];


    n[0] = (from[1]*to[2]) - (from[2] * to [1]);
    n[1] = -((from[0]*to[2]) - (from[2] * to [0]));
    n[2] = (from[0]*to[1]) - (from[1] * to [0]);

    magnitud = sqrt((n[0] * n[0])+(n[1] * n[1])+(n[2] * n[2]));
    n[0]/=magnitud;
    n[1]/=magnitud;
    n[2]/=magnitud;

    from[0]+=o[0];
    from[1]+=o[1];
    from[1]+=o[2];
    to[0]+=o[0];
    to[1]+=o[1];
    to[2]+=o[2];
}
int findFaceByEdge(int theFace , int e){
    int i;
    for(i = 0 ; i < nFaces ; i++){
        if((faces[i][0] == e || faces[i][1] == e || faces[i][2] == e) && i != theFace)
            return i;
    }
    return -1;

}
