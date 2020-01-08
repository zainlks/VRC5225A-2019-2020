#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "fBar.hpp"
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
lv_res_t liftTestButtonClicked(lv_obj_t* button);
