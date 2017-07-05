//
// Created by milad on 30/06/17.
//

#ifndef GENNEWPOINTS_POINT_H
#define GENNEWPOINTS_POINT_H


#include <cstdio>
#include <iostream>

class Point {
private:
    int flag; // only points with postive flags are considered to be control points
    double x;
    double y;
    double z;
public:
    Point(int, double, double, double);
    double getX();
    double getY();
    double getZ();
    int getFlag();
    void setFlag(size_t);
    void setX(double);
    void setY(double);
    void setZ(double);
    void print();
};


#endif //GENNEWPOINTS_POINT_H
