//
// Created by vo1 on 21.11.20.
//

#pragma once
#include "point.h"
#include "triangle.h"
#include "line.h"
#include "base_class.h"
#include "graham.h"
#include "scene_state.h"
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
class ConvexHull : public BaseAlgorithm{
    static Point q;
    static int count_value(std::vector<std::pair<Point, float>> &vector, float &value);
    static bool area_comparison(std::pair<Point, float> &p1, std::pair<Point, float> &p2);
    static void sort_points_by_x(std::vector<Point> &points);
    static void sort_pairs_by_second_arg(std::vector<std::pair<Point, float>> &vector);
    static std::pair<std::vector<Point>,std::vector<Point>> split(std::vector<Point> &points, Point &left, Point &right);
    static bool x_comparison(Point &p1, Point &p2);
public:
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
    std::vector<Point> create_convex_hull(std::vector<Point> &points, std::list<SceneState> &frames,
                                          int depth=0, bool half=true);
};