//
// Created by milad on 04/07/17.
//

#include "DepResult.h"
#include "math.h"

double DepResult::calcFeroNorm() {
    double norm = 0;

    size_t m = regional_dep[0].getM();
    size_t n = regional_dep[0].getN();

    //homogeneous scalarization using ferobenous as objective function
    for (size_t q=0; q<regional_dep.size(); q++) {
        // over region
        for (size_t i = 0; i < m; i++) {
            // over rows or diameter
            for (size_t j = 0; j < n; j++) {
                // over columns or u0
                norm += pow(regional_dep[q].getA(i, j) - ref_regional_dep[q].getA(i, j), 2);
            }
        }
    }
    return norm;
}