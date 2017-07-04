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
    size_t num_points;
    Point first_point;
    Point last_point;
    std::vector<Point> internal_points;
public:
    BSpline();
    void setNumPoints(size_t);
    void setFirstPoint(Point);
    void setLastPoint(Point);
    void addNextPoint(Point);
    void print();
};


#endif //GENNEWPOINTS_BSPLINE_H
