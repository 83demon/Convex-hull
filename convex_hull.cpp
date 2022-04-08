//
// Created by vo1 on 21.11.20.
//

#include "convex_hull.h"
Point ConvexHull::q;

void ConvexHull::sort_points_by_x(std::vector<Point> &points) {
    std::sort(points.begin(),points.end(), x_comparison);
}

std::vector<Point> ConvexHull::create_convex_hull(std::vector<Point> &points, std::list<SceneState> &frames, int depth, bool half) {
    //half == true if half is above the slope;
    if(points.empty() || points.size()==1 || points.size()==2){
        SceneState res = SceneState{points};
        return points;
    }
    sort_points_by_x(points);
    std::vector<Point> res;
    res.reserve(points.size()); //should I?
    std::vector<Point> max_area_vec;
    std::vector<std::pair<Point, float>> area_vec, max_angle_vec; // points with area/max_area triangles
    float max_area = 0, max_angle = 0;
    Point left = points[0], right = points.back();

    if(depth==0){
        std::vector<Point> s1; //upper half-plane
        std::vector<Point> s2; //lower half-plane
        std::vector<Point> s1_res, s2_res;
        res.push_back(left);
        res.push_back(right);
        std::pair<std::vector<Point>, std::vector<Point>> splitted = split(points, left, right);
        s1 = splitted.first, s2 = splitted.second;
        s1_res = create_convex_hull(s1, frames, depth+1,true);
        for(int i=0;i<s1_res.size();i++){
            res.push_back(s1_res[i]);
        }
        s2_res = create_convex_hull(s2, frames, depth+1, false);
        for(int i=0;i<s2_res.size();i++){
            res.push_back(s2_res[i]);
        }

        return res;
    }

    for(auto point: points){
        Triangle tri = Triangle(left,point,right);
        float current_area = Triangle::area(tri);
        if(current_area>max_area){
            max_area=current_area;
            area_vec.emplace_back(point,current_area);
        }
    }

    sort_pairs_by_second_arg(area_vec);
    int times = count_value(area_vec, max_area);
    max_area_vec.reserve(times);
    for(int i=0;i<times;i++){
        max_area_vec.push_back(area_vec[i].first);
    }

    if(max_area_vec.size()==1){
        res.push_back(max_area_vec[0]);
    }
    else if(max_area_vec.size()>1){
        for(auto point: max_area_vec){
            float current_angle = Point::angle(left,point,right);
            if(current_angle>max_angle){
                max_angle = current_angle;
                max_angle_vec.emplace_back(point,current_angle);
            }
        }
        sort_pairs_by_second_arg(max_angle_vec);
        int times_angle = count_value(max_angle_vec, max_angle);
        for(int i=0;i<times_angle;i++){
            res.push_back(max_angle_vec[i].first);
        }
    }

    std::vector<Point> s1l={}, s1r={}, s2l={}, s2r={};
    if(res.size()==1){
        std::pair<std::vector<Point>, std::vector<Point>> splitted_l = split(points, left, res[0]);
        s1l = splitted_l.first, s2l = splitted_l.second;
        std::pair<std::vector<Point>, std::vector<Point>> splitted_r = split(points, res[0], right);
        s1r = splitted_r.first, s2r = splitted_r.second;
    }
    else if(res.size()==2){
        std::pair<std::vector<Point>, std::vector<Point>> splitted_l = split(points, left, res[0]);
        s1l = splitted_l.first, s2l = splitted_l.second;
        std::pair<std::vector<Point>, std::vector<Point>> splitted_r = split(points, res.back(), right);
        s1r = splitted_r.first, s2r = splitted_r.second;
    }
    if(half){
        std::vector<Point> s1l_res, s1r_res;
        s1l_res = create_convex_hull(s1l, frames, depth+1,true);
        for(auto point: s1l_res){
            res.push_back(point);
        }
        s1r_res = create_convex_hull(s1r, frames, depth+1, true);
        for(auto point: s1r_res){
            res.push_back(point);
        }
        return res;
    }
    else{
        std::vector<Point> s2l_res, s2r_res;
        s2l_res = create_convex_hull(s2l, frames, depth+1,false);
        for(auto point: s2l_res){
            res.push_back(point);
        }
        s2r_res = create_convex_hull(s2r, frames, depth+1, false);
        for(auto point: s2r_res){
            res.push_back(point);
        }
        return res;
    }
}


std::pair<std::vector<Point>, std::vector<Point>> ConvexHull::split(std::vector<Point> &points, Point &left, Point &right) {
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

bool ConvexHull::area_comparison(std::pair<Point, float> &p1, std::pair<Point, float> &p2) {
    return p1.second>p2.second;
}

void ConvexHull::sort_pairs_by_second_arg(std::vector<std::pair<Point, float>> &vector) {
    std::sort(vector.begin(),vector.end(),area_comparison);
}

int ConvexHull::count_value(std::vector<std::pair<Point, float>> &vector, float &value) {
    int times = 0;
    for(auto pair:vector){
        if(pair.second==value){
            times++;
        }
    }
    return times;
}

SceneState ConvexHull::create_hull(std::vector<Point> &points, std::list<SceneState> &frames) {
    std::vector<Point> points_ = create_convex_hull(points,frames,0,true);
    SceneState res = SceneState {points};
    GrahamScan::calculate_q(points);
    std::sort(points_.begin(),points_.end(),GrahamScan::polar_angles_sort);
    for(int i=0;i<points_.size();i++){
        res.points[Point::find_point(points,points_[i])].color = res.good_color;
        if(i>0){res.create_line(points_[i-1],points_[i],res.good_color);}
    }
    res.create_line(points_.back(),points_[0],res.good_color);
    return res;
}

bool ConvexHull::x_comparison(Point &p1, Point &p2) {
    return p1.get_x()<p2.get_x();
}

