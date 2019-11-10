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
  intakeL.move(127);
  delay(80);
  green.sig_num = 1;
  autotimer = pros::millis();
  printf("global angle:%f",tracking.global_angle);
  angler.move_absolute(1700, 200);
  intakeOn();
  move_to_target_sync(0,23.5,0,false,75,false,true);
  brake();
  delay(100);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[1]-300, 200);
  move_drive(0, -30, 0);
  angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[1]- 350 || angler.get_position()>1600) delay(1);
  move_to_target_async(0, 25.25, 0, false, 75);
  tracking.waitForDistance(0.75);
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  brake();
  delay(100);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_async(0, 30.5, 0, false);
  angler.move_absolute(1700, 200);
  tracking.waitForComplete();
  fBar.move(-10);
  move_drive(0, -100, 0); //80
  while(tracking.ycoord>18)delay(1);
  move_to_target_sync(-25.5, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(-25.5, 45, 0, false, 70); //60
  tracking.waitForDistance(18);
  move_to_target_sync(-25.5, 45, 0, false, 60); //50
  tracking.waitForComplete();
  delay(70);
  move_to_target_async(-31.75,9.75, deg_to_rad(-135),false,127);
  tracking.waitForDistance(12);
  intakeL.move(-15);
  intakeR.move(15);
  tracking.waitForDistance(7);
  angler.move_absolute(ANGLER_MID-1800, 200);
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  angler.move_absolute(ANGLER_TOP-1000, 100);
  intakeL.move(15);
  intakeR.move(-15);
  delay(50);
  tracking.LSLineup();
  angler.move_absolute(ANGLER_TOP, 120);
  while((intakeL.get_actual_velocity()>1 || intakeR.get_actual_velocity()>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  move_to_target_sync(-26,14, deg_to_rad(-135));

  printf("i am done\n");
  printf("time is %d\n", autotimer-pros::millis());
  master.clear();
  delay(50);
  master.print(2,0,"%d",millis()-autotimer);

}
