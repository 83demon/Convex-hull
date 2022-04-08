//
// Created by vo1 on 19.11.20.
//

#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "point.h"
class Reader{
public:
    static std::vector<Point> read(const char* path);
};