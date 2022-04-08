//
// Created by vo1 on 28.11.20.
//

#include "scene_state.h"

void SceneState::draw(sf::RenderWindow &window) {
    for(auto l:lines){
        window.draw(l);
    }
    for(auto p:points){
        p.draw(window);
    }
}

void SceneState::create_line(Point &a, Point &b, sf::Color color_) {
    float radius = Point::get_radius();
    sf::VertexArray line(sf::LinesStrip,2);
    line[0].color = line[1].color = color_;
    line[0].position = sf::Vector2f(a.get_x()+radius, a.get_y()+radius);
    line[1].position = sf::Vector2f(b.get_x()+radius, b.get_y()+radius);
    lines.push_back(line);
}

void SceneState::delete_line(Point &a, Point &b) {
    create_line(a,b,background_color);
}
