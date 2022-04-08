//
// Created by vo1 on 29.11.20.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};
class Button {
protected:
    unsigned short button_state;
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
    std::string input_str;
    sf::Color idle_color, hover_color, active_color, text_color;
public:
    Button(){};
    sf::String get_str();
    float get_x();
    float get_y();
    float get_height();
    float get_width();
    Button(float x, float y, float width, float height, sf::Font &font_, const std::string& Text, int text_size,
           sf::Color text_color, sf::Color idle_color_, sf::Color hover_color_, sf::Color active_color_);
    void update(sf::Vector2f mouse_pos);
    void draw(sf::RenderWindow &window);
    bool is_pressed();
};
