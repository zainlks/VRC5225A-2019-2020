#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "config.hpp"
#include "controller.hpp"
using namespace pros;
uint32_t autotimer;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  tracking.reset();
  autotimer = pros::millis();
  printf("global angle:%f",tracking.global_angle);
  intakeOn();
  angler.move_absolute(2100, 200);
  tracking.move_to_target(0, 22.5, 0, true, 75);
  delay(50);
  fBar.move_absolute(towerHeights[1], 200);
  angler.move_absolute(900, 200);
  while(fBar.get_position()<towerHeights[1]- 350|| angler.get_position()>1600) delay(1);
  move_drive(0,40,0);
  while(tracking.ycoord<24)delay(1);
  move_drive(0, -10, 0);
  delay(100);
  fBar.move_absolute(1, 200);
  while(fBar.get_position() > 1000) delay(1);
  tracking.move_to_target(0, 29.5, 0);
  angler.move_absolute(2500, 200);
  tracking.move_to_target(-24, 2, 0);
  tracking.move_to_target(-24, 39, 0, false, 75);
  printf("time is %d\n", autotimer-pros::millis());
  master.clear();
  delay(50);
  master.print(2,0,"%d",millis()-autotimer);
}
