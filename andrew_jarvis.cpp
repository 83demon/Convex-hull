//
// Created by vo1 on 23.11.20.
//

#include "andrew_jarvis.h"

std::pair<std::vector<Point>, std::vector<Point>> AndrewJarvis::split(std::vector<Point> &points, Point &left, Point &right) {
    std::vector<Point> s1; //upper half-plane
    std::vector<Point> s2 = {left}; //lower half-plane
    Line slope_eq = Line::calculate_slope_eq(left,right);
    for(auto point : points){
        if(Line::point_above_or_on_the_slope(point,slope_eq)){
            s1.push_back(point);
        }
        else{
            s2.push_back(point);
        }
    }
    s2.push_back(right);
    return std::pair<std::vector<Point>, std::vector<Point>>(s1,s2);
}


SceneState AndrewJarvis::create_hull(std::vector<Point> &points, std::list<SceneState> &frames) {
    std::sort(points.begin(), points.end(), x_comparison);
    SceneState res = SceneState{points}, scene;
    frames.push_back(SceneState{points});
    std::vector<Point> upper_half, lower_half;
    Point left = points[0], right = points.back();
    frames.back().create_line(left,right,scene. bad_color);
    Line line, line1;
    int index;
    bool is_in_hull = false, p_in_right = false, p_in_left = false;
    std::pair<std::vector<Point>, std::vector<Point>> splitted = split(points, left, right);
    upper_half = splitted.first, lower_half = splitted.second;
    Point last = left;
    res.points[0].color = scene.good_color;
    for(int i=0;i<upper_half.size();i++){
        line = Line(last,upper_half[i]);
        scene = frames.back();
        index = Point::find_point(points,upper_half[i]);
        scene.points[index].color = scene.current_color;
        if(i>0){
            scene.create_line(last,upper_half[i],scene.current_color);
        }
        frames.push_back(scene);
        for(int j=i;j<upper_half.size();j++){
            if(last.get_x()==upper_half[j].get_x()){
                if (p_in_right && p_in_left) {
                    p_in_left = false;
                    p_in_right = false;
                    is_in_hull = false;
                    break;
                }}
            if (Line::point_to_the_left_of_or_on_slope(last, upper_half[j])) {
                p_in_left = true;
            } else if (Line::point_to_the_right_of_or_on_slope(last, upper_half[j])) {
                p_in_right = true;
            }
            if(Line::point_above_the_slope(upper_half[j],line.get_k(),line.get_b())){
                is_in_hull = false;
                break;
            }
            else{
                is_in_hull = true;
            }
        }
        scene = frames.back();
        if(is_in_hull){
            scene.create_line(last,upper_half[i],scene.good_color);
            res.create_line(last,upper_half[i],scene.good_color);
            last = upper_half[i];
            scene.points[Point::find_point(points,last)].color = scene.good_color;
            res.points[Point::find_point(points,last)].color = scene.good_color;
            if(last==right){break;}
        }
        else{
            if(!frames.back().lines.empty()){
                scene.points[Point::find_point(points,upper_half[i])].color = scene.bad_color;
                scene.lines.erase(scene.lines.end());
            }
        }
        frames.push_back(scene);
    }
    p_in_right=p_in_left=false;
    last = left;
    for(int i=0;i<lower_half.size();i++){
        line1 = Line(last,lower_half[i]);
        scene = frames.back();
        index = Point::find_point(points,lower_half[i]);
        scene.points[index].color = scene.current_color;
        if(i>0){
            scene.create_line(last,lower_half[i],scene.current_color);
        }
        frames.push_back(scene);
        for(int j=i;j<lower_half.size();j++){
            if(last.get_x()==lower_half[j].get_x()){
                if (p_in_right && p_in_left) {
                    p_in_left = false;
                    p_in_right = false;
                    is_in_hull = false;
                    break;
                }}
            if (Line::point_to_the_left_of_or_on_slope(last, lower_half[j])) {
                p_in_left = true;
            } else if (Line::point_to_the_right_of_or_on_slope(last, lower_half[j])) {
                p_in_right = true;
            }
            if(Line::point_below_the_slope(lower_half[j],line1.get_k(),line1.get_b())){
                is_in_hull = false;
                break;
            }
            else{
                is_in_hull = true;
            }
        }
        scene = frames.back();
        if(is_in_hull){
            scene.create_line(last,lower_half[i],scene.good_color);
            res.create_line(last,lower_half[i],scene.good_color);
            last = lower_half[i];
            scene.points[Point::find_point(points,last)].color = scene.good_color;
            res.points[Point::find_point(points,last)].color = scene.good_color;
        }
        else{
            if(!frames.back().lines.empty()){
                scene.points[Point::find_point(points,lower_half[i])].color = scene.bad_color;
                scene.lines.erase(scene.lines.end());
            }
        }
        frames.push_back(scene);
    }
    //res.create_line(points.back(),points[0],res.good_color);
    return res;
}

bool AndrewJarvis::x_comparison(Point &p1, Point &p2) {
    return p1.get_x()<p2.get_x();
}


