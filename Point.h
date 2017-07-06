//
// Created by milad on 30/06/17.
//

#ifndef GENNEWPOINTS_POINT_H
#define GENNEWPOINTS_POINT_H


#include <cstdio>
#include <iostream>

class Point {
private:
    std::string flag; // only points with postive flags are considered to be control points
    double x;
    double y;
    double z;
public:
    Point(std::string, double, double, double);
    double getX();
    double getY();
    double getZ();
    std::string getFlag();
    void setFlag(std::string);
    void setX(double);
    void setY(double);
    void setZ(double);
    void print();
};


#endif //GENNEWPOINTS_POINT_H
