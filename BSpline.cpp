//
// Created by milad on 30/06/17.
//

#include "BSpline.h"

BSpline::BSpline(size_t np) {
    num_points = np;
}

void BSpline::changeNumPts(size_t np) {
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

