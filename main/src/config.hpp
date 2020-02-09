#pragma once
#include "main.h"
#include "angler.hpp"

using namespace pros;

extern ADIEncoder leftencoder;
extern ADIEncoder rightencoder;
extern ADIAnalogIn topLs;
extern ADIAnalogIn bottomLs;
extern ADIEncoder backencoder;
extern Vision vision;
extern Motor intakeR, intakeL;
extern Motor fBar;
extern Motor front_L, front_R, back_L, back_R;
extern Controller master;
