//
// Created by vo1 on 23.11.20.
//

#include "points_set.h"
std::pair<PointsSet, PointsSet> PointsSet::split(PointsSet &points, Line &line) {
    Point left = points.set[0], right = points.set.back();
    PointsSet s1; //upper half-plane
    PointsSet s2 ; //lower half-plane
    s2.set.push_back(left);
    Line slope_eq = Line::calculate_slope_eq(left,right);
    for(auto point : points.set){
        if(Line::point_above_or_on_the_slope(point,slope_eq)){
            s1.set.push_back(point);
        }
        else{
            s2.set.push_back(point);
        }
    }
    s2.set.push_back(right);
    return std::pair<PointsSet, PointsSet>(s1,s2);
}

