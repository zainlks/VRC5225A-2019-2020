#pragma once 

#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "config.hpp"
#include "controller.hpp"
#include "menu.hpp"
using namespace pros;

void intakeTask();

void blue10();
void blue9();
void blueProtect();
void red10();
void red9();
void redProtect();
void skills();
void newSkills();

extern uint32_t autotimer;
