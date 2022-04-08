//
// Created by vo1 on 19.11.20.
//

#pragma once
#include "reader.h"
#include "button.h"
#include "base_class.h"
#include "fortune.h"
#include "delaunay.h"
#include "kirkpatrick.h"
#include "andrew_jarvis.h"
#include "convex_hull.h"
#include "graham.h"
#include "input_field.h"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Point;
class Triangle;


enum States{Menu,Animation,Wait,Result};


class Graphics{
    const int window_width = 1500, window_height = 1000;
    const int width_rect = 250, height_rect = 75;
    int text_size = 30;
    int index_alg;
    const float offset_y = 0.05; // from 0 to 1;
    float interval = 0.01f; //speed of animation in seconds
    sf::Color text_color = sf::Color::White;
    sf::Color idle_color = sf::Color(90,131,132,150);
    sf::Color hover_color = sf::Color(12,123,132,150);
    sf::Color active_color = sf::Color(5,80,132,150);
    sf::RenderWindow window;
    sf::Font font;
    std::vector<Point> points, file_points;
    std::vector<Button> algorithms_buttons, other_buttons;
    InputField input_field;
    std::vector<BaseAlgorithm*> algorithms = {new Fortune(),new Delaunay(),new Kirkpatrick(),new AndrewJarvis(),
                                              new GrahamScan(), new ConvexHull()};
    States current_state = States::Menu;
    std::list<SceneState> frames;
    bool load_from_file = false;
    unsigned int n_clicks = 0;
    void create_buttons();
    void load_points_from_file(const char* path);
    void load_font(const char* path);
    void generate(int number);
public:
    void init();
    void draw();
};

#include "point.h"
#include "triangle.h"


