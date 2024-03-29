//
// Created by milad on 04/07/17.
//

/*
 * regions: 1-Vestibule 2-Valve 3-Olfactory 4-Anterior 5-Posterior 6-Naso
 * fractions
 */

#ifndef GENNEWPOINTS_DEPRESULT_H
#define GENNEWPOINTS_DEPRESULT_H

#include "PtsLis.h"
#include "ResultMatrix.h"

class DepResult {
private:
    size_t n_injection_points; // number of position of particle injector tip
    std::vector<ResultMatrix> regional_deps; // average contains 6 regional deposition matrices
    std::vector<ResultMatrix> ref_regional_deps; // contains 6 regional reference deposition matrices
    std::vector<ResultMatrix> ref_sub4_regional_deps;
    double norm;
    size_t num_particle;
public:
    DepResult();
    DepResult &operator=(DepResult);
    std::vector<ResultMatrix> getRegionalDep();
    std::vector<ResultMatrix> getRefRegionalDep();
    std::vector<ResultMatrix> getRefRegionalDep_sub4();
    void setNumberOfInjectionPoints(size_t);
    void readFiles(std::string, std::vector<ResultMatrix>);
    void readRefFiles();
    void findnAdd(std::vector<std::string>, size_t, size_t);
    void readLogFiles(std::string);
    void setNumParticle(size_t);
    size_t getNumParticle();
    void F();
    void addToNormFile(std::string);
    void print();
};


#endif //GENNEWPOINTS_DEPRESULT_H
