#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "controller.hpp"
#include "menu.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
extern pros::Task *moveTask;
extern pros::Task *updateTask;
int sgn(double num);
extern bool speedLimit;
extern int offset;
extern int updateCount;
extern bool resetDone;
extern void* labelPointer;
extern void* gotoPointers[10];
double deg_to_rad(double degrees);
double rad_to_deg(double radians);
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
  bool inDrive = false;
};
extern bool trackingReset;
extern moveTargetParams moveParams;
enum direction{
  x,
  y
};

void moveStartTask();
void moveStopTask();
void updateStartTask(bool reset = true);
void updateStopTask();
void move_to_target(void* params);
void move_to_target_sync(double target_x, double target_y, double target_a, bool brakeOn = true, double max_xy = 127, bool cubeLineUp = false,  bool debug = false, bool inDrive = false);
void move_to_target_async(double target_x, double target_y, double target_a, bool brakeOn = true, double max_xy = 127, bool cubeLineUp = false,  bool debug = false, bool inDrive = false);


class Tracking {
public:
  double xcoord = 0, ycoord = 0, global_angle = 0, power_a = 0, power_x = 0, power_y = 0, x2 = 0 , y2 = 0, a2= 0, holdAngle= 0, driveError  = 0, velocityL = 0, velocityR = 0, velocityB = 0, target_x = 0 , target_y = 0, target_a = 0;
  bool toggle_target, toggle_cube, target, cube, moveComplete,safety = false;
  void reset();
  void waitForDistance(double distance);
  void waitForComplete();
  void trackingInput();
  void setAngleHold(double angle);
  void turn_to_target(double target_x, double target_y, bool debug = false, bool brakeOn = true);
  void turn_to_angle(double target_a, bool debug = false, bool brakeOn = true);
  void flattenAgainstWall(bool forward, bool hold = true);
  void LSLineup(bool hold = true, bool intake_deposit = true, int timeoutTime = 5000, int speed = 65);
  void LSLineupSkills(bool hold = true, bool intake_deposit = true, int timeoutTime = 5000, int speed = 65);
  void straightLift(double height);
  void static move_xy(double distance, direction direct, bool brakeon = true, bool debug = false);
};

extern Tracking tracking;

double operator "" _deg(long double degree);
double operator "" _rad(long double radians);
