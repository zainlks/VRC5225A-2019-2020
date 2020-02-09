#pragma once
#include "main.h"
#include "config.hpp"

#include "fBar.hpp"
#include "tracking.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
using namespace std;
using namespace pros;

extern bool gui_running;

void gui_init();
void gui_handle();
lv_res_t liftTestButtonClicked(lv_obj_t* button);
lv_res_t resetClicked(lv_obj_t* button);
lv_res_t MotorClicked(lv_obj_t* button);
