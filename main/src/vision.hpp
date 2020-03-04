#pragma once
#include "main.h"
#include "config.hpp"

#include "controller.hpp"
#include "menu.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;

extern pros::vision_object_s_t obj;
class VisionClass {
  public:
    double angle = 0;
    double distance = 0;
    double last_distance = 0;
    double avg_distance = 0;
    double avg_middle = 0;
    int16_t last_middle = 0;
    int good_count =  0;
    int distance_good_count = 0;
    void update();
};
extern VisionClass green;
