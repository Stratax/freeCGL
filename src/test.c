#include<myGraphics.h>


int main(int argc, char const *argv[]) {

    vector Normal = newVector(0,0,1);
    vector Normal1 = Normal;
    vector Ang =newVector(-1,1,0);
    float cs1 = dotProduct(Normal,Ang)/(magnitudVector(Ang));
    resizeVector(&Normal,2);
    vector r = restVector(Normal,Ang);
    float cs = dotProduct(Normal1,r)/(magnitudVector(Ang));
    printVector(r);
    printf("\n%f, %f\n",cs1,cs);
    return 0;
}
