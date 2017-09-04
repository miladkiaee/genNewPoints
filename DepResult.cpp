//
// Created by milad on 04/07/17.
//

#include "DepResult.h"
#include "math.h"
#include <stdlib.h>

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

void DepResult::readRefFiles(){
    std::vector <std::string> regions =
            {"vesti", "valve", "olf"
            , "anterior", "posterior", "naso"};
    std::cout << "reading ref files " << std::endl;
    for (size_t i=0; i<6; i++){
        std::ifstream file;
        std::string s;
        std::ostringstream oss;
        oss << "ref_" << regions[i] << ".txt";
        s = oss.str();
        file.open(s.c_str());
        double x0, x1;
        std::string line;
        size_t line_num = 0;
        while (file.is_open() && line_num < 2) {
            getline(file, line);
            std::stringstream ss(line);
            ss >> x0 >> x1;
            x0 /= 100; //change percentage to fraction of 1
            x1 /= 100;
            ref_regional_deps[i].setA(line_num, 0, x0);
            ref_regional_deps[i].setA(line_num, 1, x1);
            line_num++;
        }
        std::cout << i << " " << s << std::endl;
        ref_regional_deps[i].printA(regions[i]);
        file.close();
    }
    std::cout << "- - - - - -" << std::endl;
}

void DepResult::readLogFiles(std::string filename){

    std::ifstream file;
    std::vector <std::string> regions = {"VESTIBULE", "VALVE", "OLF"
            , "ANTERIOR", "POSTERIOR", "NASO"};

    std::vector<double> u0 = {0, 10};
    std::vector<double> diam = {5e-06, 2e-05}; //micron

    std::cout << "reading log files " << std::endl;
    // file format is plog_number_diam_u0
    for (size_t i=1; i<=n_injection_points; i++) {
        for (size_t m=0; m<2; m++) {
            for (size_t n=0; n<2; n++) {
                char c;
                std::string tmp;
                std::vector<std::string> lines;
                std::string line;
                std::ostringstream oss;
                std::string s;
                oss << "_" << i << "_" << diam[m] << "_" << u0[n];
                s = filename + oss.str();
                // std::cout << s << std::endl;
                file.open(s.c_str());
                if (file.is_open()) {
                    while (std::getline(file, line)) {
                        lines.push_back(line);
                    }
                }
                int value;
                for (int j = 0; j < 6; j++) {
                    for (int k = lines.size() - 1; k > 0; k--) {
                        if (lines[k].find(regions[j].c_str()) !=
                                std::string::npos) {
                            std::stringstream ss(lines[k+2]);
                            ss >> c >> tmp >> c >> tmp;
                            std::stringstream tmps(tmp);
                            std::getline(tmps, tmp, ',');
                            value = atoi(tmp.c_str());
                            double dvalue = double(value) / double(num_particle); //deposition fraction of 1
                            regional_deps[j].addToA(m, n, dvalue);
                            break;
                        }
                    }
                }
                file.close();
            }
        }
    }
    for (int j = 0; j < 6; j++) {
        regional_deps[j].devideABy(double(n_injection_points));
        regional_deps[j].printA(regions[j]);
    }
    std::cout << "- - - - - -" << std::endl;
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
    norm = sqrt(norm);
}

void DepResult::addToNormFile() {
    std::ofstream file;
    F();
    file.open("norm.tmp", std::fstream::app);
    std::cout << "adding norm " << norm << " to norm file" << std::endl;
    file << norm << std::endl;
    file.close();
}