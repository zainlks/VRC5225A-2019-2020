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
constexpr double FBAR_TOP = 3600;
constexpr double FBAR_MID = 1450;
enum class fBarStates {
  Idle,
  Mid,
  Top
};

void setfBarState(fBarStates state);
void fBarCal();
void fBarHandle();
extern fBarStates fBarState ;
extern fBarStates fBarStateLast;
extern int fBarStateChangeTime;
