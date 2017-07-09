//
// Created by milad on 04/07/17.
//

#ifndef GENNEWPOINTS_PTSLIS_H
#define GENNEWPOINTS_PTSLIS_H


#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include "Point.h"

class PtsLis {
private:
    std::string input_file_name;
    std::string output_file_name;
    std::vector<Point> points;
    size_t n_points;
    //std::vector<BSpline> bsplines;


public:
    PtsLis & operator= (PtsLis);
    void setInputFileName(std::string);
    std::string getInputFileName();
    void setOutputFileName(std::string);
    std::string getOutputFileName();
    size_t getNumPoints();
    void setNumPoints(size_t);
    //std::vector <BSpline> getBSplines();
    std::vector <Point> getPoints();
    void setPoints(std::vector<Point>);
    //void setBSplines(std::vector<BSpline>);
    void differOnePoint(size_t, double);
    void readFile();
    void printFile();
};


#endif //GENNEWPOINTS_PTSLIS_H
