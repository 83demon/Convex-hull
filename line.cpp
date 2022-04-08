//
// Created by vo1 on 23.11.20.
//

#include "line.h"
float Line::k = 0, Line::b = 0;


Line Line::calculate_slope_eq(Point &p1, Point &p2) {
    k = (p2.get_y()-p1.get_y())/(p2.get_x()-p1.get_x());
    b = p1.get_y()-k*p1.get_x();
    return Line(k,b);
}

bool Line::point_above_or_on_the_slope(Point &p, Line &line) {
    if(p.get_y()>=line.get_k()*p.get_x()+line.get_b()){  // if point is on the slope, it won't affect the alg. result, cause area of triangle is 0
        return true;
    }
    return false;
}

float Line::get_k() {
    return k;
}

float Line::get_b() {
    return b;
}

bool Line::point_above_the_slope(Point &p, Line &line) {
    if(p.get_y()>line.get_k()*p.get_x()+line.get_b()){  // if point is on the slope, it won't affect the alg. result, cause area of triangle is 0
        return true;
    }
    return false;
}

bool Line::point_to_the_left_of_or_on_slope(Point &constanta, Point &p) {
    return p.get_x()<=constanta.get_x();
}

bool Line::point_to_the_right_of_or_on_slope(Point &constanta, Point &p) {
    return p.get_x()>=constanta.get_x();
}

bool Line::point_below_the_slope(Point &p, Line &line) {
    if(p.get_y()<line.get_k()*p.get_x()+line.get_b()){  // if point is on the slope, it won't affect the alg. result, cause area of triangle is 0
        return true;
    }
    return false;
}

bool Line::point_above_the_slope(Point &p, float m, float x) {
    if(p.get_y()>m*p.get_x()+x){  // if point is on the slope, it won't affect the alg. result, cause area of triangle is 0
        return true;
    }
    return false;
}

bool Line::point_below_the_slope(Point &p, float m, float x) {
    if(p.get_y()<m*p.get_x()+x){  // if point is on the slope, it won't affect the alg. result, cause area of triangle is 0
        return true;
    }
    return false;
}
