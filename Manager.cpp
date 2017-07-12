//
// Created by milad on 04/07/17.
//

#include <cmath>
#include "Manager.h"

Manager::Manager(double d, PtsLis ptslis)
{
    delta = d;
    ptsLis_0 = ptslis;
    n_lines = ptslis.getNumPoints();
}

Manager::Manager(double d, double g){
    delta = d;
    gamma = g;
}
Manager::Manager(double d) {
    delta = d;
}

Manager::Manager() {

}

void Manager::setNLines(size_t n) {
    n_lines = n;
}

size_t Manager::getNLines() {
    return n_lines;
}

void Manager::printPtsLisFiles() {
    size_t N = ptsLis_0.getPoints().size();

    for (size_t i=0; i<=N; i++){
        std::ofstream file;
        PtsLis ptslis;
        ptslis = ptsLis_0;
        if (i > 0) {
            ptslis.differOnePoint(i - 1, delta);
        }
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

    ptsLis_0.setInputFileName("pts.lis_0");
    ptsLis_0.readFile();
    n_lines = ptsLis_0.getNumPoints();

    prevPtsLis_0.setInputFileName("pts.lis-prev");
    prevPtsLis_0.readFile();

    std::ifstream file;
    std::string line;

    std::vector<double> norms;
    // read norms from norm.tmp file which is written by depresult class
    file.open("norm.tmp");
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
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

    //read the current grad_prev from previous grad file still here
    file.open("grad");
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            double nn;
            ss >> nn;
            grad_prev.push_back(nn);
        }
    }
    else
    {
        std::cout << "Error! check if the norm.tmp file can be opened ..."
                  << std::endl;
    }
    file.close();

    //calculate the current step explicit gradient
    double D;
    for (size_t i=1; i<n_lines; i++) {
        D =(norms[i]-norms[0])/delta;
        grad.push_back(D); // this is explicit grad{n}
    }

    double gamma_denom=0;
    double gamma_numer=0;
    for (size_t i=0; i<n_lines; i++){
        gamma_denom += pow(grad[i]-grad_prev[i], 2);
        gamma_numer += (
                               ptsLis_0.getPoints()[i].getX() -
                                       prevPtsLis_0.getPoints()[i].getX()
                       )*(grad[i]-grad_prev[i]);
    }

    gamma = gamma_numer/gamma_denom;

    newPtsLis_0 = ptsLis_0;
    for (size_t i=1; i<n_lines; i++)
    {
        newPtsLis_0.differOnePoint(i, gamma*grad[i]);
    }
}

void Manager::printGrad() {
    std::ofstream file;
    file.open("grad-update");
    for (size_t i=0; i<n_lines; i++){
        file << grad[i] << std::endl;
    }
}

void Manager::printNewMasterPtsLis() {
    newPtsLis_0.setOutputFileName("pts.lis-update");
    newPtsLis_0.printFile();
}
