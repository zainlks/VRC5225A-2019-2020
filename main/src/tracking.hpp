#pragma once
#include "main.h"
#include "config.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;

void move_drive(int x, int y, int a);
void brake();
void update(void *param);

class Tracking {
public:
  double xcoord, ycoord, global_angle, power_a, power_x, power_y, x2 , y2 , a2  = 0;
  bool toggle_target, toggle_cube, target, cube = false;
  void move_to_target(double target_x, double target_y, double target_a, bool debug = false);
};

extern Tracking tracking;
