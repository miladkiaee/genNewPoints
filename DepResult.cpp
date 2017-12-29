//
// Created by milad on 04/07/17.
//

#include "DepResult.h"
#include "math.h"
#include <stdlib.h>
DepResult::DepResult() {
    size_t N = 6;
    regional_deps= std::vector<ResultMatrix> (N);
    ref_regional_deps = std::vector<ResultMatrix> (N);
    ref_sub4_regional_deps = std::vector<ResultMatrix> (N);
    num_particle = 10000;
}

DepResult& DepResult::operator=(DepResult A) {
    regional_deps = A.getRegionalDep();
    ref_regional_deps = A.getRefRegionalDep();
    ref_sub4_regional_deps = A.getRefRegionalDep_sub4();
    num_particle = A.getNumParticle();
    return *this;
}

void DepResult::readFiles(std::string name, std::vector<ResultMatrix> M){
    std::vector <std::string> regions = {"VESTIBULE", "VALVE", "OLF"
            , "ANTERIOR", "POSTERIOR", "NASO"};
    std::cout << "reading ref files " << std::endl;
    for (size_t i=0; i<6; i++){
        std::ifstream file;
        std::string s;
        std::ostringstream oss;
        oss << name.c_str() << regions[i] << ".txt";
        s = oss.str();
        file.open(s.c_str());
        double x0, x1, x2, x3;
        std::string line;
        size_t line_num = 0;
        while (file.is_open() && line_num < 5) {
            getline(file, line);
            std::stringstream ss(line);
            ss >> x0 >> x1 >> x2 >> x3;
            x0 /= 100; //change percentage to fraction of 1
            x1 /= 100;
            x2 /= 100;
            x3 /= 100;
            M[i].setA(line_num, 0, x0);
            M[i].setA(line_num, 1, x1);
            M[i].setA(line_num, 2, x2);
            M[i].setA(line_num, 3, x3);
            line_num++;
        }
        //std::cout << i << " " << s << std::endl;
        M[i].printA(regions[i]);
        file.close();
    }
}

void DepResult::readRefFiles(){
    readFiles("ref_", ref_regional_deps);
    readFiles("ref_sub4_", ref_sub4_regional_deps);
    std::cout << "- - - - - -" << std::endl;
}

void DepResult::findnAdd(std::string s, std::vector<std::string> sv, size_t i, size_t j) {
    int value;
    char c;
    std::vector <std::string> regions = {"VESTIBULE", "VALVE", "OLF"
            , "ANTERIOR", "POSTERIOR", "NASO"};
    for (int j = 0; j < 6; j++) {
        for (int k = sv.size() - 1; k > 0; k--) {
            if (sv[k].find(regions[j].c_str()) != std::string::npos) {
                std::cout << sv[k+2] << std::endl;
                std::stringstream ss(sv[k+2]);
                ss >> c >> s >> c >> s;
                std::stringstream tmps(s);
                std::getline(tmps, s, ',');
                value = atoi(s.c_str());
                double dvalue = double(value) / double(num_particle);
                regional_deps[j].addToA(i, j, dvalue);
                break;
            }
        }
    }
}

void DepResult::readLogFiles(std::string filename){
    std::vector<double> _u0_ = {0, 5, 10, 20};
    std::vector<double> _diam_ = {5e-06, 1e-5, 1.5e-05, 2e-05, 4e-05};
    std::ifstream file;
    std::cout << "reading log files " << std::endl;
    for (size_t i=1; i<=n_injection_points; i++) {
        for (size_t m=0; m<4; m++) {
            for (size_t n=0; n<5; n++) {
                std::string tmp, line, s;
                std::vector<std::string> lines;
                std::ostringstream oss;
                oss << "_" << i << "_" << _diam_[m] << "_" << _u0_[n];
                s = filename + oss.str();
                file.open(s.c_str());

                if (file.is_open())
                    while (std::getline(file, line))
                        lines.push_back(line);

                findnAdd(tmp, lines, m, n);
                file.close();
            }
        }
    }
    // calculate fraction
    for (int j = 0; j < 6; j++) {
        regional_deps[j].devideABy(double(n_injection_points));
    }
    std::cout << "- - - - - -" << std::endl;
}

void DepResult::F() {
    size_t m = regional_deps[0].getM();
    size_t n = regional_deps[0].getN();

    //homogeneous scalarization using ferobenous as objective function
    for (size_t q=0; q<regional_deps.size(); q++) {
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                norm += pow(regional_deps[q].getA(i, j)
                            - ref_regional_deps[q].getA(i, j), 2);
            }
        }
    }
    norm = sqrt(norm);
}

void DepResult::addToNormFile( std::string output) {
    std::ofstream file;
    std::ofstream dakfile; //dakota file
    dakfile.open(output.c_str(), std::fstream::app);
    F();
    file.open("norm.tmp", std::fstream::app);
    file << norm << std::endl;
    std::ostringstream oss;
    oss << "norm";
    std::string s = oss.str();
    dakfile << norm << " " << s << std::endl;
    file.close();
    dakfile.close();
}


std::vector <ResultMatrix> DepResult::getRegionalDep() {
    return regional_deps;
}

std::vector <ResultMatrix> DepResult::getRefRegionalDep() {
    return ref_regional_deps;
}

std::vector <ResultMatrix> DepResult::getRefRegionalDep_sub4() {
    return ref_sub4_regional_deps;
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