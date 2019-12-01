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
  "protected    ",
  "unprotected  ",
  "sr5kills       "
};

const string Off_set_arrayS[] = {
  "-1.5",
  "-1",
  "-0.5",
  "0",
  "0.5",
  "1",
  "1.5"
};

const double Off_set_arrayI[] = {
  -1.5,
  -1,
  -0.5,
  0,
  0.5,
  1,
  1.5
};

extern sides side;
extern autos cur_auto;

void menu();
void menu_init();
void menu_update();
void autos_page();
void Offset();

extern double Inches_Off;
// extern screens pages;
// extern sides side;
// extern autos cur_auto;
// extern bool auto_set;
