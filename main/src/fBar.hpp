#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "angler.hpp"
#include "controller.hpp"
#include "gui.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
const int towerHeights[3] = {1850,2830,3160};
constexpr double FBAR_TOP = 4105;
constexpr double FBAR_MID = 3000;
enum class fBarStates {
  Idle,
  Mid,
  InZone,
  Tower,
  Top
};

void setfBarState(fBarStates state);
void fBarCal();
void fBarHandle();
extern fBarStates fBarState ;
extern fBarStates fBarStateLast;
extern int fBarStateChangeTime;
