//
// Created by vo1 on 29.11.20.
//

#include "button.h"


Button::Button(float x, float y, float width, float height, sf::Font &font_, const std::string& Text, int text_size,
               sf::Color text_color_, sf::Color idle_color_, sf::Color hover_color_, sf::Color active_color_) {
    button_state = BTN_IDLE;
    shape.setPosition(x,y);
    shape.setSize(sf::Vector2f(width,height));
    font = font_;
    text.setFont(font_);
    text.setString(Text);
    text_color = text_color_;
    input_str = Text;
    text.setFillColor(text_color);
    text.setCharacterSize(text_size);
    text.setPosition(shape.getPosition().x,shape.getPosition().y+height/4);
    idle_color = idle_color_;
    hover_color = hover_color_;
    active_color = active_color_;
//    shape.setOutlineColor(sf::Color::Yellow);
//    shape.setOutlineThickness(0.5);
    shape.setFillColor(idle_color);


}


void Button::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update(sf::Vector2f mouse_pos) {
    button_state = BTN_IDLE;
    if(shape.getGlobalBounds().contains(mouse_pos)){
        button_state = BTN_HOVER;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            button_state = BTN_PRESSED;
        }
    }
    switch (button_state) {
        case BTN_IDLE:
            shape.setFillColor(idle_color);
            break;
        case BTN_HOVER:
            shape.setFillColor(hover_color);
            break;
        case BTN_PRESSED:
            shape.setFillColor(active_color);
            break;
        default:
            shape.setFillColor(idle_color);
            break;
    }
}

bool Button::is_pressed() {
    return button_state==BTN_PRESSED;
}

float Button::get_x() {
    return shape.getPosition().x;
}

float Button::get_y() {
    return shape.getPosition().y;
}

float Button::get_height() {
    return shape.getGlobalBounds().height;
}

float Button::get_width() {
    return shape.getGlobalBounds().width;
}

sf::String Button::get_str() {
    return text.getString();
}
