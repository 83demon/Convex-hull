//
// Created by vo1 on 23.11.20.
//

#pragma once
#include <utility>
#include "point.h"
class Line{
    static float k,b;
public:
    Line(){};
    Line(float m, float t){k=m,b=t;}
    Line(Point &m, Point &t){calculate_slope_eq(m,t);}
    float get_k();
    float get_b();
    static bool point_above_or_on_the_slope(Point &p, Line &line);
    static bool point_above_the_slope(Point &p, float k, float b);
    static bool point_below_the_slope(Point &p, float k, float b);
    static bool point_below_the_slope(Point &p, Line &line);
    static bool point_above_the_slope(Point &p, Line &line);
    static bool point_to_the_left_of_or_on_slope(Point &constanta, Point &p); // when slope is x=const;
    static bool point_to_the_right_of_or_on_slope(Point &constanta, Point &p); // when slope is x=const;
    static Line calculate_slope_eq(Point &p1, Point &p2);
};
