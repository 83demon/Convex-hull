//
// Created by vo1 on 30.11.20.
//

#include "input_field.h"

void InputField::set_focus(bool focus) {
    hasfocus = focus;
    shape.setOutlineThickness(thickness);
    if (focus){
        shape.setOutlineColor(sf::Color::Blue);
    }
    else{
        shape.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
    }

}

InputField::InputField(float x, float y, float width, float height, sf::Font &font_, const std::string &Text,
                       int text_size, sf::Color text_color, sf::Color idle_color_, sf::Color hover_color_,
                       sf::Color active_color_) : Button(x, y, width, height, font_, Text, text_size, text_color,
                                                         idle_color_, hover_color_, active_color_) {

}

bool InputField::contains(sf::Vector2f pos) {
    return shape.getGlobalBounds().contains(pos);
}

void InputField::draw(sf::RenderWindow &window) {
    text.setString(text_);
    Button::draw(window);
}

void InputField::handle(sf::Uint32 uint32) {
    text_ += uint32;
}

sf::String InputField::get_str() {
    return text.getString();
}

void InputField::clear_text() {
    text_ = "";
}

bool InputField::focus() {
    return hasfocus;
}
