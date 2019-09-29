#pragma once
#include "main.h"
#include "config.hpp"
#include <iostream>
#include <cmath>
using namespace pros;

typedef enum _IntakeState {
	intakeIn,
	intakeOut,
	intakeStopped,
	intakeJammed
} IntakeState;

void intk_ctrl(void* param);
void intake(int speed);

extern 	IntakeState intk_state, state;
extern  unsigned long jammed_time;
