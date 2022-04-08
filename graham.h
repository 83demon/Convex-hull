//
// Created by vo1 on 22.11.20.
//

#pragma once
#include "point.h"
#include "triangle.h"
#include "convex_hull.h"
#include "base_class.h"
#include "scene_state.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
class GrahamScan : public BaseAlgorithm{
    static Point q;
    static bool angle_is_concave(Point &p1, Point &p2, Point &p3);
public:
    static void calculate_q(std::vector<Point> &points);
    static bool polar_angles_sort(Point &p1, Point &p2);
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
};