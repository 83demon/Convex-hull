//
// Created by vo1 on 19.11.20.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>
#include <cmath>


class Point{
    float x,y;
    static constexpr float radius = 7;
public:
    sf::Color color = sf::Color::Yellow;
    Point(float a, float b){x=a,y=b;}
    Point(){x=0.f,y=0.f;}
    static float get_radius();
    float get_x();
    float get_y();
    static float distance(Point &a, Point &b);
    static float angle(Point &a, Point &b, Point &c);
    static float polar_angle(Point &center, Point &p);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend bool operator ==(Point &a, Point &b);
    void draw(sf::RenderWindow &window);
    static int find_point(std::vector<Point> &points, Point &value);
};

