//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_MANAGER_H
#define GENNEWPOINTS_MANAGER_H
#include "PtsLis.h"
#include "DepResult.h"

class Manager {
private:
    double delta;
    PtsLis parent_geom;
    DepResult parent_result;
    std::vector <PtsLis> branches;
    std::vector<Point> optimization_points;
    //double value specifies the x value for each point (each point have one component to the
    // gradient vector), points here are basically optimization points
    std::vector<std::pair<Point, double> > gradient_vector;
public:
    Manager(PtsLis, DepResult);
    void setOptimizationPoints();
    void calcGradientVector();
    void generateBranches();



};


#endif //GENNEWPOINTS_MANAGER_H
