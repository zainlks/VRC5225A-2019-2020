#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
constexpr double ANGLER_TOP = 2600;
constexpr double ANGLER_MID = 1350;
enum class anglerStates {
  Idle,
  Mid,
  CubeOut,
  Top
};

void setAnglerState(anglerStates state);
void anglerCal();
void anglerHandle();
extern anglerStates anglerState ;
extern anglerStates anglerStateLast;
extern int anglerStateChangeTime;
