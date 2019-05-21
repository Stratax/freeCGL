#include<myGraphics.h>

void initScene(){
    color gray = newColor(100,100,100);
    initZBuffer(-100000);
    clearRaster(FHD,gray);
    setAmbientLight(newColor(0,0,0));
}

void loadSettings(model *m, camera *c, listLRad *lr, listLSpot *lp){
    FILE *doc;
    char buffer[100];
    char aux[100];
    doc = fopen("settings","r");
    material mat;
    spot sp;
    radial rd;
    color c1;
    float nf;
    int sc,x,y,z;
    vecI posI,posI2;
    vecF posF;
    while(fgets(buffer,100,doc)) {
        if(buffer[0] == '/')
            break;
        switch (buffer[0]) {
            case 'm':
                fgets(buffer,100,doc);
                strcpy(aux,strtok(buffer,"\n"));
                fgets(buffer,100,doc);
                c1.r = atoi(strtok(buffer," "));
                c1.g = atoi(strtok(NULL," "));
                c1.b = atoi(strtok(NULL," "));
                nf = atof(strtok(NULL," "));
                fgets(buffer,100,doc);
                sc = atoi(buffer);
                mat = newMaterial(c1,nf);
                *m = loadModel(aux,mat,sc);
            break;
            case 'c':
                fgets(buffer,100,doc);
                posI = newStrVecI(buffer);
                fgets(buffer,100,doc);
                sc = atoi(strtok(buffer," "));
                x = atoi(strtok(NULL," "));
                y = atoi(strtok(NULL," "));
                z = atoi(strtok(NULL," "));
                *c = newCamera(posI,sc,x,y,z);

            break;
            case 's':
                fgets(buffer,100,doc);
                posI = newStrVecI(buffer);
                fgets(buffer,100,doc);
                posI2 = newStrVecI(buffer);
                fgets(buffer,100,doc);
                c1.r = atoi(strtok(buffer," "));
                c1.g = atoi(strtok(NULL," "));
                c1.b = atoi(strtok(NULL," "));
                fgets(buffer,100,doc);
                posF = newStrVecF(buffer);
                fgets(buffer,100,doc);
                sc = atoi(buffer);
                sp = newSpot(posI,c1,posF,sc,posI2.x,posI2.y,posI2.z);
                if(*lp){
                    addListLSpot(*lp,sp);
                }else{
                    *lp = startListLSpot(sp);
                }

            break;
            case 'r':
                fgets(buffer,100,doc);
                posI = newStrVecI(buffer);
                fgets(buffer,100,doc);
                c1.r = atoi(strtok(buffer," "));
                c1.g = atoi(strtok(NULL," "));
                c1.b = atoi(strtok(NULL," "));
                fgets(buffer,100,doc);
                posF = newStrVecF(buffer);
                rd = newRadial(posI,c1,posF);
                if(*lr){
                    addListLRad(*lr,rd);
                }else{
                    *lr = startListLRad(rd);
                }

            break;

        }
    }
    fclose(doc);
}

int main(int argc, char const *argv[]) {

    model m = NULL;
    camera c1 = NULL;
    listLRad radLights = NULL;
    listLSpot spotLights = NULL;
    initScene();
    loadSettings(&m,&c1,&radLights,&spotLights);
    takePhotoScene(c1,m,radLights,spotLights);
    rasterModelLight(m,FHD,c1,radLights,spotLights);
    printPPM(FHD);
    freeModel(m);
    freeCamera(c1);
    freeListLRad(radLights);
    freeListLSpot(spotLights);

    return 0;
}
