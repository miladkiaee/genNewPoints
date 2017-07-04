//
// Created by milad on 04/07/17.
//

/*
 * regions: 0-Vestibule 1-Valve 2-Valve 3-Anterior 4-Posterior 5-Olfactory 6-Nasopharynx
 * fractions
 */

#ifndef GENNEWPOINTS_DEPRESULT_H
#define GENNEWPOINTS_DEPRESULT_H

#include "PtsLis.h"
#include "ResultMatrix.h"

class DepResult {
private:
    std::vector<ResultMatrix> regional_dep; // contains 6 regional deposition matrices
    std::vector<ResultMatrix> ref_regional_dep; // contains 6 regional reference deposition matrices
    PtsLis* ptslis;
public:
    double calcFeroNorm();
    double F();
};


#endif //GENNEWPOINTS_DEPRESULT_H
