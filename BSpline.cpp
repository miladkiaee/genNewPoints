//
// Created by milad on 30/06/17.
//

#include "BSpline.h"

void BSpline::setNumPoints(size_t np) {
    num_points = np;
}


void BSpline::addNextPoint(Point p) {
    all_points.push_back(p);

}

size_t BSpline::getNumPoints() {
    return num_points;
}

Point BSpline::getPoint(size_t i) {
    return all_points[i];
}

void BSpline::print(){
    std::cout << "BSpline:" << std::endl;
    for (size_t i=0; i<num_points; i++){
        all_points[i].print();
    }
}