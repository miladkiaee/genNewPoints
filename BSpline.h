//
// Created by milad on 30/06/17.
//

#ifndef GENNEWPOINTS_BSPLINE_H
#define GENNEWPOINTS_BSPLINE_H

#include <iostream>
#include <vector>

#include "Point.h"

class BSpline {
private:
    // internal points will have the -1 flag
    size_t num_points;
    std::vector<Point> all_points;
public:
    void setNumPoints(size_t);
    void setFirstPoint(Point);
    void setLastPoint(Point);
    void addNextPoint(Point);
    size_t getNumPoints();
    Point getPoint(size_t);
    void print();
};


#endif //GENNEWPOINTS_BSPLINE_H
