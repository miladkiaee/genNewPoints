//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_MANAGER_H
#define GENNEWPOINTS_MANAGER_H
#include "PtsLis.h"

class Manager {
private:
    double delta;
    PtsLis parent_geom;
    std::vector <PtsLis> branch_geoms;
    std::vector<Point> optimization_points;
    //double value specifies the x value for each point (each point have one component to the
    // gradient vector), points here are basically optimization points
    std::vector<std::pair<Point, double> > gradient_vector;
public:
    Manager(double, PtsLis);
    void setOptimizationPoints();
    void calcGradientVector();
    void generateBranches();
    void genPtsLisFiles();
};

#endif //GENNEWPOINTS_MANAGER_H