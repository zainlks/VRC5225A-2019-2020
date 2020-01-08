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

extern pros::Mutex mutex;
struct graphingEntries {
  int entry1;
  double entry2;
  double entry3;
  double entry4;
  double entry5;
  double entry6;
};
extern graphingEntries graphParams;

extern bool log_done;
void log_init();
void log(const char * format, ...);
void log_graph(int en1, double entry2 = 0, double entry3 = 0, double entry4 = 0, double entry5 = 0, double entry6 = 0);

void log_task(void* params);
void logStartTask();
void logStopTask();
