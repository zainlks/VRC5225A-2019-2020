#include "main.h"
#include "config.hpp"
#include "angler_move.hpp"
using namespace pros;
#include <iostream>
#include <cmath>

void opcontrol() {
  angler_move(5200, 80);
}
