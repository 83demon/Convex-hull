//
// Created by vo1 on 21.11.20.
//

#include "triangle.h"

float Triangle::area(Triangle &tri) {
    float ab = Point::distance(tri.a,tri.b);
    float ac = Point::distance(tri.a,tri.c);
    float bc = Point::distance(tri.b,tri.c);
    float p = (ab+ac+bc)/2; // half_perimeter
    return sqrt((p*(p-ab)*(p-ac)*(p-bc)));
}

float Triangle::oriented_area(Triangle &tri) {
    return 0.5*(tri.a.get_x()*tri.b.get_y()+tri.b.get_x()*tri.c.get_y()+tri.a.get_y()*tri.c.get_x()
               -tri.c.get_x()*tri.b.get_y()-tri.c.get_y()*tri.a.get_x()-tri.b.get_x()*tri.a.get_y());
}

