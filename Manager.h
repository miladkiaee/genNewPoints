//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_MANAGER_H
#define GENNEWPOINTS_MANAGER_H
#include "PtsLis.h"

class Manager {
private:
    size_t n_lines;
    double delta;
    double gamma;
    PtsLis prevPtsLis_0;
    PtsLis ptsLis_0;
    PtsLis newPtsLis_0;
    std::vector<double> grad;
    std::vector<double> grad_prev;
public:
    Manager(double, PtsLis);
    Manager(double, double);
    Manager(double);
    Manager();
    void setNLines(size_t);
    size_t getNLines();
    void update();
    void printPtsLisFiles();
    void printGrad();
    void printNewMasterPtsLis();
};

#endif //GENNEWPOINTS_MANAGER_H