
#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"

int main() {
    PtsLis crntPtsLis;
    crntPtsLis.setInputFileName("pts.lis");
    crntPtsLis.setOutputFileName("pts1.lis")
    crntPtsLis.readFile();
    crntPtsLis.printFile();

    DepResult crntDepResult;

    Manager manager();






    return 0;
}


