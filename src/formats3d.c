#include<formats3d.h>

float vertex[10000][3];
int edges[10000][2];
int faces[10000][3];
int nVertex=0,nFaces=0,nEdges=0;

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

        e1 = findEdge(v1,v2);
        e2 = findEdge(v2,v3);
        e3 = findEdge(v3,v1);
        faces[nFaces][0] = e1;
        faces[nFaces][1] = e2;
        faces[nFaces][2] = e3;
        nFaces++;

    }
    fclose(obj);


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
