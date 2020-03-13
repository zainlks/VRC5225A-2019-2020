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
    int goodcount = 0;
    long double FOV_HEIGHT = 0;
    double x_middle = 0;
    double y_middle = 0;
    double plane_height = 2.75;
    double camera_height = 7.25 ;
    long double camera_angle = 0;
    long double vertical_angle = 0;
    long double horizontal_angle = 0;
    double last_distance = 0;
    double avg_distance = 0;
    double x = 0;
    double y = 0;
    double avg_middle = 0;
    int16_t last_middle = 0;
    int good_count = 0;
    void update();
};
extern VisionClass green;
void fov_cal();
