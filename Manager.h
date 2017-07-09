//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_MANAGER_H
#define GENNEWPOINTS_MANAGER_H
#include "PtsLis.h"

class Manager {
private:
    double delta;
    double gamma;
    PtsLis parentPtsLis;
    std::vector <PtsLis> branch_geoms;
    std::vector<Point> optimization_points;
    //double value specifies the x value for each point (each point have one component to the
    // gradient vector), points here are basically optimization points
    std::vector<double> gradient_vector; // normalized
public:
    Manager(double, PtsLis);
    Manager();
    Manager(double, double);
    void setOptimizationPoints();
    void update();
    void generateBranches();
    void genPtsLisFiles();
};

#endif //GENNEWPOINTS_MANAGER_H