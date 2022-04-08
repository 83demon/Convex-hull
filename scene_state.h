//
// Created by vo1 on 28.11.20.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "point.h"
#include <vector>
#include <list>
class SceneState{
public:
    std::vector<Point> points;
    std::vector<sf::VertexArray> lines;
    sf::Color background_color = sf::Color::Black;
    sf::Color current_color = sf::Color::Red,
    good_color = sf::Color::Green, bad_color = sf::Color(235, 151, 78, 255);
    void create_line(Point &a, Point &b, sf::Color color);
    void delete_line(Point &a, Point &b);
    void draw(sf::RenderWindow &window);
};
