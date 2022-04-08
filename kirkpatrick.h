//
// Created by vo1 on 24.11.20.
//

#pragma once
#include "point.h"
#include "triangle.h"
#include "base_class.h"
#include "scene_state.h"
#include <list>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
class Kirkpatrick : public BaseAlgorithm{
public:
    int unreal_value = -1; // for bucket sort
    int n_buckets = 1000;
    std::vector<int> left, right;
    std::vector<Point> left_vec, right_vec;
    void init_l_and_r(int size);
    void bucket_sort(std::vector<Point> &points);
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
};

