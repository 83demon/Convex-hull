//
// Created by vo1 on 23.11.20.
//

#pragma once
#include "point.h"
#include "line.h"
#include <vector>
#include <utility>
class PointsSet : public Point {
    std::vector<Point> set;
public:
    static std::pair<PointsSet, PointsSet> split(PointsSet &points, Line &line);
};