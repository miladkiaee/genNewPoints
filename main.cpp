
#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cstdlib>

int main(int argc, char* argv[]) {

    std::string input = argv[1];

    if (input == "gen_pts_files")
    {
        PtsLis crntPtsLis;
        crntPtsLis.setInputFileName("pts.lis");
        crntPtsLis.readFile();
        double delta = atof(argv[2]);
        Manager manager(delta, crntPtsLis);
        manager.printPtsLisFiles();
    }

    if (input == "append_norm_file")
    {
        DepResult dep;
        dep.setNumberOfInjectionPoints(10);
        dep.readRefFiles(); //reads the reference values
        dep.readLogFiles("plog");
        dep.addToNormFile();
    }

    // generates the new set of ptslis objects
    if (input == "update_pts_grad_files")
    {
        Manager manager;
        manager.update();
        manager.printGrad();
        manager.printNewMasterPtsLis();
    }

    return 0;
}


