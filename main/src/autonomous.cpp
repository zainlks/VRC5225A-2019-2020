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
void blue9() {
  angler.move_absolute(1700, 200);
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  fBar.move(-13);
  angler.move_absolute(1700, 200);
  intakeOn();
  move_to_target_sync(0,20,0,false,85,false,true);
  move_to_target_sync(0,23.5,0,false,55,false,true);
  brake();
  delay(50);
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
  delay(50);
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
}

void blueSweep() {
  intakeOn();
  move_to_target_sync(0, 40, 0, false, 45);
  move_to_target_sync(4, 44, deg_to_rad(30), false, 45);
  move_to_target_sync(12, 47, deg_to_rad(110), false, 45);
  move_to_target_sync(17, 51, deg_to_rad(150), false, 45);
  move_to_target_sync(19,45, deg_to_rad(150), false, 45);
  move_to_target_sync(21, 20, deg_to_rad(180), false, 45);
  move_to_target_sync(-10, 9.75, deg_to_rad(-135), false, 127);
  //tracking.waitForDistance(12);

  return;







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
}

void blueLeft(){
  fBar.move_absolute(500, 200);
  while(fBar.get_position() < 495 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  fBar.move(-13);
  intakeOn();

  move_to_target_async(0, 18, 0, false, 60);
  tracking.waitForDistance(12);
  fBar.move_absolute(towerHeights[2], 200);
  tracking.waitForComplete();
  brake();
  delay(100);
  angler.move_absolute(2000,200);
  while(fBar.get_position() < (towerHeights[2] -50)){delay(2);}
  move_to_target_sync(0, 24, 0, true, 60);
  fBar.move_absolute(towerHeights[0], 200);
  while(fBar.get_position() > (towerHeights[0] +50)){delay(2);}
  move_to_target_sync(0,27,false,65);
  fBar.move_absolute(1, 200);
  while(fBar.get_position()>50) delay(1);
  move_to_target_sync(0, 32, 0, true);

}

void autonomous() {
  setDriveState(driveStates::Auto);
  tracking.reset();
  intakeL.move(127);
  delay(80);
  green.sig_num = 1;
  autotimer = pros::millis();
  log("global angle:%f",tracking.global_angle);


  //blue9();
  blueLeft();
  log("autotime is %d\n", autotimer-pros::millis());
  master.clear();
  delay(50);
  master.print(2,0,"%d",millis()-autotimer);

}









//
// move_to_target_sync(0,23.5,0,false,75,false,true);
// brake();
// delay(100);
// move_drive(0,0,0);
// fBar.move_absolute(towerHeights[1]-300, 200);
// move_drive(0, -30, 0);
// angler.move_absolute(400, 200);
// while(fBar.get_position()<towerHeights[1]- 350 || angler.get_position()>1600) delay(1);
// move_to_target_async(0, 25.25, 0, false, 75);
// tracking.waitForDistance(0.75);
// fBar.move_absolute(1, 200);
// tracking.waitForComplete();
// brake();
// delay(100);
// move_drive(0,0,0);
// while(fBar.get_position() > 1000) delay(1);
// move_to_target_async(0, 30.5, 0, false);
// angler.move_absolute(1700, 200);
// tracking.waitForComplete();
// fBar.move(-10);
// move_drive(0, -100, 0); //80
// while(tracking.ycoord>18)delay(1);
// move_to_target_sync(25.5, 2, 0, false,127);
// move_drive(0, 80, 0); //80
// while(tracking.ycoord<9)delay(1);
// move_to_target_async(25.5, 45, 0, false, 70); //60
// tracking.waitForDistance(18);
// move_to_target_sync(25.5, 45, 0, false, 60); //50
// tracking.waitForComplete();
// delay(70);
// move_to_target_async(31.75,9.75, deg_to_rad(135),false,127);
// tracking.waitForDistance(12);
// intakeL.move(-15);
// intakeR.move(15);
// tracking.waitForDistance(7);
// angler.move_absolute(ANGLER_MID-1800, 200);
// tracking.waitForComplete();
// brake()
// delay(75);
// move_drive(0,0,0);
// angler.move_absolute(ANGLER_TOP-1000, 100);
// intakeL.move(15);
// intakeR.move(-15);
// delay(50);
// tracking.LSLineup();
// angler.move_absolute(ANGLER_TOP, 120);
// while((intakeL.get_actual_velocity()>1 || intakeR.get_actual_velocity()>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
// intakeL.move(-10);
// intakeR.move(10);
// while(angler.get_position()<ANGLER_TOP-50) delay(1);
// move_to_target_sync(26,14, deg_to_rad(135));
