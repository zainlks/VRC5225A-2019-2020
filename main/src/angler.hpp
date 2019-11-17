#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "drive.hpp"
#include "controller.hpp"
#include "logging.hpp"
#include "tracking.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
constexpr double ANGLER_TOP = 7500;
constexpr double ANGLER_MID = 5200;
enum class anglerStates {
  Idle,
  Mid,
  Push,
  CubeOutLast,
  CubeOutFirst,
  Top
};
void intakeOn();
void startDropOff();
void stopDropOff();
void dropOff(void *param);
void setAnglerState(anglerStates state);
void anglerCal();
void anglerHandle();
extern anglerStates anglerState ;
extern anglerStates anglerStateLast;
extern int anglerStateChangeTime;
