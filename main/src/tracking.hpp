#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "controller.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
extern pros::Task *moveTask;
int sgn(double num);
extern bool speedLimit;
extern int offset;
double deg_to_rad(double degrees);
void move_drive(int x, int y, int a);
void move_drive_side(int L, int R);
void brake();
void update(void *param);
void pointToAngle(void *param);
struct moveTargetParams {
  double target_x;
  double target_y;
  double target_a;
  bool brakeOn = true;
  double max_xy = 127;
  bool cubeLineUp = false;
  bool debug = false;
};
extern moveTargetParams moveParams;

void moveStartTask();
void moveStopTask();
void move_to_target(void* params);
void move_to_target_sync(double target_x, double target_y, double target_a, bool brakeOn = true, double max_xy = 127, bool cubeLineUp = false,  bool debug = false);
void move_to_target_async(double target_x, double target_y, double target_a, bool brakeOn = true, double max_xy = 127, bool cubeLineUp = false,  bool debug = false);

class Tracking {
public:
  double xcoord, ycoord, global_angle, power_a, power_x, power_y, x2 , y2 , a2, holdAngle, driveError  = 0;
  bool toggle_target, toggle_cube, target, cube, moveComplete = false;
  void reset();
  void waitForDistance(double distance);
  void waitForComplete();
  void trackingInput();
  void setAngleHold(double angle);
  void turn_to_target(double target_x, double target_y, bool debug = false);
  void turn_to_angle(double target_a, bool debug = false);
  void flattenAgainstWall(bool forward, bool hold = true);
  void LSLineup(bool hold = true);
};

extern Tracking tracking;
