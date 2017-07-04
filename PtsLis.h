//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_PTSLIS_H
#define GENNEWPOINTS_PTSLIS_H


#include "BSpline.h"
#include <fstream>
#include <sstream>

class PtsLis {
private:
    size_t id;
    std::string input_file_name;
    std::string output_file_name;
    std::vector<Point> control_points;
    std::vector<BSpline> bsplines;
    std::vector<double> optimization_space;
public:
    void setInputFileName(std::string);
    std::string getInputFileName();
    void setOutputFileName(std::string);
    std::string getOutputFileName();
    void setControlPoints(std::vector<Point>);
    void setBSplines(std::vector<BSpline>);
    void setOptimizationSpace();
    void readFile();
    void printFile();

};


#endif //GENNEWPOINTS_PTSLIS_H
