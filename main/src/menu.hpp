#pragma once
#include "main.h"
#include "config.hpp"

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

enum autos{
  auto1,
  auto2,
  auto3,
  auto4,
  num_of_ele
};

const string auto_names[] = {
  "protected    ",
  "unprotected  ",
  "four first   ",
  "skills       "
};

extern sides side;
extern autos cur_auto;


void menu();
void menu_init();
void menu_update();
void autos_page();
void auto_increase();
void auto_decrease();

// extern screens pages;
// extern sides side;
// extern autos cur_auto;
// extern bool auto_set;
