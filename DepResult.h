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
    double norm;
public:
    DepResult();
    DepResult &operator=(DepResult);
    std::vector<ResultMatrix> getRegionalDep();
    std::vector<ResultMatrix> getRefRegionalDep();
    void setNumberOfInjectionPoints(size_t);
    void readLogFiles(std::string);
    void F();
    void addToNormFile();
};


#endif //GENNEWPOINTS_DEPRESULT_H
