
#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cstdlib>


int main(int argc, char* argv[]) {
    //PtsLis crntPtsLis;
    //crntPtsLis.setInputFileName("pts.lis");
    //crntPtsLis.setOutputFileName("pts_test.lis");
    //crntPtsLis.readFile();
   // crntPtsLis.printFile();
    double delta = atof(argv[1]);

    DepResult dep;
    dep.readLogFiles("log");
    dep.addToNormFile();

    //Manager manager(delta, crntPtsLis);
    //manager.genPtsLisFiles();

    return 0;
}


