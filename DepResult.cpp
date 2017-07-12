//
// Created by milad on 04/07/17.
//

#include "DepResult.h"
#include "math.h"

DepResult::DepResult() {
    regional_deps= std::vector<ResultMatrix> (6); //uses the default constructor of ResultMatrix
    ref_regional_deps= std::vector<ResultMatrix> (6);
    num_particle = 10000;
}

DepResult& DepResult::operator=(DepResult A) {
    regional_deps = A.getRegionalDep();
    ref_regional_deps = A.getRefRegionalDep();
    num_particle = A.getNumParticle();
    return *this;
}

std::vector <ResultMatrix> DepResult::getRegionalDep() {
    return regional_deps;
}

std::vector <ResultMatrix> DepResult::getRefRegionalDep() {
    return ref_regional_deps;
}

void DepResult::setNumberOfInjectionPoints(size_t n) {
    n_injection_points = n;
}

void DepResult::setNumParticle(size_t n) {
    num_particle = n;
}

size_t DepResult::getNumParticle() {
    return num_particle;
}

void DepResult::readLogFiles(std::string filename){

    std::ifstream file;
    std::vector <std::string> regions = {"Vestibule", "Valve", "Olfactory"
            , "Anterior", "Posterior", "Naso"};

    std::vector<double> u0 = {0, 5, 10, 20};
    std::vector<double> diam = {5, 10, 15, 20, 40}; //micron

    // file format is log_number_diam_u0
    for (size_t i=0; i<n_injection_points; i++) {
        for (size_t m=0; m<5; m++) {
            for (size_t n; n<4; n++) {
                char c;
                std::string tmp;
                std::vector<std::string> lines;
                std::string line;
                std::ostringstream oss;
                std::string s;
                oss << "_" << i << diam[m] << "_" << u0[n];
                s = filename + oss.str();
                file.open(s.c_str());
                if (file.is_open()) {
                    while (std::getline(file, line)) {
                        lines.push_back(line);
                    }
                }
                int value;
                for (int j = 0; j < 6; j++) {
                    for (int i = 0; i < lines.size(); i++) {
                        if (lines[i].find(regions[j]) != std::string::npos) {
                            std::stringstream ss(lines[i - 2]);
                            ss >> c >> tmp >> c >> value;
                            value /= num_particle; //normalized deposition
                            regional_deps[j].addToA(m, n, value);
                            break;
                        }
                    }
                }
                file.close();
            }
        }
    }
    for (int j = 0; j < 6; j++) {
        regional_deps[j].devideABy(n_injection_points);
    }
}

void DepResult::F() {
    size_t m = regional_deps[0].getM();
    size_t n = regional_deps[0].getN();

    //homogeneous scalarization using ferobenous as objective function
    for (size_t q=0; q<regional_deps.size(); q++) {
        // over region
        for (size_t i = 0; i < m; i++) {
            // over rows or diameter
            for (size_t j = 0; j < n; j++) {
                // over columns or u0
                norm += pow(regional_deps[q].getA(i, j)
                            - ref_regional_deps[q].getA(i, j), 2);
            }
        }
    }
}

void DepResult::addToNormFile() {
    std::ofstream file;
    F();
    file.open("norm.tmp", std::fstream::app);
    file << norm << std::endl;
    file.close();
}