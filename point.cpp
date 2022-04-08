//
// Created by vo1 on 19.11.20.
//

#include "point.h"
#include <iostream>
float Point::get_x() {
    return x;
}

float Point::get_y() {
    return y;
}

float Point::distance(Point &a, Point &b) {
    return sqrt((pow(a.x-b.x,2)+pow(a.y-b.y,2)));
}

float Point::angle(Point &a, Point &b, Point &c) {
    //returns value in degrees
    float ab = distance(a,b);
    float bc = distance(b,c);
    float ac = distance(a,c);
    return acos((ab*ab+bc*bc-ac*ac)/2/ab/bc) * 360 / 2 / M_PI;
    }

float Point::polar_angle(Point &center, Point &p) {
    float y = p.y-center.y, x = p.x-center.x;
    if(x!=0){
        float res = atan2(y,x)* 180 / M_PI;
        if(res<0){return res+360.f;}
        else{return res;}
    }
    else if(y>0 && x==0){return 90;}
    else if(y<0 && x==0){return 270;}
    else{return 0;}
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << p.x << ","<<p.y;
    return os;
}

bool operator==(Point &a, Point &b) {
    return (a.x==b.x && a.y==b.y);
}

void Point::draw(sf::RenderWindow &window) {
    sf::CircleShape p(radius);
    p.setFillColor(color);
    p.setPosition(x,y);
    window.draw(p);
}

float Point::get_radius() {
    return radius;
}

int Point::find_point(std::vector<Point> &points, Point &value) {
    //returns index
    for(int i=0;i<points.size();i++){
        if(points[i]==value){
            return i;
        }
    }
    return -1;
}

