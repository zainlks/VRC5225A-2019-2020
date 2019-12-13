#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "angler.hpp"
#include "controller.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
const int towerHeights[3] = {1100,1850,2900};
constexpr double FBAR_TOP = 3450;
constexpr double FBAR_MID = 2600;
enum class fBarStates {
  Idle,
  Mid,
  Tower,
  Top
};

void setfBarState(fBarStates state);
void fBarCal();
void fBarHandle();
extern fBarStates fBarState ;
extern fBarStates fBarStateLast;
extern int fBarStateChangeTime;
