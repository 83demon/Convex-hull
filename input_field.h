//
// Created by vo1 on 30.11.20.
//

#pragma once
#include "button.h"
class InputField : protected Button{
    bool hasfocus;
    std::string text_ = "30";
    float thickness = 1.f;
public:
    InputField(){};
    InputField(float x, float y, float width, float height, sf::Font &font_, const std::string& Text, int text_size,
           sf::Color text_color, sf::Color idle_color_, sf::Color hover_color_, sf::Color active_color_);
    void set_focus(bool focus);
    bool focus();
    bool contains(sf::Vector2f pos);
    void clear_text();
    sf::String get_str();
    void draw(sf::RenderWindow &window);
    void handle(sf::Uint32);
};
