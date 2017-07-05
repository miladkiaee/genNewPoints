//
// Created by milad on 30/06/17.
//

#include "Point.h"

Point::Point (int f, double xx, double yy, double zz){
    flag = f;
    x = xx;
    y = yy;
    z = zz;
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

double Point::getZ() {
    return z;
}

int Point::getFlag() {
    return flag;
}

void Point::setFlag(size_t f) {
    flag = f;
}

void Point::setX(double xx){
    x = xx;
}

void Point::setY(double yy){
    y = yy;
}

void Point::setZ(double zz){
    z = zz;
}

void Point::print(){
    std::cout << "Point: " << x
              << " " << y
              << " " << z << std::endl;
}