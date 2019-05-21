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

    // -------------------------------------Transformations------------------------//
    void pushTranslate(int tx, int ty, int tz);
    void pushScale(float sx, float sy, float sz);
    void pushRotateX(int ang);
    void pushRotateY(int ang);
    void pushRotateZ(int ang);
    void projection(int focus);
    void resetMatrix();
    //Testing:
    void printTrans();
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //----------------------------------vectors------------------------------------//
    typedef struct {
        int x,y,z;
    }vecI;

    typedef struct {
        float x,y,z;
    }vecF;

    vecI newVecI(int x, int y, int z);
    vecF newVecF(float x, float y, float z);
    vecI newStrVecI(char * str);
    vecF newStrVecF(char * str);
    vecI roundVecF(vecF v);
    vecF presicionVecI(vecI v);
    float lengthVecI(vecI v);
    float lengthVecF(vecF v);
    vecF normalizeVecI(vecI v);
    vecF normalizeVecF(vecF v);
    vecI crossVecI(vecI v1, vecI v2);
    vecF crossVecF(vecF v1, vecF v2);
    int dotVecI(vecI v1, vecI v2);
    float dotVecF(vecF v1, vecF v2);
    vecI addVecI(vecI v1, vecI v2);
    vecF addVecF(vecF v1, vecF v2);
    vecI restVecI(vecI v1, vecI v2);
    vecF restVecF(vecF v1, vecF v2);
    void resizeVecI(vecI * v, float scale);
    void resizeVecF(vecF * v, float scale);
    int isSameVecI(vecI v1, vecI v2);
    int isSameVecF(vecF v1, vecF v2);
    void loadTransformationVecI(vecI *v);
    void loadTransformationVecF(vecF *v);
    void loadTransformationVecFN(vecF *v);
    //Testing:
    void printVecI(char * label,vecI v);
    void printVecF(char * label,vecF v);
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //-----------------------------------------Colors------------------------------//
    typedef struct{
        unsigned char r,g,b;
    }color;
    color newColor(unsigned char r, unsigned char g , unsigned char b);
    color addColor(color c1, color c2);
    color randomColor();
    color randomBaseColor(color c);
    //Testing:
    void printColor(char * label ,color c);
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------------Raster----------------------------//
    unsigned char rasterQVGA[320][240][3];
    unsigned char rasterHD[1280][720][3];
    unsigned char rasterFHD[1920][1080][3];
    unsigned char rasterVR[960][540][3];
    int zBuffer[1920][1080];

    typedef enum Resolution{QVGA, HD, FHD, VR}resolution;

    void printPPM(resolution res);
    void clearRaster(resolution res, color c);
    void initZBuffer(int depth);
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //------------------------------------------Line-------------------------------//
    typedef struct{
        vecI *points;
        int dx,dy,dz;
        int nPoints;
    }Line;

    typedef Line *line;

    line newLine(vecI v1, vecI v2);
    void rasterLine(line l,resolution res,color c,int buffering);
    void freeLine(line l);
    //Testing:
    void printLine(line l);

    //------------------------------------------------------------------------------//
    //////////////////////////////////////////////////////////////////////////////////
    //-----------------------------------------3DModel------------------------------//

    typedef struct{
        int n_specular;
        color c;
    }material;
    material newMaterial(color c, int n);

    typedef struct{
        int scale;
        material m;
        vecF *vertex;
        vecF *normals;
        int edges[10000][2];
        int faces[10000][3];
        int nVertex,nEdges,nFaces,nNormals;
    }Model; //VLF fortmat

    typedef Model *model;

    model loadModel(char* fileName, material mat, int scale);
    void rasterModel(model m,resolution res,char type,int buffering);
    void loadTransformation(model m);
    void freeModel(model m);
    //Testing:
    void rasterNormals(model m,resolution res);
    void printModel(model m);
    //------------------------------------------------------------------------------//
    //////////////////////////////////////////////////////////////////////////////////
    //-------------------------------Camera-----------------------------------------//
    typedef struct{
        vecI origin,direction;
        int focus,ang_x,ang_y,ang_z;
    }Camera;

    typedef Camera * camera;

    camera newCamera(vecI origin , int focus, int ang_x, int ang_y, int ang_z);
    void takePhoto(camera cam,model m);
    void freeCamera(camera c);
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //--------------------------------------Light----------------------------------//
    color ambient;
    void setAmbientLight(color c);

    typedef struct{
        vecI position;
        color c;
        vecF abc;
        float at;
    }radial;
    radial newRadial(vecI position,color c,vecF abc);

    typedef struct RADIALS{
        radial rd;
        int index,length;
        struct RADIALS * next;
    }ListLRad;

    typedef ListLRad * listLRad;

    listLRad startListLRad(radial rd);
    void addListLRad(listLRad l, radial rd);
    void putsListRad(listLRad l , radial rd, int index);
    radial getListLRad(listLRad l, int index);
    int lengthListLRad(listLRad l);
    void freeListLRad(listLRad l);

    typedef struct{
        vecI position;
        vecF norm;
        color c;
        vecF abc;
        float at;
        int ang;
    }spot;
    spot newSpot(vecI position,color c,vecF abc,int ang,int ang_x,int ang_y,int ang_z);

    typedef struct SPOTS{
        spot sp;
        int index,length;
        struct SPOTS * next;
    }ListLSpot;

    typedef ListLSpot * listLSpot;

    listLSpot startListLSpot(spot sp);
    void addListLSpot(listLSpot l, spot sp);
    void putsListSpot(listLSpot l , spot sp, int index);
    spot getListLSpot(listLSpot l, int index);
    int lengthListLSpot(listLSpot l);
    void freeListLSpot(listLSpot l);


    color diffuseLightPoint(listLRad rd,listLSpot sp,vecI point, vecF n);
    color specularLightPoint(int n_s,listLRad rd,listLSpot sp, vecI point,vecF n);

    void takePhotoScene(camera cam,model m,listLRad rLights,listLSpot sLights);
    void rasterModelLight(model m,resolution res,camera c1,listLRad rd,listLSpot sp);



    //Testing:
    void printRadial(radial rd);
    void printSpot(spot sp);
    //-----------------------------------------------------------------------------//
    /////////////////////////////////////////////////////////////////////////////////
    //-----------------------------Miscellaneous-----------------------------------//
    void swap(int *a, int *b);
    vecI findVertexFace(model m,int face);
    vecF calculateReflected(vecF l, vecF n);



#endif
