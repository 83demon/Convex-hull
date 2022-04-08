//
// Created by vo1 on 29.11.20.
//

#pragma once
#include "base_class.h"
#include "point.h"
#include <list>
#include <vector>
class Delaunay : public BaseAlgorithm{
public:
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
};
