//
// Created by milad on 30/06/17.
//

#ifndef GENNEWPOINTS_POINT_H
#define GENNEWPOINTS_POINT_H


#include <cstdio>

class Point {
private:
    size_t flag;
    double x;
    double y;
    double z;
public:
    Point(size_t, double, double, double);
    double getX();
    double getY();
    double getZ();
    void setFlag(size_t);
    void setX(double);
    void setY(double);
    void setZ(double);
};


#endif //GENNEWPOINTS_POINT_H
