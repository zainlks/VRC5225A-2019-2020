#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;

enum class driveStates {
  Driver,
  Auto
};
void setDriveState(driveStates state);
void driveHandle(void *param);
extern driveStates driveState;
extern driveStates driveStateLast;
