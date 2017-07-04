//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_PTSLIS_H
#define GENNEWPOINTS_PTSLIS_H


#include "BSpline.h"
#include <fstream>
#include <sstream>
#include <utility>

class PtsLis {
private:
    std::string input_file_name;
    std::string output_file_name;
    std::vector<Point> control_points;
    std::vector<BSpline> bsplines;


public:
    void setInputFileName(std::string);
    std::string getInputFileName();
    void setOutputFileName(std::string);
    std::string getOutputFileName();
    std::vector <BSpline> getBSplines();
    std::vector <Point> getControlPoints();
    void setControlPoints(std::vector<Point>);
    void setBSplines(std::vector<BSpline>);
    void readFile();
    void printFile();

};


#endif //GENNEWPOINTS_PTSLIS_H
