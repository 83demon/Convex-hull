//
// Created by vo1 on 22.11.20.
//

#include "graham.h"
Point GrahamScan::q = Point(0,0);//to prevent exceptions, that cannot be caught


SceneState GrahamScan::create_hull(std::vector<Point> &points, std::list<SceneState> &frames) {
    SceneState res = SceneState{points};
    calculate_q(points);
    std::sort(points.begin(),points.end(),polar_angles_sort);
    for(int i=0;i<points.size();i++){
        //std::cout<<points[i]<<" / ";
        if(i==0){
            if(angle_is_concave(points.back(),points[i],points[i+1])){
                //std::cout<<points[i]<<" is removed"<<"\n";
                points.erase(points.begin()+i);
                i--;
            }
        }
        else if(i==points.size()-1){
            if(angle_is_concave(points[i-1],points[i],points[0])){
                //std::cout<<points[i]<<" is removed"<<"\n";
                points.erase(points.begin()+i);
                i--;
                i--;
            }
        }
        else{
            if(angle_is_concave(points[i-1],points[i],points[i+1])){
                //std::cout<<points[i]<<" is removed"<<"\n";
                points.erase(points.begin()+i);
                i--;
                i--;
            }
        }
    }
    if(angle_is_concave(points.back(),points[0],points[1])){
        //std::cout<<points[0]<<" is removed"<<"\n";
        points.erase(points.begin());
        create_hull(points,frames);
    }

    std::sort(points.begin(),points.end(),polar_angles_sort);
    for(int i=0;i<points.size();i++){
        res.points[i].color = res.good_color;
        if(i>0){res.create_line(points[i-1],points[i],res.good_color);}
    }
    res.create_line(points.back(),points[0],res.good_color);
    return res;
}

void GrahamScan::calculate_q(std::vector<Point> &points) {
    float x = 0, y = 0;
    for(auto point: points){
        x+=point.get_x();
        y+=point.get_y();
    }
    x = x/points.size();
    y = y/points.size();
    q = Point(x,y);
    //std::cout<<q.get_x()<<" "<<q.get_y()<<"\n";
}

bool GrahamScan::polar_angles_sort(Point &p1, Point &p2) {
    float ang1 = Point::polar_angle(q,p1), ang2 = Point::polar_angle(q,p2);
    bool res = ang1<ang2;
    //std::cout<<p1<<" / "<<ang1<<" ||| "<<p2<<" / "<<ang2<<"\n";
    return res;
}

bool GrahamScan::angle_is_concave(Point &p1, Point &p2, Point &p3) {
    bool res = Point::angle(p1,p2,q)+Point::angle(p3,p2,q)>=180.f;
    if(res){
        //std::cout<<"angle "<<p1<<" "<<p2<<" "<<p3<<" is concave"<<"\n";
    }
    else{
        //std::cout<<"angle "<<p1<<" "<<p2<<" "<<p3<<" is NOT concave"<<"\n";
    }
    return res;
}

