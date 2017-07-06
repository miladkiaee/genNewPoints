//
// Created by milad on 04/07/17.
//

#include "Manager.h"

Manager::Manager(double d, PtsLis ptslis)
{
    delta = d;
    parent_geom = ptslis;
}

void Manager::setOptimizationPoints()
{
    // we set the first index for the spline number
    // second index for the index within the spline
    // third index should be x y or z for now we
    // consider all to be 0 showing x variation only

}

void Manager::calcGradientVector()
{

}

void Manager::genPtsLisFiles() {
    size_t N = parent_geom.getPoints().size();

    for (size_t i=0; i<N; i++){
        std::ofstream file;
        PtsLis ptslis;
        ptslis = parent_geom;
        ptslis.differOnePoint(i, delta);
        std::ostringstream oss;
        std::string s;
        oss << "_" << i;
        s = ptslis.getInputFileName() + oss.str();
        ptslis.setOutputFileName(s.c_str());
        ptslis.printFile();
        file.close();
    }
}
