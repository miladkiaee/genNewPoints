
#include "PtsLis.h"

int main() {
    PtsLis crntPtsLis;
    crntPtsLis.setInputFileName("pts.lis");
    crntPtsLis.setOutputFileName("pts1.lis")
    crntPtsLis.readFile();
    crntPtsLis.printFile();





    return 0;
}


