//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_RESULTMATRIX_H
#define GENNEWPOINTS_RESULTMATRIX_H

#include <iostream>
#include <vector>

class ResultMatrix {
private:
    size_t m; // number of rows
    size_t n; // number of columns
    std::vector< std::vector<double> > a;
public:
    size_t getM();
    size_t getN();
    double getA(size_t, size_t);
};


#endif //GENNEWPOINTS_RESULTMATRIX_H
