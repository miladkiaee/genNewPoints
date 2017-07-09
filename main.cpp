
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
        //crntPtsLis.setOutputFileName("pts_test.lis");
        crntPtsLis.readFile();
        //crntPtsLis.printFile();
        double delta = atof(argv[2]);
        Manager manager(delta, crntPtsLis);
        manager.genPtsLisFiles();
    }

    if (input == "append_norm_file")
    {
        DepResult dep;
        dep.setNumberOfInjectionPoints(10);
        dep.readLogFiles("log");
        dep.addToNormFile();
    }

    if (input == "update_pts_F_files")
    {
        double delta = atof(argv[2]);
        double gamma = atof(argv[3]);
        Manager manager(delta, gamma);
        manager.genPtsLisFiles();
        manager.update();
    }

    return 0;
}


