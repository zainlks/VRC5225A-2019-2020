#pragma once
#include "main.h"
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
extern pros::Vision vision;
extern pros::Motor drive_fl;
extern pros::Motor drive_fr;
extern pros::Motor drive_bl;
extern pros::Motor drive_br;
class Vision {
public:
  double x, y, distance, average_distance, average_height, total_average = 0;
  int cur_height, last_height, sig_num, good_count = 0;
  pros::vision_object_s_t obj = vision.get_by_sig(0, this->sig_num);
  void update();
  void reset();
  vector<double> position();
};
extern Vision green;
extern Vision purple;
extern int avg_height;
