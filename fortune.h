//
// Created by vo1 on 25.11.20.
//

#pragma once
#include "base_class.h"
#include "point.h"
#include "scene_state.h"
#include <list>
#include <vector>
class Fortune : public BaseAlgorithm{
public:
    SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames) override;
};