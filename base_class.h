//
// Created by vo1 on 29.11.20.
//

#pragma once
#include "point.h"
#include "scene_state.h"
#include <list>
#include <vector>
class BaseAlgorithm{
public:
    virtual SceneState create_hull(std::vector<Point> &points, std::list<SceneState> &frames){
        return SceneState();};
};
