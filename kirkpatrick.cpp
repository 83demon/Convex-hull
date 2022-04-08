//
// Created by vo1 on 24.11.20.
//

#include "kirkpatrick.h"


void discard(std::vector<Point> &all_points,std::vector<Point> &points_, int index,std::list<SceneState> &frames){
    if(!frames.back().lines.empty()){
        if(index==-1){index++;}
        SceneState scene = frames.back();
        frames.pop_back();
        scene.points[Point::find_point(all_points,points_[index])].color = scene.bad_color;
        scene.lines.erase(scene.lines.end());
    }
}

SceneState Kirkpatrick::create_hull(std::vector<Point> &points, std::list<SceneState> &frames) {
    SceneState scene = SceneState{points}, res = SceneState{points};
    frames.push_back(scene);
    std::vector<Point> temp_res;
    init_l_and_r(n_buckets);
    bucket_sort(points);
    scene = frames.back();
    scene.points[Point::find_point(points,left_vec[0])].color = scene.current_color;
    frames.push_back(scene);
    scene = frames.back();
    scene.points[Point::find_point(points,left_vec[0])].color = scene.good_color;
    frames.push_back(scene);
    for(int i=1;i<left_vec.size();i++){
        scene = frames.back();
        scene.points[Point::find_point(points,left_vec[i])].color = scene.current_color;
        scene.create_line(left_vec[i-1],left_vec[i],scene.current_color);
        frames.push_back(scene);
        if(i!=left_vec.size()-1){
            Triangle tri = Triangle(left_vec[i-1],left_vec[i],left_vec[i+1]);
            if(Triangle::oriented_area(tri)>=0){
                left_vec.erase(left_vec.begin()+i);
                i--;
                i--;
                discard(points,left_vec,i,frames);
            }
            else{
                scene = frames.back();
                scene.create_line(left_vec[i-1],left_vec[i],scene.good_color);
                scene.points[Point::find_point(points,left_vec[i])].color = scene.good_color;
            }
        }
        else{
            Triangle tri = Triangle(left_vec[i-1],left_vec.back(),left_vec[0]);
            if(Triangle::oriented_area(tri)>=0){
                left_vec.erase(left_vec.begin()+i);
                i--;
                i--;
                discard(points,left_vec,i,frames);
            }
            else{
                scene = frames.back();
                scene.create_line(left_vec[i-1],left_vec[i],scene.good_color);
                scene.points[Point::find_point(points,left_vec[i])].color = scene.good_color;
            }
        }
        frames.push_back(scene);
    }
    std::cout<<"\n";


    scene = frames.back();
    scene.points[Point::find_point(points,right_vec[0])].color = scene.current_color;
    frames.push_back(scene);
    scene = frames.back();
    scene.points[Point::find_point(points,right_vec[0])].color = scene.good_color;
    frames.push_back(scene);
    for(int i=1;i<right_vec.size();i++){
        scene = frames.back();
        scene.points[Point::find_point(points,right_vec[i])].color = scene.current_color;
        scene.create_line(right_vec[i-1],right_vec[i],scene.current_color);
        frames.push_back(scene);
        if(i!=right_vec.size()-1){
            Triangle tri = Triangle(right_vec[i-1],right_vec[i],right_vec[i+1]);
            if(Triangle::oriented_area(tri)<=0){
                right_vec.erase(right_vec.begin()+i);
                i--;
                i--;
                discard(points,right_vec,i,frames);
            }
            else{
                scene = frames.back();
                scene.create_line(right_vec[i-1],right_vec[i],scene.good_color);
                scene.points[Point::find_point(points,right_vec[i])].color = scene.good_color;
            }
        }
        else{
            Triangle tri = Triangle(right_vec[i-1],right_vec.back(),right_vec[0]);
            if(Triangle::oriented_area(tri)<=0){
                right_vec.erase(right_vec.begin()+i);
                i--;
                i--;
                discard(points,right_vec,i,frames);
            }
            else{
                scene = frames.back();
                scene.create_line(right_vec[i-1],right_vec[i],scene.good_color);
                scene.points[Point::find_point(points,right_vec[i])].color = scene.good_color;
            }
        }
        frames.push_back(scene);
    }
    for(auto p:left_vec){
        temp_res.push_back(p);
    }
    for(auto p:right_vec){
        temp_res.push_back(p);
    }
    for(int i=0;i<temp_res.size();i++){
        res.points[Point::find_point(points,temp_res[i])].color = scene.good_color;
        if(i>0){res.create_line(temp_res[i-1],temp_res[i],scene.good_color);}
    }
    return res;

}

void Kirkpatrick::bucket_sort(std::vector<Point> &points) {
    for(int i=0;i<points.size();i++){
        if(left[points[i].get_y()]==-1){
            left[points[i].get_y()]=i;
        }
        else{
            if(points[left[points[i].get_y()]].get_x() > points[i].get_x()){
                left[points[i].get_y()] = i;
            }
        }
        if(right[points[i].get_y()]==-1){
            right[points[i].get_y()]=i;
        }
        else{
            if(points[right[points[i].get_y()]].get_x() < points[i].get_x()){
                right[points[i].get_y()] = i;
            }
        }
    }
    for(int i=0;i<n_buckets;i++){
        if(left[i]!=-1){
            left_vec.push_back(points[left[i]]);
        }
        if(right[i]!=-1){
            right_vec.push_back(points[right[i]]);
        }
    }
    left.clear();
    right.clear();
}

void Kirkpatrick::init_l_and_r(int size) {
    left.resize(size);
    right.resize(size);
    std::fill(left.begin(),left.end(),unreal_value);
    std::fill(right.begin(),right.end(),unreal_value);
}
