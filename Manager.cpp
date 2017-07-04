//
// Created by milad on 04/07/17.
//

#include "Manager.h"

Manager::Manager(PtsLis ptslis): delta(0.00001){
    parent = ptslis; // @todo copy constuctor should be made for this to work
}



void Manager::setOptimizationPoints() {
    // we set the first index for the spline number
    // second index for the index wihtin the spline
    // third index should be x y or z for now we
    // consider all to be 0 showing x variation only
    for (size_t i1=0; i1<parent.getBSplines().size(); i1++ ){
        for (size_t i2=0; i2<parent.getBSplines()[i1].getNumPoints()-2; i2++){
            if (!parent.getBSplines()[i1].getPoint(i2).isFixed()){
                optimization_points.push_back(parent.getBSplines()[i1].getPoint(i2));
            }
        }
    }
}


