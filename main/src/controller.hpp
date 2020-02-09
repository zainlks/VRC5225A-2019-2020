#pragma once
#include "main.h"
#include "config.hpp"

#include "fBar.hpp"
#include "drive.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;

#define INTK_IN_BUTTON E_CONTROLLER_DIGITAL_X
#define INTK_OUT_BUTTON E_CONTROLLER_DIGITAL_A
#define TOWER_HEIGHT E_CONTROLLER_DIGITAL_L2
#define ANGLER_DOWN E_CONTROLLER_DIGITAL_DOWN
#define DROPOFF_BUTTON E_CONTROLLER_DIGITAL_L1
#define FBAR_DOWN E_CONTROLLER_DIGITAL_B
#define UP_CUBE_HEIGHT E_CONTROLLER_DIGITAL_R1
#define DOWN_CUBE_HEIGHT E_CONTROLLER_DIGITAL_R2
#define SPEED_LIMIT E_CONTROLLER_DIGITAL_Y
#define JOY_FORWARD E_CONTROLLER_ANALOG_LEFT_Y
#define JOY_TURN E_CONTROLLER_ANALOG_LEFT_X
#define JOY_STRAFE E_CONTROLLER_ANALOG_RIGHT_X
extern bool doublePressCheck;

void printTemp(void *param);
