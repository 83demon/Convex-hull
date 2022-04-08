//
// Created by vo1 on 19.11.20.
//

#include "graphics.h"

void Graphics::init() {
    window.create(sf::VideoMode(window_width,window_height),"LAB");
    load_font("/home/vo1/Documents/CLionProjects/OOP/lab3/OpenSans-Regular.ttf");
    create_buttons();
}

void Graphics::load_font(const char* path) {
    if(!font.loadFromFile(path)){
        throw "Error loading text";
    }
}

void Graphics::load_points_from_file(const char *path) {
    file_points = Reader::read(path);
}

void Graphics::create_buttons() {
    Button alg1(window_width/2-3*width_rect/2,window_height/2-height_rect,width_rect,height_rect,font,
                "Fortune's",text_size,
                text_color,idle_color,hover_color,active_color);
    Button alg2(alg1.get_x()+alg1.get_width(),alg1.get_y(),width_rect,height_rect,font,
                "Delaunay",text_size,
                text_color,idle_color,hover_color,active_color);
    Button alg3(alg1.get_x()+2*alg1.get_width(),alg1.get_y(),width_rect,height_rect,font,
                "Kirkpatrick",text_size,
                text_color,idle_color,hover_color,active_color);
    Button alg4(alg1.get_x(),alg1.get_y()+alg1.get_height(),width_rect,height_rect,font,
                "Andrew & Jarvis",text_size,
                text_color,idle_color,hover_color,active_color);
    Button alg5(alg4.get_x()+alg4.get_width(),alg4.get_y(),width_rect,height_rect,font,
                "Graham's",text_size,
                text_color,idle_color,hover_color,active_color);
    Button alg6(alg4.get_x()+2*alg4.get_width(),alg4.get_y(),width_rect,height_rect,font,
                "Convex Hull",text_size,
                text_color,idle_color,hover_color,active_color);
    Button generate(window_width/2-3*width_rect/2,window_height*(1-offset_y),width_rect/1.5,
                    height_rect/1.5,font,"Generate",text_size-5,
                    text_color,idle_color,hover_color,active_color);
    Button read_from_file(generate.get_x()+5*generate.get_width(),generate.get_y(),generate.get_width(),
                    generate.get_height(),font,"Read file",text_size-5,
                    text_color,idle_color,hover_color,active_color);
    Button back(generate.get_x()-generate.get_width(),generate.get_y(),generate.get_width(),
                generate.get_height(),font,"Back",text_size-5,
                    text_color,idle_color,hover_color,active_color);
    Button start(generate.get_x()+4*generate.get_width(),generate.get_y(),generate.get_width(),
                generate.get_height(),font,"Start",text_size-5,
                text_color,idle_color,hover_color,active_color);
    Button clear(generate.get_x()+3*generate.get_width(),generate.get_y(),generate.get_width(),
                 generate.get_height(),font,"Clear points",text_size-5,
                 text_color,idle_color,hover_color,active_color);
    Button clear_input(generate.get_x()+2*generate.get_width(),generate.get_y(),generate.get_width(),
                 generate.get_height(),font,"Clear input",text_size-5,
                 text_color,idle_color,hover_color,active_color);
    input_field = InputField(generate.get_x()+generate.get_width(),generate.get_y(),generate.get_width(),
                           generate.get_height(),font,"Input an int",text_size-5,
                           text_color,idle_color,idle_color,active_color);
    algorithms_buttons = {alg1,alg2,alg3,alg4,alg5,alg6};
    other_buttons = {back,generate,clear_input,clear,start,read_from_file};

}

//void Graphics::paint() {
//    alg1.setFillColor(sf::Color(12,123,132,150));
//    alg2.setFillColor(sf::Color(123,9,150));
//    alg3.setFillColor(sf::Color(123,123,132,150));
//    alg4.setFillColor(sf::Color(38,123,1,150));
//    alg5.setFillColor(sf::Color(13,93,75,150));
//    alg6.setFillColor(sf::Color(12,143,92,150));
//}


void Graphics::draw() {
    init();
    SceneState final_frame;
    clock_t prev_time, cur_time;
    window.clear();
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        current_state = States::Menu;
                        load_from_file = false;
                        points.clear();
                        n_clicks=0;
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (current_state == States::Menu) {
                        for (int i = 0; i < algorithms_buttons.size(); i++) {
                            algorithms_buttons[i].update(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                        }
                    } else {
                        for (int i = 0; i < other_buttons.size(); i++) {
                            other_buttons[i].update(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                    break;
                case sf::Event::TextEntered:
                    if (input_field.focus()){
                        input_field.handle(event.text.unicode);
                    }
                case sf::Event::MouseButtonReleased:{
                    auto pos = sf::Mouse::getPosition(window);
                    input_field.set_focus(false);
                    if (input_field.contains(sf::Vector2f(pos))) {
                        input_field.set_focus(true);
                    }
                    if(0<=event.mouseButton.x && event.mouseButton.x<=window_width &&
                            0<=event.mouseButton.y && n_clicks>1 &&
                            event.mouseButton.y<=(window_height*(1-offset_y)-2*Point::get_radius())){
                        points.emplace_back(Point(event.mouseButton.x,event.mouseButton.y));
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed: {
                    n_clicks++;
                    if(current_state==States::Menu){
                        for (int i = 0; i < algorithms_buttons.size(); i++) {
                            algorithms_buttons[i].update(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            if (algorithms_buttons[i].is_pressed()){
                                current_state = States::Wait;
                                index_alg = i;
                            }
                        }
                    }
                    else{
                        for(int i = 0; i < other_buttons.size(); i++) {
                            other_buttons[i].update(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                            if (other_buttons[0].is_pressed()) {
                                current_state = States::Menu;
                                load_from_file = false;
                                points.clear();
                                n_clicks=0;
                            }
                            else if(other_buttons[1].is_pressed()){
                                int number = std::stoi((std::string)input_field.get_str());
                                generate(number);
                            }
                            else if(other_buttons[2].is_pressed()){
                                input_field.clear_text();
                            }
                            else if(other_buttons[3].is_pressed()){
                                points.clear();
                                current_state = States::Wait;
                            }
                            else if(other_buttons[4].is_pressed()){
                                final_frame = algorithms[index_alg]->create_hull(points, frames);
                                current_state = States::Animation;
                                prev_time = clock();
                            }
                            else if(other_buttons.back().is_pressed()){
                                load_from_file = true;
                                if(file_points.empty()){
                                    load_points_from_file("/home/vo1/Documents/CLionProjects/OOP/lab3/points.txt");
                                }
                                points.insert(points.end(),file_points.begin(),file_points.end());
                                for(auto p:points){
                                    p.draw(window);
                                }
                            }
                    }
                    break;
                }
                default:
                    break;
                }
            }
        window.clear();
        switch (current_state) {
            case States::Menu:
                for (auto button:algorithms_buttons) {
                    button.draw(window);
                }
                break;
            case States::Wait:
                for(auto button:other_buttons) {
                    button.draw(window);
                }
                input_field.draw(window);
                if(!points.empty()){
                    for(auto p:points){
                        p.draw(window);
                    }
                }
                break;
            case States::Animation:
            {
                for(auto button:other_buttons){
                    button.draw(window);
                }
                input_field.draw(window);
                if(!frames.empty()){frames.front().draw(window);}
                cur_time = clock();
                if((float)(cur_time-prev_time)/(float)CLOCKS_PER_SEC*2>interval){
                    if (!frames.empty()) {
                        frames.pop_front();
                    } else {
                        current_state = States::Result;
                    }
                    prev_time = cur_time;
                }
                break;
            }
            case States::Result:
                final_frame.draw(window);
                for(auto button:other_buttons){
                    button.draw(window);
                }
                input_field.draw(window);
                break;
        }
        window.display();
    }

}

void Graphics::generate(int number) {
    for(int i=0;i<number;i++){
        points.emplace_back(Point(rand()%window_width-2*Point::get_radius(),
                                  rand()%((int)(window_height*(1-offset_y)-2*Point::get_radius()))));
    }
}
