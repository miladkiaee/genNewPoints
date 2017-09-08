//
// Created by milad on 04/07/17.
//

#include <cmath>
#include "Manager.h"
#include "math.h"
#include <stdlib.h>

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

    std::ifstream norm_file;
    std::string line;

    std::vector<double> norms;
    // read norms from norm.tmp file which is written by depresult class
    norm_file.open("norm.tmp");
    if (norm_file.is_open()) {
        while (std::getline(norm_file, line)) {
            std::stringstream ss(line);
            double nn;
            ss >> nn;
            norms.push_back(nn);
        }
    } else {
        std::cout << "Error! check if the norm.tmp file can be opened ..."
                  << std::endl;
    }
    norm_file.close();

    std::ifstream grad_file;
    //read the current grad_prev from previous grad file still here
    if (std::ifstream("grad-prev")) {
        grad_file.open("grad-prev");
        while (std::getline(grad_file, line)) {
            std::stringstream ss(line);
            double gg;
            ss >> gg;
            grad_prev.push_back(gg);
        }
    } else {
        // if there is no grad file already existing
        for (size_t i = 0; i <= n_lines; i++) {
            grad_prev.push_back(0);
        }
    }
    grad_file.close();

    //calculate the current step explicit gradient
    double D;
    for (size_t i = 0; i <= n_lines; i++) {
        D = (norms[i] - norms[0]) / delta;
        grad.push_back(D); // this is explicit grad{n}
    }

    // normalizing the gradient vector
    double sum = 0;
    for (size_t i = 0; i <= n_lines; i++) {
        sum += pow(grad[i], 2);
    }
    sum = sqrt(sum);
    double SMALL = 1e-6;
    if (sum > SMALL) {
        for (size_t i = 0; i <= n_lines; i++) {
            grad[i] = grad[i] / sum;
        }
    } else {
        for (size_t i = 0; i <= n_lines; i++) {
            std::cout << "gradient vector length is very small so set to zero! " << std::endl;
            grad[i] = 0;
        }
    }
    //

    /*
    if (std::ifstream("pts.lis-prev") && sum > SMALL) {
        prevPtsLis_0.setInputFileName("pts.lis-prev");
        prevPtsLis_0.readFile();
        double gamma_denom = 0;
        double gamma_numer = 0;
        for (size_t i = 1; i <= n_lines; i++) {
            gamma_denom += pow(grad[i] - grad_prev[i], 2);

            gamma_numer += (
                                   ptsLis_0.getPoints()[i].getX() -
                                   prevPtsLis_0.getPoints()[i].getX()
                           ) * (grad[i] - grad_prev[i]);
        }
        if (gamma_denom == 0){
            gamma = delta;
        } else {
            gamma = gamma_numer / gamma_denom;
        }
    } else {
        std::cout << "no previous pts.lis-prev found. "
                "using delta as gamma .." << std::endl;
        gamma = delta;
    }
     */

    gamma = delta;

    // gamma = delta; //to be reformed and the above commented section to be implemented
    newPtsLis_0 = ptsLis_0;
    if (sum > SMALL && gamma > SMALL) {
        for (size_t i = 1; i <= n_lines; i++)
            newPtsLis_0.differOnePoint(i - 1, -1.0 * gamma * grad[i]);
    } else {
            std::cout << "gradient lenght or gamma is too small!" << std::endl;
            for (size_t i = 1; i <= n_lines; i++)
                newPtsLis_0.differOnePoint(i - 1, -1.0 * grad[i]);
    }

    std::ofstream gamma_file;
    gamma_file.open("gamma-update");
    gamma_file << gamma << std::endl;
    gamma_file.close();
}

void Manager::printGrad() {
    std::ofstream file;
    file.open("grad-update");
    for (size_t i=0; i<=n_lines; i++){
        file << grad[i] << std::endl;
    }
    file.close();
}

void Manager::printNewMasterPtsLis() {
    newPtsLis_0.setOutputFileName("pts.lis-update");
    newPtsLis_0.printFile();
}