//
// Created by milad on 04/07/17.
//

#include "ResultMatrix.h"

ResultMatrix::ResultMatrix() {
    m=2;
    n=2;
    a = std::vector <std::vector <double> > (m, std::vector<double> (n));
}

ResultMatrix::ResultMatrix(size_t mm, size_t nn) {
    m = mm;
    n = nn;
    a = std::vector <std::vector <double> > (m, std::vector<double> (n));
}

size_t ResultMatrix::getM() {
    return m;
}

size_t ResultMatrix::getN() {
    return n;
}

void ResultMatrix::setM(size_t mm) {
    m = mm;
}

void ResultMatrix::setN(size_t nn) {
    n = nn;
}

double ResultMatrix::getA(size_t i, size_t j) {
    return a[i][j];
}

void ResultMatrix::setA(size_t i, size_t j, double b) {
    a[i][j] = b;
}

void ResultMatrix::addToA(size_t i, size_t j, double b) {
    a[i][j] += b;
}

void ResultMatrix::printA(std::string name){
    std::cout << " - - - " << std::endl;
    std::cout << name << " matrix = " << std::endl;
    for (size_t i=0; i<m; i++){
        for (size_t j=0; j<n; j++){
            std::cout << " " << a[i][j];
         }
        std::cout << std::endl;
    }
    std::cout << " - - - " << std::endl;
}

void ResultMatrix::devideABy(double k) {
    for (size_t i; i<m; i++){
        for (size_t j=0; j<n; j++){
            a[i][j] /= k;
        }
    }
}