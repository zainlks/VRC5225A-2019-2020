#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "controller.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;

enum class screens{
  motor_temps,
  autos
};

enum class sides {red, blue};

const string side_colour[]{"red", "blue"};

enum class autos{
  auto1,
  auto2,
  auto3
};

const string auto_names[] = {
  "9    ",
  "sweep",
  "3    "
};

void menu();
void menu_update();
void autos_page();

// extern screens pages;
// extern sides side;
// extern autos cur_auto;
// extern bool auto_set;
