//
// Created by milad on 04/07/17.
//

#include <cmath>
#include "Manager.h"

Manager::Manager(double d, PtsLis ptslis)
{
    delta = d;
    parentPtsLis = ptslis;
}

Manager::Manager(double d, double g){
    delta = d;
    gamma = g;
}

void Manager::setOptimizationPoints()
{
    // we set the first index for the spline number
    // second index for the index within the spline
    // third index should be x y or z for now we
    // consider all to be 0 showing x variation only

}

void Manager::genPtsLisFiles() {
    size_t N = parentPtsLis.getPoints().size();

    for (size_t i=1; i<=N; i++){
        std::ofstream file;
        PtsLis ptslis;
        ptslis = parentPtsLis;
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

void Manager::update() {
    // this should be called when there are already list of pts.lis_i files
    // exist
    std::vector< PtsLis > ptsliss;
    PtsLis ptslis_org;
    ptslis_org.setInputFileName("pts.lis");
    ptslis_org.readFile();
    size_t n_lines = ptslis_org.getNumPoints();
    ptsliss.push_back(ptslis_org);

    for (size_t i=0; i<n_lines; i++){
        PtsLis ptslis;
        std::ostringstream oss;
        std::string s;
        oss << "_" << i;
        s = "pts.lis" + oss.str();
        ptslis.setInputFileName(s.c_str());
        ptslis.readFile();
        ptsliss.push_back(ptslis);
    }
    std::vector<double> norms;

    std::ifstream file;
    file.open("norm.tmp");
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            //store the lines
            std::stringstream ss(line);
            double nn;
            ss >> nn;
            norms.push_back(nn);
        }
    }
    else
    {
        std::cout << "Error! check if the norm.tmp file can be opened ..."
                  << std::endl;
    }

    file.close();
/*
    double F_old;
    file.open("F"); // f is the norm
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            //Reads the f till the last one
            std::stringstream ss(line);
            ss >> F_old;
        }
    }
    else
    {
        std::cout << "Error! check if the norm.tmp file can be opened ..."
                  << std::endl;
    }
    file.close();
*/
    double D;
    for (size_t i=1; i<n_lines; i++) {
        D =(norms[i]-norms[0])/delta;
        //sum += D*D;
        gradient_vector.push_back(D);
    }

    PtsLis newPtsLis = ptslis_org;
    for (size_t i=1; i<n_lines; i++)
    {
        newPtsLis.differOnePoint(i, gamma*gradient_vector[i]);
    }
}
