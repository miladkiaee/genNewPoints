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
    ResultMatrix();
    ResultMatrix(size_t, size_t);
    size_t getM();
    size_t getN();
    void setM(size_t);
    void setN(size_t);
    double getA(size_t, size_t);
    void setA(size_t, size_t, double);
    void addToA(size_t, size_t, double);
    void devideABy(size_t);
};


#endif //GENNEWPOINTS_RESULTMATRIX_H
