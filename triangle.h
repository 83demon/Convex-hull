//
// Created by vo1 on 21.11.20.
//

#pragma once
#include "point.h"
class Triangle{
    Point a,b,c;
public:
    static float area(Triangle &tri);
    static float oriented_area(Triangle &tri);
    Triangle(Point &x, Point &y, Point &z){a=x,b=y,c=z;}
};
