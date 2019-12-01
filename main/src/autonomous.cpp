#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "config.hpp"
#include "controller.hpp"
#include "menu.hpp"
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
  intakeL.move(-8);
  intakeR.move(8);
  move_to_target_async(-31.75,9.75, deg_to_rad(-135),false,127);
  tracking.waitForDistance(30);
  intakeL.move(-8);
  intakeR.move(8);
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
  intakeL.move(127);
  intakeR.move(-127);
  while(fBar.get_position() < 495 ){delay(1);}
  delay(50);
  fBar.move_absolute(1,200);
  delay(50);
  master.print(1,0,"%d",millis()-autotimer);
  intakeOn();

  move_to_target_async(0, 15, 0, false, 60,false,true);
  tracking.waitForDistance(3);
  fBar.move_absolute(towerHeights[2], 200);
  angler.move_absolute(2000,200);
  tracking.waitForComplete();
  move_drive(0,17,0);
  while(fBar.get_position() < (towerHeights[2]-50)){delay(2);}

  move_to_target_sync(0, 23.5, 0,false,127);
  fBar.move_absolute(1, 120);
  while(fBar.get_position()>towerHeights[1]) delay(1);
  move_to_target_sync(0,25.5,0, false);
  while(fBar.get_position()>50) delay(1);
  move_to_target_sync(0, 30.5, 0, false);

  //
  // fBar.move_absolute(towerHeights[1]+250, 200);
  // while(fBar.get_position() > (towerHeights[1]+350)){delay(2); printf("stuck\n");}
  // move_drive(0,-17,0);
  // fBar.move_absolute(towerHeights[0]+250, 200);
  // while(fBar.get_position() > (towerHeights[0]+350)){delay(2); printf("stuck\n");}
  // move_to_target_async(0, curPos+1.5, 0,false,127);
  // tracking.waitForDistance(0.5);
  // fBar.move_absolute(1, 150);
  // tracking.waitForComplete();
  // while(fBar.get_position()>75) delay(1);
  // move_to_target_sync(0, tracking.ycoord + 6, 0, false,127);
  move_to_target_sync(8, 48, (M_PI/4),false);
  move_drive(0,-50,0);
  delay(300);
  move_to_target_sync(14, 32, (3*M_PI/4),false);
  move_to_target_async(22, 19, (3*M_PI/4),false);
  tracking.waitForDistance(10);
  angler.move_absolute(ANGLER_TOP-1000, 100);
  tracking.waitForComplete();
  tracking.LSLineup(true, true);
  intakeL.move(25);
  intakeR.move(-25);
  angler.move_absolute(ANGLER_TOP, 80);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_to_target_sync(0, -10.0, 0, false, 127, false, false);
  // move_to_target_sync(0,27,false,65);
  // fBar.move_absolute(1, 200);
  // while(fBar.get_position()>50) delay(1);
  // move_to_target_sync(0, 32, 0, true);

}

void red9() {
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
  move_to_target_sync(24, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(24, 45, 0, false, 70); //60
  tracking.waitForDistance(18);
  move_to_target_sync(24, 45, 0, false, 60); //50
  tracking.waitForComplete();
  delay(70);
  move_to_target_async(31.75,9.75, deg_to_rad(135),false,127);
  tracking.waitForDistance(30);
  intakeL.move(-8);
  intakeR.move(8);
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
  move_to_target_sync(26,14, deg_to_rad(135));
}

void redProtect(){
  fBar.move_absolute(500, 200);
  intakeL.move(127);
  intakeR.move(-127);
  while(fBar.get_position() < 495 ){delay(1);}
  delay(50);
  fBar.move_absolute(1,200);
  delay(50);
  master.print(1,0,"%d",millis()-autotimer);
  intakeOn();

  move_to_target_async(0, 15, 0, false, 60,false,true);
  tracking.waitForDistance(3);
  fBar.move_absolute(towerHeights[2], 200);
  angler.move_absolute(2000,200);
  tracking.waitForComplete();
  move_drive(0,17,0);
  while(fBar.get_position() < (towerHeights[2]-50)){delay(2);}

  move_to_target_sync(0, 23.5, 0,false,127);
  fBar.move_absolute(1, 120);
  while(fBar.get_position()>towerHeights[1]) delay(1);
  move_to_target_sync(0,25.5,0, false);
  while(fBar.get_position()>50) delay(1);
  move_to_target_sync(0, 30.5, 0, false);


  // move_to_target_async(0, 15, 0, false, 60,false,true);
  // tracking.waitForDistance(3);
  // fBar.move_absolute(towerHeights[2]+400, 200);
  // angler.move_absolute(2000,200);
  // tracking.waitForComplete();
  // move_drive(0,20,0);
  // while(fBar.get_position() < (towerHeights[2] +350)){delay(2);}
  // move_to_target_async(0, 10000, 0,false,60);
  // while(orange.obj.height < 10) delay(1);
  // moveStopTask();
  // brake();
  // delay(50);
  // move_to_target_sync(0, tracking.ycoord-5.5, 0,false,127);
  // double curPos = tracking.ycoord;
  // fBar.move_absolute(towerHeights[1]+250, 200);
  // while(fBar.get_position() > (towerHeights[1]+350)){delay(2); printf("stuck\n");}
  // move_drive(0,-9,0);
  // fBar.move_absolute(towerHeights[0]+250, 200);
  // while(fBar.get_position() > (towerHeights[0]+350)){delay(2); printf("stuck\n");}
  // move_to_target_sync(0, curPos+1.5, 0,false,127);
  // fBar.move_absolute(1, 200);
  // while(fBar.get_position()>75) delay(1);
  // move_to_target_sync(0, tracking.ycoord + 6, 0, false,127);

  //move_to_target_sync(-7, 47.5, deg_to_rad(-40), false);
  move_to_target_sync(-8, 40, 0, false);
  move_to_target_sync(-8, 47, 0, false);
  move_drive(0,-50,0);
  delay(300);
  move_to_target_sync(-14, 32, -(3*M_PI/4),false);
  move_to_target_async(-22, 19, -(3*M_PI/4),false);
  tracking.waitForDistance(10);
  angler.move_absolute(ANGLER_TOP-1000, 100);
  tracking.waitForComplete();
  tracking.LSLineup(true, true);
  intakeL.move(25);
  intakeR.move(-25);
  angler.move_absolute(ANGLER_TOP, 80);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_to_target_sync(0, -10.0, 0, false, 127, false, false);
}

void autonomous() {
  setDriveState(driveStates::Auto);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  delay(1);
  while(resetDone == false) delay(1);
  // intakeL.move(127);
  green.sig_num = 1;
  orange.sig_num = 2;
  autotimer = pros::millis();
  log("global angle:%f",tracking.global_angle);
  switch(side) {
    case sides::blue:
      switch(cur_auto) {
        case autos::auto1:
          blueLeft();
        break;
        case autos::auto2:
          blue9();
        break;
        case autos::auto3:
        break;
      }
    break;
    case sides::red:
      switch(cur_auto) {
        case autos::auto1:
          redProtect();
        break;
        case autos::auto2:
          red9();
        break;
        case autos::auto3:
        break;
      }
    break;

  }
  // blue9();
  //blueLeft();
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
