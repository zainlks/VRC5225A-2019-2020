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
void intakeTask(void *param) {
  while(true) {
      if(tracking.xcoord<-28 && tracking.ycoord<20) {
        intakeL.move(-10);
        intakeR.move(10);
        break;
      }
  }

}
void autonomous() {
  setDriveState(driveStates::Auto);
  tracking.reset();
  autotimer = pros::millis();
  printf("global angle:%f",tracking.global_angle);
  intakeOn();
  angler.move_absolute(1700, 200);
  move_to_target_sync(0,22.5,0,false,75);
  brake();
  delay(100);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[1]-300, 200);
  move_drive(0, -30, 0);
  angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[1]- 350 || angler.get_position()>1600) delay(1);
  move_to_target_sync(0, 24.5, 0, false, 60);
  brake();
  delay(100);
  move_drive(0,0,0);
  fBar.move_absolute(1, 200);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_sync(0, 29, 0, false);
  angler.move_absolute(1700, 200);
  move_to_target_sync(-25.5, 2, 0, false);
  move_drive(0, 95, 0);
  while(tracking.ycoord<19)delay(1);
  move_to_target_sync(-25.5, 48, 0, false, 60);
  intakeL.move(-10);
  intakeR.move(10);
  move_to_target_sync(-33,9, deg_to_rad(-135),false,127,false,true);
  angler.move_absolute(ANGLER_TOP-500, 200);
  tracking.flattenAgainstWall(true,true);
  tracking.reset();
  intakeL.move(30);
  intakeR.move(-30);
  angler.move_absolute(ANGLER_TOP, 100);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  move_to_target_sync(0, -10, 0);
  printf("i am done\n");
  printf("time is %d\n", autotimer-pros::millis());
  master.clear();
  delay(50);
  master.print(2,0,"%d",millis()-autotimer);

}
