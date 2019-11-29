#pragma once
#include "main.h"
#include "tracking.hpp"
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

class visionClass {
public:
  double x, y, distance, average_distance, average_height, total_average = 0;
  int cur_height, last_height, sig_num, good_count, line_dif = 0;
  bool linedUp = true;
  pros::vision_object_s_t obj = vision.get_by_sig(0, this->sig_num);
  void update ();
  void reset();
  vector<double> position();
  void lineMiddle(float kP, double yHold, double angle = 0);
};
extern visionClass green;
extern visionClass purple;
extern visionClass orange;
extern int avg_height;
