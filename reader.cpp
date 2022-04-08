//
// Created by vo1 on 19.11.20.
//

#include "reader.h"

std::vector<Point> Reader::read(const char* filename) {

    //also scales to fit the window(commented)
    std::vector<Point> res;
    std::ifstream file(filename);
    if(file.is_open()){
        std::cout<<"OPENED";
    }
    else{
        std::cout<<"CLOSED";
    }
    //std::string input;
//    float max_x = -INFINITY, max_y = -INFINITY, min_x = INFINITY, min_y = INFINITY;
//    std::vector<float> x_s,y_s;
//    std::vector<std::pair<float, float>> x_y;
    float a, b;
    while (file >> a >> b)
    {
        res.emplace_back(Point(a,b));
    }
    file.close();
//        x_y.emplace_back(std::make_pair(a,b));
//        x_s.push_back(a);
//        y_s.push_back(b);
//    }
//    for(auto i:x_s){
//        if(i>max_x){max_x=i;}
//        if(i<min_x){min_x=i;}
//    }
//    for(auto i:y_s){
//        if(i>max_y){max_y=i;}
//        if(i<min_y){min_y=i;}
//    }
//    for(auto &pair:x_y){
//        pair.first = (pair.first+abs(min_x))/max_x*window_width;
//        pair.second = (pair.second+abs(min_y))/max_y*window_height;
//    }
//    res.reserve(x_y.size());
//    for(auto pair:x_y){
//        res.emplace_back(Point(pair.first,pair.second));
//    }
    return res;
}

