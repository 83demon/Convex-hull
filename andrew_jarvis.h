//
// Created by vo1 on 23.11.20.
//

#pragma once
#include "point.h"
#include "line.h"
#include "base_class.h"
#include "scene_state.h"
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
class AndrewJarvis : public BaseAlgorithm{
    std::pair<std::vector<Point>, std::vector<Point>> split(std::vector<Point> &points, Point &left, Point &right);
    static bool x_comparison(Point &p1, Point &p2);
public:
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
};
