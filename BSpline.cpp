//
// Created by milad on 30/06/17.
//

#include "BSpline.h"

BSpline::BSpline():first_point(0,0,0,0),
                   last_point(0,0,0,0) {
}

void BSpline::setNumPoints(size_t np) {
    num_points = np;
}

void BSpline::setFirstPoint(Point fp) {
    first_point.setX(fp.getX());
    first_point.setY(fp.getY());
    first_point.setZ(fp.getZ());
}

void BSpline::setLastPoint(Point lp) {
    last_point.setX(lp.getX());
    last_point.setY(lp.getY());
    last_point.setZ(lp.getZ());
}

void BSpline::addNextPoint(Point p) {
    internal_points.push_back(p);

}

void BSpline::print(){
    std::cout << "BSpline:" << std::endl;
    first_point.print();
    for (size_t i=0; i<num_points; i++){
        internal_points[i].print();
    }
    last_point.print();
}