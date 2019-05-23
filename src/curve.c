#include<myGraphics.h>

//float t,x,y,param[4][3] ={{-3,0,0},{3,4,0},{-1,1,0},{-4,3,0}};

listCurves loadSettings(){
    FILE * doc;
    char buffer[100];
    doc = fopen("curveS","r");
    vecF v;
    listCurves lc=NULL;
    matrix m = newMatrix(4,3);
    color c1;
    curve c;

    while (fgets(buffer,100,doc)) {
        if(buffer[0]=='/')
            break;
        if(buffer[0] == 'b'){
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,0);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,1);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,2);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,3);
            fgets(buffer,100,doc);
            c1.r = atoi(strtok(buffer," "));
            c1.g = atoi(strtok(NULL," "));
            c1.b = atoi(strtok(NULL," "));
            c = newCurve(m,100,'b',c1);
            if(lc){
                addListCurves(lc,c);
            }else{
                lc = startListCurves(c);
            }
        }

        if(buffer[0] == 'h'){
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,0);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,1);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,2);
            fgets(buffer,100,doc);
            v = newStrVecF(buffer);
            addVecF2Row(m,v,3);
            fgets(buffer,100,doc);
            c1.r = atoi(strtok(buffer," "));
            c1.g = atoi(strtok(NULL," "));
            c1.b = atoi(strtok(NULL," "));
            c = newCurve(m,100,'h',c1);
            if(lc){
                addListCurves(lc,c);
            }else{
                lc = startListCurves(c);
            }
        }


    }
    freeMatrix(m);
    return lc;
}

int main(int argc, char const *argv[]) {
    listCurves lc = loadSettings();
    rasterCurves(lc,FHD,50);
    printPPM(FHD);
    //printCurve(c);
    freeListCurves(lc);
    return 0;
}
