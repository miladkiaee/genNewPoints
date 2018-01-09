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

void DepResult::readFiles(std::string name, std::vector<ResultMatrix> M) {
    std::vector <std::string> rgs = {"vesti", "valve", "olf"
            , "turbinates", "naso", "outlet"};
    std::cout << "reading " << name << " files " << std::endl;
    for (size_t i=0; i<6; i++){
        std::ifstream f;
        std::string s;
        std::ostringstream oss;
        oss << name.c_str() << rgs[i] << ".txt";
        s = oss.str();
        f.open(s.c_str());
        double x0, x1, x2, x3;
        std::string ln;
        size_t l = 0;
        while (f.is_open() && l < 5) {
            getline(f, ln);
            std::stringstream ss(ln);
            ss >> x0 >> x1 >> x2 >> x3;
            x0 /= 100; //change percentage to fraction of 1
            x1 /= 100;
            x2 /= 100;
            x3 /= 100;
            M[i].setA(l, 0, x0);
            M[i].setA(l, 1, x1);
            M[i].setA(l, 2, x2);
            M[i].setA(l, 3, x3);
            l++;
        }
        //std::cout << i << " " << s << std::endl;
        M[i].printA(rgs[i]);
        f.close();
    }
}

void DepResult::readRefFiles(){
    std::cout << "####################### " << std::endl;
    readFiles("ref_", ref_regional_deps);
    readFiles("ref_sub4_", ref_sub4_regional_deps);
    std::cout << "#######################" << std::endl;
}

void DepResult::findnAdd(std::vector<std::string> SV, size_t m, size_t n) {
    int v;
    char c;
    std::string S;
    std::vector <std::string> rgs = {"VESTIBULE", "VALVE", "OLF"
            , "ANTERIOR", "POSTERIOR", "NASO", "OUTLET"};
    int index=0;
    for (int j = 0; j < 6; j++) {
        for (int k = SV.size() - 1; k > 0; k--) {
            if (SV[k].find(rgs[j].c_str()) != std::string::npos) {
                //std::cout << SV[k+2] << std::endl;
                if (rgs[j].c_str() == "OUTLET")
                    k = k + 1;
                else
                    k = k + 2;
                std::stringstream ss(SV[k]);
                ss >> c >> S >> c >> S;
                std::stringstream ss2(S);
                std::getline(ss2, S, ',');
                v = atoi(S.c_str());
                double dv = double(v) / double(num_particle);
                if (rgs[j].c_str() == "POSTERIOR") {
                    index --;
                }
                std::cout << dv << " ";
                regional_deps[index].addToA(m, n, dv);
                index ++;
                break;
            }
        }
    }
}

void DepResult::readLogFiles(std::string fn) {
    std::vector<double> _u0_ = {0, 5, 10, 20};
    std::vector<double> _diam_ = {5e-06, 1e-5, 1.5e-05, 2e-05, 4e-05};
    std::ifstream f;
    std::cout << "reading log files " << std::endl;
    for (size_t i=1; i<=n_injection_points; i++) {
        for (size_t m=0; m<4; m++) {
            for (size_t n=0; n<5; n++) {
                std::string ln, s;
                std::vector<std::string> lns;
                std::ostringstream oss;
                oss << "_" << i << "_" << _diam_[m] << "_" << _u0_[n];
                s = fn + oss.str();
                f.open(s.c_str());
                if (f.is_open())
                    while (std::getline(f, ln))
                        lns.push_back(ln);
                findnAdd(lns, m, n);
                std::cout << "line " << s << " : " << std::endl;
                f.close();
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
    norm = norm / 6 / (4*5);
}

void DepResult::addToNormFile( std::string K) {
    std::ofstream f;
    std::ofstream dakf; //dakota file
    dakf.open(K.c_str(), std::fstream::app);
    F();
    f.open("norm.tmp", std::fstream::app);
    f << norm << std::endl;
    std::ostringstream oss;
    oss << "norm";
    std::string s = oss.str();
    dakf << norm << " " << s << std::endl;
    f.close();
    dakf.close();
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