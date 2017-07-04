//
// Created by milad on 04/07/17.
//

#include "ResultMatrix.h"

size_t ResultMatrix::getM() {
    return m;
}

size_t ResultMatrix::getN() {
    return n;
}

size_t ResultMatrix::getA(size_t i, size_t j) {
    return a[i][j];
}