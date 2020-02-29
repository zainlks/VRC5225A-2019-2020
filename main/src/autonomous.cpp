#include "main.h"
#include "tracking.hpp"

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

void blueFourFirst() {
  //angler.move_absolute(1700, 200);
  // gotoPointers[0] = &&dropOff;x
  uint32_t nineCubeTime = 0;
  bool nineCubeSafety = false;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  int lsFilter = 0;

  //angler.move_absolute(1700, 200);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  //angler.move_absolute(1700, 200);
  move_to_target_async(0,20,0,false,90);
  tracking.waitForDistance(17);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(0,23.5,0,false,80);
  brake();
  delay(50);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[0]+ 50, 200);

  move_to_target_sync(0,18.5,0,false,127);
  //angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[0]) delay(1);
  brake();

  move_to_target_async(0, 22, 0, false, 127);
  tracking.waitForDistance(1);
  //delay(100);
  // return;
  // tracking.waitForDistance(0.75);
  fBar.move(-127);
  tracking.waitForComplete();
  // tracking.waitForComplete();
  brake();
  delay(50);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_async(0, 30.5, 0, false);
  while(fBar.get_position() > 300) delay(1);
  fBar.move(-13);
  delay(100);
  // delay(100);
  move_to_target_async(-7.5, 45.5, -M_PI/4,false);
  tracking.waitForDistance(4);
  angler.move_absolute(3200,200);
  while(angler.get_position()<3000)delay(1);
  tracking.waitForComplete();
  move_to_target_async(-9.5,50.5,-3*M_PI/4,false);
  tracking.waitForDistance(2.5);
  angler.move_absolute(1,200);
  tracking.waitForComplete();
  while(angler.get_position()<300)delay(1);
  delay(50);
  move_to_target_sync(-13.5,43.5,-3*M_PI/4,false);
  move_to_target_sync(-22.5,41,-180.0_deg,false);
  move_to_target_sync(-22.5,37,-180.0_deg,false);
  move_to_target_async(-22.5,12,-M_PI,false);
  tracking.waitForComplete();
  intakeR.move(30);
  intakeL.move(-30);
  // return;xx
  move_to_target_async(-28.5,15.5, deg_to_rad(-135),false,127);
  uint32_t LSTimer = millis();
  angler.move_absolute(ANGLER_MID, 120);
  fBar.move_absolute(650,100);
  while((topLs.get_value() > 500 || bottomLs.get_value() > 2500) && millis()-LSTimer<800) delay(1);
  intakeR.move(20);
  intakeL.move(-20);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 140);
  intakeL.move(35);
  intakeR.move(-35);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-1150) delay(1);
  angler.move(127);
                  // while(angler.get_position()<ANGLER_TOP-800) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 85);
                  // while(angler.get_position()<ANGLER_TOP-300) delay(1);
                  // angler.move_absolute(ANGLER_TOP,160);
                  // while(angler.get_position()<ANGLER_TOP-50) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 100);
                  // while(angler.get_position()<ANGLER_TOP-10) delay(1);
                  // delay(100);
                  // fBar.move_absolute(600,200);
                  // while(fBar.get_position()<300)delay(1);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  angler.move(0);
  fBar.move_absolute(750,200);
  while(fBar.get_position()<700)delay(1);
  // fBar.move_absolute(600,200);
  // while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_drive(0,-75,0);
  while(fabs(tracking.ycoord)<10) delay (1);
  move_drive(0,0,0);
  end:
  delay(1);
}

void blue9() {
  gotoPointers[0] = &&dropOff;
  uint32_t nineCubeTime = 0;
  bool nineCubeSafety = false;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  int lsFilter = 0;

  //angler.move_absolute(1700, 200);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  //angler.move_absolute(1700, 200);
  move_to_target_async(0,20,0,false,90);
  tracking.waitForDistance(17);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(0,24,0,false,80);
  brake();
  delay(50);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[0]+ 50, 200);

  move_to_target_sync(0,18.5,0,false,127);
  //angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[0]) delay(1);
  brake();

  move_to_target_async(0, 22, 0, false, 127);
  tracking.waitForDistance(1);
  //delay(100);
  // return;
  // tracking.waitForDistance(0.75);
  printf("grfajhsgdkasgdklashdjkdshfkasdhjsd\n");
  fBar.move(-127);
  tracking.waitForComplete();
  // tracking.waitForComplete();
  brake();
  delay(50);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_async(0, 31, 0, false);
  while(fBar.get_position() > 300) delay(1);
  fBar.move(-13);
  tracking.waitForComplete();
  // delay(100);
  //move_to_target_sync(-4, 30.5, 0,false);
  // return;
  move_to_target_async(0, -10, 0, false, 127);
  tracking.waitForDistance(23);
  move_to_target_sync(-24, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(-24, 40, 0, false, 100); //60
  tracking.waitForDistance(15);
  move_to_target_async(-24, 42.5, 0, false, 70);
  tracking.waitForDistance(0.5);
  if(tracking.safety) goto dropOff;
  dropOff:
  move_to_target_async(-30,11.5, deg_to_rad(-135),false,127);
  uint32_t LSTimer = millis();
  angler.move_absolute(ANGLER_MID, 130);
  fBar.move_absolute(650,200);
  while((topLs.get_value() > 500 || bottomLs.get_value() > 2500) && millis()-LSTimer<800) delay(1);
  delay(70);
  intakeR.move(20);
  intakeL.move(-20);
  intakeR.move(-6);
  intakeL.move(6);
  while(bottomLs.get_value()>2500 && !tracking.moveComplete) delay(1);
  intakeR.move(20);
  intakeL.move(-20);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  tracking.LSLineup(true, true, 1500);
  // double curY = tracking.ycoord;
  // move_drive(0,-35,0);
  // while(tracking.ycoord-curY < 0.75) delay(1);
  // move_drive(0,0,0);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(45);
  intakeR.move(-45);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-1150) delay(1);
  angler.move(110);
                  // while(angler.get_position()<ANGLER_TOP-800) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 85);
                  // while(angler.get_position()<ANGLER_TOP-300) delay(1);
                  // angler.move_absolute(ANGLER_TOP,160);
                  // while(angler.get_position()<ANGLER_TOP-50) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 100);
                  // while(angler.get_position()<ANGLER_TOP-10) delay(1);
                  // delay(100);
                  // fBar.move_absolute(600,200);
                  // while(fBar.get_position()<300)delay(1);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  angler.move(0);
  delay(300);
  fBar.move_absolute(600,200);
  while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_drive(0,-75,0);
  while(fabs(tracking.ycoord)<10) delay (1);
  move_drive(0,0,0);
  end:
  delay(1);
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
  gotoPointers[0] = &&dropOff;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);

  intakeL.move(-15);
  intakeR.move(15);
  fBar.move_absolute(1,200);
  //delay(50);
  while(fBar.get_position()> 50) {delay(1);}
  fBar.move(-25);
  delay(250);
  master.print(1,0,"%d",millis()-autotimer);
  move_to_target_async(0, 16, 0, false, 50);
  intakeOn();
  tracking.waitForDistance(12);

  fBar.move_absolute(towerHeights[2] + 400, 200);
  while(fBar.get_position()<towerHeights[2] +100) delay(1);
  fBar.move_absolute(towerHeights[2] + 400, 100);
  while(fBar.get_position()<towerHeights[2] + 200)delay(1);
  delay(50);
  tracking.waitForComplete();
  move_to_target_sync(0, 24,0, false, 60);
  fBar.move_absolute(towerHeights[1]- 700, 100);
  move_to_target_async(0, 20,0, false);
  while(fBar.get_position()>towerHeights[1]-550)delay(1);
  fBar.move_absolute(towerHeights[0]- 500, 100);
  move_to_target_async(0, 22,0,false);
  while(fBar.get_position()>towerHeights[0]-350)delay(1);
  delay(50);
  fBar.move_absolute(1, 200);
  while(fBar.get_position()> 1000)delay(1);
  move_to_target_sync(4, 46, (M_PI/4),false);
  move_drive(0,-65,0);
  delay(300);
  move_to_target_sync(13, 28, 135.0_deg,false, 127);
  dropOff:
  move_to_target_async(23.5, 17, (3*M_PI/4),false, 127);
  tracking.waitForDistance(6);
  angler.move_absolute(3500, 200);
  fBar.move_absolute(650,100);
  outtakeTime = millis();
  while (true){
    if ((millis() - outtakeTime) > 500)
    {
      intakeR.move(-5);
      intakeL.move(5);
      outtakeState = true;
      printf ("%d| outtakes", millis());
    }
    if (outtakeState && bottomLs.get_value() < 1000){
      intakeR.move(15);
      intakeL.move(-15);
      printf ("%d| light sensor covered", millis());
    }
    if (tracking.moveComplete) break;
    delay(2);
  }
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  while(angler.get_position() < 3100)delay(1);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 160);
  intakeL.move(27);
  intakeR.move(-27);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-800) delay(1);
  angler.move_absolute(ANGLER_TOP, 80);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  angler.move_absolute(ANGLER_TOP, 100);
  delay(50);

  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_drive(0,-75,0);
  while(fabs(tracking.ycoord)<10) delay (1);
  move_drive(0,0,0);
  end:
  delay(1);
}

void redFourFirst() {
  uint32_t nineCubeTime = 0;
  bool nineCubeSafety = false;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  int lsFilter = 0;

  //angler.move_absolute(1700, 200);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  //angler.move_absolute(1700, 200);
  move_to_target_async(0,20,0,false,90,false,true);
  tracking.waitForDistance(17);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(0,23.5,0,false,80,false,true);
  brake();
  delay(50);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[0]+ 50, 200);

  move_to_target_sync(0,18.5,0,false,127);
  //angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[0]-50) delay(1);
  brake();

  move_to_target_async(0, 22, 0, false, 127);
  tracking.waitForDistance(1);
  //delay(100);
  // return;
  // tracking.waitForDistance(0.75);
  fBar.move(-127);
  tracking.waitForComplete();
  // tracking.waitForComplete();
  brake();
  delay(50);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_async(0, 30.5, 0, false);
  while(fBar.get_position() > 300) delay(1);
  fBar.move(-13);
  delay(100);
  // delay(100);
  move_to_target_async(7.5, 45.5, M_PI/4,false);
  tracking.waitForDistance(4);
  angler.move_absolute(3200,200);
  while(angler.get_position()<3000)delay(1);
  tracking.waitForComplete();
  move_to_target_async(9,50,3*M_PI/4,false);
  tracking.waitForDistance(2.5);
  angler.move_absolute(1,200);
  tracking.waitForComplete();
  while(angler.get_position()<300)delay(1);
  delay(50);
  move_to_target_sync(13.5,43.5,3*M_PI/4,false);
  move_to_target_sync(22.5,37,M_PI,false);
  move_to_target_async(22.5,12,M_PI,false);
  while((topLs.get_value() > 500 || bottomLs.get_value() > 2500) && !tracking.moveComplete) delay(1);
  intakeR.move(20);
  intakeL.move(-20);
  tracking.waitForComplete();
  // return;xx
  move_to_target_async(26,14, deg_to_rad(135),false,127);
  uint32_t LSTimer = millis();
  angler.move_absolute(ANGLER_MID, 120);
  fBar.move_absolute(650,100);
  while((topLs.get_value() > 500 || bottomLs.get_value() > 2500) && millis()-LSTimer<800) delay(1);
  intakeR.move(20);
  intakeL.move(-20);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
    tracking.LSLineup(true, true, 1500);
    angler.move_absolute(ANGLER_TOP, 160);
    intakeL.move(35);
    intakeR.move(-35);
    delay(50);
    while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
    fBar.move(5);
    while(angler.get_position()<ANGLER_TOP-800) delay(1);
    angler.move_absolute(ANGLER_TOP, 85);
    while(angler.get_position()<ANGLER_TOP-300) delay(1);
    angler.move_absolute(ANGLER_TOP,160);
    while(angler.get_position()<ANGLER_TOP-50) delay(1);
    angler.move_absolute(ANGLER_TOP, 145);
    while(angler.get_position()<ANGLER_TOP-10) delay(1);
    delay(200);
    // fBar.move_absolute(600,200);
    // while(fBar.get_position()<300)delay(1);
    updateStopTask();
    tracking.reset();
    updateStartTask();
    move_drive(0,-75,0);
    while(fabs(tracking.ycoord)<10) delay (1);
    move_drive(0,0,0);
    end:
    delay(1);
}

void red9() {
  gotoPointers[0] = &&dropOff;
  uint32_t nineCubeTime = 0;
  bool nineCubeSafety = false;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  int lsFilter = 0;

  //angler.move_absolute(1700, 200);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  //angler.move_absolute(1700, 200);
  move_to_target_async(0,20,0,false,90);
  tracking.waitForDistance(17);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(0,23.5,0,false,80);
  brake();
  delay(50);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[0]+ 50, 200);

  move_drive(0, -40, 0);
  //angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[0]) delay(1);
  brake();

  move_to_target_async(0, 22, 0, false, 75);
  tracking.waitForDistance(0.5);
  //delay(100);
  // return;
  // tracking.waitForDistance(0.75);
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  // tracking.waitForComplete();
  brake();
  delay(50);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_sync(0, 32, 0, false);
  delay(100);
  // delay(100);
  //move_to_target_sync(-4, 30.5, 0,false);
  // return;
  move_to_target_async(0, -10, 0, false, 127);
  tracking.waitForDistance(23);
  move_to_target_sync(24, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(24, 42, 0, false, 100); //60
  tracking.waitForDistance(15);
  move_to_target_async(24, 42, 0, false, 70); //50
  tracking.waitForDistance(0.75);
  // while(topLs.get_value() > 500 && bottomLs.get_value() > 2500) delay(1);
  if(tracking.safety) goto dropOff;
  dropOff:
  move_to_target_async(30,11.5, deg_to_rad(135),false,127);
  uint32_t LSTimer = millis();
  angler.move_absolute(ANGLER_MID, 130);
  fBar.move_absolute(650,200);
  while((topLs.get_value() > 500 || bottomLs.get_value() > 2500) && millis()-LSTimer<800) delay(1);
  delay(100);
  intakeR.move(20);
  intakeL.move(-20);
  intakeR.move(-6);
  intakeL.move(6);
  while(bottomLs.get_value()>2500 && !tracking.moveComplete) delay(1);
  intakeR.move(20);
  intakeL.move(-20);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(45);
  intakeR.move(-45);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-1150) delay(1);
  angler.move(110);
                  // while(angler.get_position()<ANGLER_TOP-800) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 85);
                  // while(angler.get_position()<ANGLER_TOP-300) delay(1);
                  // angler.move_absolute(ANGLER_TOP,160);
                  // while(angler.get_position()<ANGLER_TOP-50) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 100);
                  // while(angler.get_position()<ANGLER_TOP-10) delay(1);
                  // delay(100);
                  // fBar.move_absolute(600,200);
                  // while(fBar.get_position()<300)delay(1);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  angler.move(0);
  delay(300);
  fBar.move_absolute(600,200);
  while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_drive(0,-75,0);
  while(fabs(tracking.ycoord)<10) delay (1);
  move_drive(0,0,0);
  end:
  delay(1);
}

void redProtect(){

  gotoPointers[0] = &&dropOff;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);

  intakeL.move(-15);
  intakeR.move(15);
  fBar.move_absolute(1,200);
  //delay(50);
  while(fBar.get_position()> 50) {delay(1);}
  fBar.move(-25);
  delay(250);
  master.print(1,0,"%d",millis()-autotimer);
  move_to_target_async(0, 16, 0, false, 50);
  intakeOn();
  tracking.waitForDistance(12);

  fBar.move_absolute(towerHeights[2] + 400, 200);
  while(fBar.get_position()<towerHeights[2] +100) delay(1);
  fBar.move_absolute(towerHeights[2] + 400, 100);
  while(fBar.get_position()<towerHeights[2] + 200)delay(1);
  delay(50);
  tracking.waitForComplete();
  move_to_target_sync(0, 24,0, false, 60);
  fBar.move_absolute(towerHeights[1]- 700, 100);
  move_to_target_async(0, 20,0, false);
  while(fBar.get_position()>towerHeights[1]-550)delay(1);
  fBar.move_absolute(towerHeights[0]- 500, 100);
  move_to_target_async(0, 22,0,false);
  while(fBar.get_position()>towerHeights[0]-350)delay(1);
  delay(50);
  fBar.move_absolute(1, 200);
  while(fBar.get_position()> 1000)delay(1);
  move_to_target_sync(-4, 46, -45.0_deg,false);
  move_drive(0,-65,0);
  delay(300);
  move_to_target_sync(-13, 28, -135.0_deg,false, 127);
  dropOff:
  move_to_target_async(-23.5, 17, (-3*M_PI/4),false, 127);
  tracking.waitForDistance(6);
  angler.move_absolute(3500, 200);
  fBar.move_absolute(650,100);
  outtakeTime = millis();
  while (true){
    if ((millis() - outtakeTime) > 500)
    {
      intakeR.move(-5);
      intakeL.move(5);
      outtakeState = true;
      printf ("%d| outtakes", millis());
    }
    if (outtakeState && bottomLs.get_value() < 1000){
      intakeR.move(15);
      intakeL.move(-15);
      printf ("%d| light sensor covered", millis());
    }
    if (tracking.moveComplete) break;
    delay(2);
  }
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  while(angler.get_position() < 3100)delay(1);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 160);
  intakeL.move(27);
  intakeR.move(-27);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-800) delay(1);
  angler.move_absolute(ANGLER_TOP, 80);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  angler.move_absolute(ANGLER_TOP, 100);
  delay(50);

  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_drive(0,-75,0);
  while(fabs(tracking.ycoord)<10) delay (1);
  move_drive(0,0,0);
  end:
  delay(1);
}

void skills() {
  uint32_t nineCubeTime = 0;
  bool nineCubeSafety = false;
  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  //angler.move_absolute(1700, 200);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  //angler.move_absolute(1700, 200);
  move_to_target_async(0,20,0,false,90,false,true);
  tracking.waitForDistance(17);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(0,23.5,0,false,80,false,true);
  brake();
  delay(50);
  move_drive(0,0,0);
  fBar.move_absolute(towerHeights[0]+ 50, 200);

  move_drive(0, -40, 0);
  //angler.move_absolute(400, 200);
  while(fBar.get_position()<towerHeights[0]-10) delay(1);
  brake();

  move_to_target_sync(0, 22, 0, false, 75);
  //delay(100);
  // return;
  // tracking.waitForDistance(0.75);
  fBar.move_absolute(1, 200);
  // tracking.waitForComplete();
  brake();
  delay(50);
  move_drive(0,0,0);
  while(fBar.get_position() > 1000) delay(1);
  move_to_target_sync(0, 30.5, 0, false);
  delay(100);
  // delay(100);
  //move_to_target_sync(-4, 30.5, 0,false);
  // return;
  move_to_target_async(0, -10, 0, false, 127);
  tracking.waitForDistance(23);
  move_to_target_sync(-24, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(-24, 40, 0, false, 90); //60
  tracking.waitForDistance(15);
  move_to_target_sync(-24, 40, 0, false, 80); //50
  tracking.waitForComplete();
  delay(70);
  move_to_target_async(-30,11.5, deg_to_rad(-135),false,127);
  delay(50);
  while(true){
    if(!nineCubeSafety && topLs.get_value() < 500 && bottomLs.get_value() > 2000){
      nineCubeTime = millis();
      nineCubeSafety = true;
    }
    if(nineCubeSafety && (topLs.get_value() > 500 || bottomLs.get_value() < 700)){
      nineCubeSafety = false;
    }
    if(nineCubeSafety && nineCubeTime + 200 < millis()) break;
    if(tracking.driveError - 5 < 1)break;
    delay(1);
    printf("top: %d, b: %d", topLs.get_value(), bottomLs.get_value());
  }
  intakeR.move(15);
  intakeL.move(-15);
  angler.move_absolute(3500, 200);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  fBar.move_absolute(650,100);
  outtakeTime = millis();
  while (true){
    if ((millis() - outtakeTime) > 100)
    {
      intakeR.move(-5);
      intakeL.move(5);
      outtakeState = true;
      printf ("%d| outtakes", millis());
    }
    if (outtakeState && bottomLs.get_value() < 700){
      intakeL.tare_position();
      while(fabs(intakeL.get_position()) < 150 ) delay(1);
      printf("%d| stopped outtaking", millis());
      intakeR.move(15);
      intakeL.move(-15);
      printf ("%d| light sensor covered", millis());
    }
    if (tracking.moveComplete) break;
    delay(2);
  }
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  delay(50);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(27);
  intakeR.move(-27);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  // intakeL.move(-10);
  // intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  delay(100);
  // fBar.move_absolute(600,200);
  // while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.ycoord = 9;
  tracking.xcoord = -31.5;
  tracking.global_angle = tracking.global_angle;
  updateStartTask(false);




  while(!resetDone) delay(1);
  move_to_target_async(-21.5,19, deg_to_rad(-135), false,65);
  tracking.waitForDistance(8);
  angler.move_absolute(1, 200);
  intakeOn();
  tracking.waitForComplete();
  move_to_target_sync(-11, 7, 0,false);
  move_drive(0,-65,0);
  angler.move_absolute(1, 200);
  fBar.move_absolute(1,200);
  delay(500);
  tracking.flattenAgainstWall(false);
  updateStopTask();
  tracking.ycoord = 0;
  tracking.global_angle = 0;
  updateStartTask(false);
  move_to_target_sync(0, 16, deg_to_rad(90),false);
  printf("GLOBAL ANGLE IS %f\n",rad_to_deg(tracking.global_angle));
  move_drive(0, 50, 0);
  while(tracking.xcoord<=6) delay(1);
  delay(200);
  move_to_target_async(-6, 16, deg_to_rad(90), false);
  tracking.waitForComplete();
  fBar.move_absolute(FBAR_TOP, 150);
  while(fBar.get_position() < FBAR_TOP) delay(1);
  move_to_target_sync(9.5, 14.5, deg_to_rad(90), true, 60);
  intakeReverse();
  delay(800);
  move_to_target_async(0,10,deg_to_rad(90), false, 60);
  tracking.waitForDistance(4);
  intakeOn();
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  while(fBar.get_position() > 100) delay(1);
  move_to_target_sync(-14, 39, 0, false);
  move_drive(0, 40, 0);
  while(tracking.ycoord<44.5) delay(1);
  move_to_target_async(-12, 36, 0);
  fBar.move_absolute(FBAR_MID, 200);
  tracking.waitForComplete();
  while(fBar.get_position()<FBAR_MID-50) delay(1);
  move_to_target_sync(-11.5, 43, 0, false);
  intakeReverse();
  delay(800);
  move_to_target_async(-22, 36, 0,false);
  tracking.waitForDistance(4);
  intakeOn();
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  while(fBar.get_position()>50) delay(1);
  uint32_t cubeTimer = millis();
  move_to_target_async(-21, 51.5, 0,false,60);
  while(!tracking.moveComplete) {

    if(millis()-cubeTimer>1200) {
      tracking.moveComplete = true;
      moveStopTask();
    }
  }
  tracking.waitForComplete();
  delay(200);
  move_drive(0, -60, 0);
  while(tracking.ycoord>43) delay(1);
  // while(tracking.xcoord<13) delay(1);
  // brake();
  // delay(100);
  // move_drive(0,-50,0);
  // delay(500);
  // brake();
  move_drive(-65, 0, 0);
  delay(300);
  uint32_t timer = millis();
  while((tracking.velocityB!=0 || front_L.get_actual_velocity() != 0) && millis()-timer < 1500) delay(1);
  delay(150);
  updateStopTask();
  tracking.xcoord = -40.5;
  tracking.global_angle = 0;
  updateStartTask(false);
  move_drive(0,0,0);
  move_to_target_async(-27.5, 28, deg_to_rad(-90));
  fBar.move_absolute(FBAR_MID, 200);
  tracking.waitForComplete();
  while(fBar.get_position()< FBAR_MID-20) delay(1);
  intakeReverse();
  delay(800);
  move_drive(0, -40, 0);
  while(tracking.xcoord<-24) delay(1);
  move_to_target_async(-28, 70,0,false, 65);
  tracking.waitForDistance(38);
  intakeOn();
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  move_to_target_sync(-21,110,0,false,55);
  delay(75);
  move_to_target_async(-27.5, 110, -M_PI/4);
  fBar.move_absolute(650,100);
  angler.move_absolute(ANGLER_MID, 130);
  tracking.waitForComplete();
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(27);
  intakeR.move(-27);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  // intakeL.move(-10);
  // intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  delay(50);
  updateStopTask();
  tracking.xcoord = 0;
  tracking.ycoord = 0;
  tracking.global_angle = tracking.global_angle;
  updateStartTask(false);
  move_to_target_sync(10, -10, -M_PI/4,false);
  fBar.move_absolute(1,200);
  angler.move_absolute(1,200);
  intakeOn();
  move_to_target_sync(30,-10,M_PI/2,false);
  move_to_target_sync(36,-10,M_PI/2,false);
  delay(50);
  move_to_target_sync(32, -10,M_PI/2,false);
  fBar.move_absolute(FBAR_TOP, 150);
  while(fBar.get_position() < FBAR_TOP) delay(1);
  move_to_target_sync(41.5, -10, M_PI/2,false, 60);
  intakeL.move(127);
  intakeR.move(-127);
  delay(800);
  move_drive(0,-60,0);
  delay(100);
  return;


}

void newSkills() {
  int LsCheck =0;
  angler.move_absolute(1, 200);
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(50);
  fBar.move_absolute(1, 200);
  intakeOn();
  move_drive(0, 127, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(0, 36, 0, false, 90); //60
  tracking.waitForDistance(18);
  move_to_target_sync(0, 36, 0, false, 70); //50
  tracking.waitForComplete();
  delay(70);
  move_drive(70,0,0);
  while(tracking.xcoord<5) delay(1);
  move_to_target_sync(10, 43, 0, false, 127);
  delay(50);
  move_to_target_async(10, 36 , 0, false, 127);
  fBar.move_absolute(FBAR_MID+100, 200);
  while(fBar.get_position()<FBAR_MID) delay(1);
  tracking.waitForComplete();
  // move_to_target_sync(9, 43, 0,false);
  move_drive(0, 75, 0);
  while(tracking.ycoord<41) delay(1);
  brake();
  delay(50);
  //9 44
  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  // while(fabs(intakeL.get_position())<450) delay(1);
  //
  // intakeL.move(60);
  // intakeR.move(-60);
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);

  move_to_target_async(-7.5, 27, -M_PI/2,false);
  tracking.waitForDistance(12);
  intakeOn();
  fBar.move_absolute(FBAR_MID+800, 200);
  // delay(750);
  // intakeL.move(-8);
  // intakeR.move(8);
  tracking.waitForComplete();
  move_drive(0, 75, 0);
  delay(100);
  tracking.LSLineup(true,false);
  delay(200);
  updateStopTask();
  tracking.ycoord = tracking.ycoord;
  tracking.xcoord = -18;
  tracking.global_angle = -M_PI/2;
  updateStartTask(false);
  delay(50);
  // move_to_target_async(-6.5, 27, -M_PI/2,false,30);
  move_drive(0, -55, 0);
  while(tracking.xcoord < -8)delay(1);
  while(tracking.xcoord < -7)delay(1);
  brake();
  delay(50);
  fBar.move_absolute(FBAR_MID+350, 100);
  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);
  fBar.move_absolute(FBAR_MID+600, 200);
  while(fBar.get_position()<FBAR_MID+550) delay(1);
  move_to_target_async(19, 13, -3*M_PI/2,false,127);
  tracking.waitForDistance(2);
  intakeOn();
  tracking.waitForComplete();
  fBar.move_absolute(FBAR_TOP+50, 100);
  while(fBar.get_position()<FBAR_TOP-50) delay(1);
  move_to_target_sync(31, 13, -3*M_PI/2,false,60);
  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);
  move_to_target_sync(18, 6, -3*M_PI/2,false,80);
  move_to_target_async(-2, 38.5, deg_to_rad(15),false,127);
  tracking.waitForDistance(6);
  fBar.move_absolute(1, 200);
  intakeOn();
  tracking.waitForComplete();
  while(fBar.get_position()>50) delay(1);
  move_to_target_sync(-2.5, 49.5,deg_to_rad(15),false,65);
  delay(50);
  move_to_target_sync(-5, 49.5,0,false,127);
  move_to_target_sync(-5, 63.5,0,false,127);
  move_to_target_sync(-3, 70,0,false,127);
  move_to_target_async(0, 110.0,0,false,90);
  while(topLs.get_value() > 500 || bottomLs.get_value() > 2500) {
    if(bottomLs.get_value() > 2500 && tracking.moveComplete) LsCheck++;
    else LsCheck = 0;
    if (LsCheck >= 40) break;
    delay(1);
  }
  intakeR.move(20);
  intakeL.move(-20);
  angler.move_absolute(3500, 200);
  tracking.waitForComplete();
  move_to_target_async(-3,112,-M_PI/4,false);
  angler.move_absolute(ANGLER_MID, 150);
  fBar.move_absolute(650, 200);
  tracking.waitForComplete();
  while(fBar.get_position()< 600)delay(1);
  fBar.move(30);
  tracking.LSLineup(true, true, 1500);
  updateStopTask();
  tracking.xcoord=0;
  tracking.ycoord=0;
  tracking.global_angle = tracking.global_angle;
  updateStartTask(false);
  fBar.move(5);
  move_to_target_async(1.5, -1.5, tracking.global_angle,false,25);
  tracking.waitForDistance(0.5);
  intakeL.move(35);
  intakeR.move(-35);
  while((fabs(intakeL.get_actual_velocity())>0 || fabs(intakeR.get_actual_velocity())>0) && angler.get_position()<ANGLER_TOP-250) delay(1);
  angler.move_absolute(ANGLER_TOP, 130);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-800) delay(1);
  angler.move_absolute(ANGLER_TOP, 85);
  while(angler.get_position()<ANGLER_TOP-300) delay(1);
  angler.move_absolute(ANGLER_TOP,130);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  angler.move_absolute(ANGLER_TOP+150, 100);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  delay(100);
  intakeL.move(15);
  intakeR.move(-15);
  move_drive(0,-60,0);
  while(tracking.ycoord>-1) delay(1);
  fBar.move_absolute(650, 200);
  brake();
  move_drive(0,60,0);
  uint32_t moveFTimer = millis();
  while(tracking.ycoord<-0.5 && millis()-moveFTimer<500) delay(1);
  delay(50);
  brake();
  delay(50);
  move_drive(0,-60,0);
  while(tracking.ycoord>-3) delay(1);
  angler.move_absolute(1,200);
  while(tracking.ycoord>-10) delay(1);
  move_drive(0,0,0);
  fBar.move_absolute(1,200);
  move_to_target_sync(15, -3, M_PI/2,false,127);
  intakeOn();
  move_to_target_sync(26, -3, M_PI/2,false,127);
  move_drive(-60,0,0);
  while(tracking.xcoord<0) delay(1);
  bool success = false;
  int backCount = 0;
  while(!success) {
    if(tracking.velocityB==0) backCount++;
    else backCount = 0;
    if(backCount>55) {
      success=true;
    }
    delay(1);
  }
  delay(100);
  updateStopTask();
  tracking.ycoord = 0;
  tracking.xcoord = tracking.xcoord;
  tracking.global_angle = M_PI/2;
  updateStartTask(false);
  move_to_target_sync(32, -12.5, M_PI/2,false,127);
  move_drive(0, 75, 0);
  while(tracking.xcoord < 38)delay(1);
  brake();
  delay(50);
  move_to_target_async(30, -12.5, M_PI/2,false,127);
  fBar.move_absolute(FBAR_TOP, 100);
  tracking.waitForComplete();
  fBar.move_absolute(FBAR_TOP+50, 150);
  while(fBar.get_position()<FBAR_TOP) delay(1);
  move_to_target_sync(43, -16, M_PI/2,false,65);
  brake();
  delay(50);
  intakeReverse();
  delay(800);
  move_to_target_sync(33,-16,M_PI/2,false,55);
  fBar.move_absolute(1,200);
  while(fBar.get_position()>1500) delay(1);
  move_to_target_sync(36,-5,M_PI,false,127);
  delay(100);
  tracking.LSLineup(true,false,2000,-65);
  delay(100);
  updateStopTask();
  tracking.global_angle = M_PI;
  tracking.xcoord = tracking.xcoord;
  tracking.ycoord = 0;
  updateStartTask(false);
  intakeOn();
  move_to_target_sync(30.5, -22.5, M_PI,false,65);
  // move_to_target_sync(30.5, -18, M_PI,false,127);
  // fBar.move_absolute(towerHeights[0]+ 50, 200);
  // while(fBar.get_position()<towerHeights[0]) delay(1);
  // brake();
  // move_to_target_async(30.5, -22.5, M_PI,false,65);
  // tracking.waitForDistance(1);
  // fBar.move(-127);
  // tracking.waitForComplete();
  // brake();
  // delay(50);
  // move_to_target_async(30.5, -60, M_PI,false,127);
  // tracking.waitForDistance(4);
  // fBar.move_absolute(towerHeights[0]+ 50, 200);
  // tracking.waitForComplete();
  // while(fBar.get_position()<towerHeights[0]) delay(1);
  // brake();
  // move_to_target_async(30.5, -71, M_PI,false,55);
  // tracking.waitForDistance(0.5);
  // fBar.move_absolute(towerHeights[0]-150, 200);
  // tracking.waitForComplete();
  move_to_target_async(30.5, -60, M_PI,false,127);
  move_to_target_sync(29.5, -114, M_PI,false,127);
  move_to_target_async(2.5, -105, 5*M_PI/4 ,false,60);


  angler.move_absolute(ANGLER_MID, 130);
  fBar.move_absolute(650, 200);
  tracking.waitForComplete();
  while(fBar.get_position()< 600)delay(1);
  fBar.move(30);
  tracking.LSLineup(true, true, 1500);
  updateStopTask();
  tracking.reset();
  updateStartTask(true);
  fBar.move(5);
  // move_to_target_sync(1.5, -1.5, tracking.global_angle,false,25);
  intakeL.move(45);
  intakeR.move(-45);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  angler.move_absolute(ANGLER_TOP, 160);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-800) delay(1);
  angler.move_absolute(ANGLER_TOP, 85);
  while(angler.get_position()<ANGLER_TOP-300) delay(1);
  angler.move_absolute(ANGLER_TOP,130);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  angler.move_absolute(ANGLER_TOP+150, 100);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  delay(100);
  intakeL.move(15);
  intakeR.move(-15);
  move_drive(0,-60,0);
  fBar.move_absolute(650, 200);
  while(tracking.ycoord>-1) delay(1);
  brake();
  move_drive(0,60,0);
  moveFTimer = millis();
  while(tracking.ycoord<-0.5 && millis()-moveFTimer<500) delay(1);
  delay(50);
  brake();
  delay(50);
  move_drive(0,-60,0);
  while(tracking.ycoord>-3) delay(1);
  angler.move_absolute(1,200);
  while(tracking.ycoord>-10) delay(1);
  move_drive(0,0,0);
  return;




  // fBar.move_absolute(1,200);
  // move_to_target_sync(-15, -3, -M_PI/2,false,127);
  // intakeOn();
  // move_to_target_sync(-26, -3, -M_PI/2,false,127);
  // move_drive(60,0,0);
  // delay(50);
  // bool success2 = false;
  // int backCount2 = 0;
  // while(!success2) {
  //   if(tracking.velocityB==0) backCount2++;
  //   else backCount2 = 0;
  //   if(backCount2>55) {
  //     success2=true;
  //   }
  //   delay(1);
  // }
  // delay(100);
  // updateStopTask();
  // tracking.ycoord = 0;
  // tracking.xcoord = tracking.xcoord;
  // tracking.global_angle = -M_PI/2;
  // updateStartTask(false);
  //
  // return;


  // move_to_target_sync(-28, -9.5, -M_PI/2,false,127);
  // move_drive(0, 75, 0);
  // while(tracking.xcoord > -39)delay(1);
  // brake();
  // delay(50);
  // move_to_target_async(-28, -9.5, -M_PI/2,false,127);
  // fBar.move_absolute(FBAR_TOP, 100);
  // tracking.waitForComplete();
  // fBar.move_absolute(FBAR_TOP, 200);
  // while(fBar.get_position()<FBAR_TOP-50)delay(1);
  // move_to_target_sync(-42, -9.5, -M_PI/2,false,55);
  // brake();
  // delay(50);
  // intakeReverse();
  // delay(800);



}

void skills2() {
  updateStopTask();
  tracking.ycoord = 9.5;
  tracking.xcoord = 31.5;
  tracking.global_angle = M_PI/2;
  updateStartTask(false);
  fBar.move_absolute(400, 200);
  while(fBar.get_position() < 395 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  delay(1);
  move_to_target_async(40,23.5, M_PI/2,false,127);
  tracking.waitForDistance(8);
  intakeOn();
  tracking.waitForDistance(1.5);
  move_to_target_sync(57,23.5, M_PI/2,false,127);
  tracking.waitForComplete();
  move_to_target_async(43,23.5, M_PI/2,false,127);
  fBar.move(127);
  tracking.waitForComplete();
  while(fBar.get_position()<FBAR_TOP-10) delay(1);
  fBar.move_absolute(FBAR_TOP, 200);
  move_drive(0,0,0);
  // move_to_target_sync(57.5,23.5, M_PI/2,false,45);
  move_drive(0,50,0);
  while(tracking.xcoord<57) delay(1);
  move_drive(0,0,0);

  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);
  move_to_target_async(28,13,-M_PI/4,false,127, true);
  tracking.waitForDistance(3);
  fBar.move_absolute(FBAR_MID, 200);
  intakeOn();
  tracking.waitForDistance(1);
  move_to_target_async(14, 23, -M_PI/4,false,127, true);
  tracking.waitForDistance(15);
  fBar.move_absolute(FBAR_MID, 200);
  intakeOn();
  tracking.waitForComplete();
  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);
  fBar.move_absolute(FBAR_MID+100, 200);
  delay(50);

  move_to_target_async(26.5, 10, 0,false,127,true);
  tracking.waitForDistance(6);
  fBar.move_absolute(1, 200);
  tracking.waitForComplete();
  tracking.LSLineup(true, false,1400,-60);
  printf("stuck A\n");
  updateStopTask();
  tracking.ycoord = 9.5;
  tracking.xcoord = tracking.xcoord;
  tracking.global_angle = 0;
  updateStartTask(false);
  printf("stuck B\n");
  delay(50);
  intakeOn();
  move_to_target_async(24.5,52.3,0,false,127);
  tracking.waitForDistance(1.2);
  move_to_target_async(20.5, 121, 0,false,127);
  tracking.waitForDistance(55);
  move_to_target_async(25.5, 121, 0,false,90);
  int LsCheck = 0;
  while(topLs.get_value() > 500 || bottomLs.get_value() > 2500) {
    if(bottomLs.get_value() > 2500 && tracking.moveComplete) LsCheck++;
    else LsCheck = 0;
    if (LsCheck >= 40) break;
    delay(1);
  }
  intakeL.move(-17);
  intakeR.move(17);
  fBar.move_absolute(700, 200);
  angler.move_absolute(ANGLER_MID, 160);
  tracking.waitForComplete();
  delay(300);
  move_to_target_sync(18.5, 124, -M_PI/4,false,127,true);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(45);
  intakeR.move(-45);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-1150) delay(1);
  angler.move(90);
                  // while(angler.get_position()<ANGLER_TOP-800) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 85);
                  // while(angler.get_position()<ANGLER_TOP-300) delay(1);
                  // angler.move_absolute(ANGLER_TOP,160);
                  // while(angler.get_position()<ANGLER_TOP-50) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 100);
                  // while(angler.get_position()<ANGLER_TOP-10) delay(1);
                  // delay(100);
                  // fBar.move_absolute(600,200);
                  // while(fBar.get_position()<300)delay(1);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  angler.move(0);
  delay(300);
  fBar.move_absolute(600,200);
  while(fBar.get_position()<300)delay(1);
  move_drive(0,-60,0);
  while(tracking.xcoord<26) delay(1);
  move_drive(0,0,0);
  angler.move_absolute(1, 200);
  fBar.move_absolute(200, 200);
  move_to_target_sync(49, 131.5, -M_PI,false,127,true);
  tracking.LSLineup(true,false,1400,-60);
  updateStopTask();
  tracking.xcoord = tracking.xcoord;
  tracking.ycoord = 134.5;
  tracking.global_angle = -M_PI;
  updateStartTask(false);
  fBar.move_absolute(1, 200);
  intakeOn();
  move_to_target_async(49, 95, -M_PI,false,127);
  tracking.waitForDistance(1.5);
  fBar.move_absolute(FBAR_MID+200, 200);
  tracking.waitForComplete();

  move_to_target_async(10, 108,-M_PI/2, false, 127, true);
  fBar.move_absolute(FBAR_MID+200, 200);
  tracking.waitForComplete();
  tracking.LSLineup(true,false,1500,70);
  delay(75);
  updateStopTask();
  tracking.xcoord = 9.5;
  tracking.ycoord = tracking.ycoord;
  tracking.global_angle = -M_PI/2;
  updateStartTask(false);
  delay(75);
  move_to_target_async(21.5, 108, -M_PI/2, false, 45);
  tracking.waitForDistance(0.2);
  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);
  fBar.move_absolute(FBAR_MID+400, 200);
  delay(50);
  while(fBar.get_position()<FBAR_MID+350) delay(1);
  intakeOn();
  tracking.waitForComplete();


  move_to_target_async(37.5, 94, -M_PI,false,127,true);
  tracking.waitForDistance(7);
  fBar.move_absolute(FBAR_MID, 200);
  tracking.waitForComplete();
  intakeL.move(127);
  intakeR.move(-127);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<900) delay(1);
  intakeL.move(-8);
  intakeR.move(8);


  fBar.move_absolute(FBAR_MID+400, 200);
  while(fBar.get_position()<FBAR_MID-250) delay(1);

  //
  // move_to_target_async(57, 127.5, -3*M_PI/2,false,127,true);
  // tracking.waitForDistance(42);
  // intakeOn();
  // fBar.move_absolute(FBAR_TOP,200);
  //
  // // tracking.waitForComplete();
  // // tracking.LSLineup(true,false,2500,70);
  // //
  // // double curX = tracking.xcoord;
  // //
  // // move_drive(0,-40,0);
  // // while((curX-tracking.xcoord)<2) delay(1);
  // // move_drive(0,0,0);
  //
  // intakeL.move(80);
  // intakeR.move(-80);
  // while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  // intakeL.tare_position();
  // while(fabs(intakeL.get_position())<900) delay(1);
  // intakeL.move(-8);
  // intakeR.move(8);

  move_to_target_async(44.5,132.5,-3*M_PI/2,false,127,true);
  tracking.waitForDistance(12);
  fBar.move_absolute(1,200);
  intakeOn();
  tracking.waitForComplete();
  while(fBar.get_position()>100) delay(1);


  move_to_target_async(75.5,134.5,-3*M_PI/2,false,127);
  tracking.waitForDistance(0.6);
  move_to_target_sync(96, 128, -5*M_PI/4,false,127);
  tracking.waitForComplete();
  move_to_target_sync(109.5, 123.5, -3*M_PI/2,false,127);
  move_to_target_sync(118.5, 123.5, -3*M_PI/2,false,127);
  move_to_target_async(120, 137, -3*M_PI/2,false,127);
  angler.move_absolute(ANGLER_MID,200);
  fBar.move_absolute(650, 200);
  tracking.waitForComplete();

  move_drive(-60,0,0);
  delay(100);
  bool tResetDone = false;
  int count = 0;
  while(tResetDone == false) {
    if(tracking.velocityB == 0.0) count++;
    else count = 0;
    if(count>60) tResetDone = true;
    delay(1);
  }
  updateStopTask();
  tracking.ycoord = 134.5;
  tracking.xcoord = tracking.xcoord;
  tracking.global_angle = M_PI/2;
  updateStartTask(false);
  tracking.LSLineup(true,true,1500,60);
  updateStopTask();
  tracking.ycoord = tracking.ycoord;
  tracking.xcoord = 123.5;
  tracking.global_angle = tracking.global_angle;
  updateStartTask(false);
  move_drive(0,0,0);
  intakeL.move(40);
  intakeR.move(-40);
  angler.move_absolute(ANGLER_TOP, 200);
  while(angler.get_position()<ANGLER_TOP-5) delay(1);
  move_drive(-30,-60,0);
  while(tracking.xcoord>120.0) delay(1);

  move_to_target_async(101.5, 122, M_PI,false,80);
  angler.move_absolute(1, 200);
  fBar.move_absolute(towerHeights[2] + 400, 75);
  tracking.waitForDistance(12);
  intakeOn();
  while(fBar.get_position()<towerHeights[2] +100) delay(1);
  fBar.move_absolute(towerHeights[2] + 400, 100);
  while(fBar.get_position()<towerHeights[2] + 200)delay(1);
  delay(50);
  tracking.waitForComplete();
  move_to_target_sync(100.5, 110.5,M_PI, false, 60);
  fBar.move_absolute(towerHeights[1]- 700, 100);
  move_to_target_async(100.5, 113.5,M_PI, false);
  while(fBar.get_position()>towerHeights[1]-550)delay(1);
  fBar.move_absolute(towerHeights[0]- 500, 100);
  move_to_target_async(100.5, 112.5,M_PI,false);
  while(fBar.get_position()>towerHeights[0]-350)delay(1);
  delay(50);
  fBar.move_absolute(1, 200);
  angler.move_absolute(1, 200);
  tracking.waitForComplete();
  while(fBar.get_position()>100) delay(1);
  move_to_target_sync(100.5,99,M_PI,false,127);
  move_to_target_sync(109.5,99,M_PI,false,127);
  move_to_target_sync(109.5,93,M_PI,false,80);
  move_to_target_sync(122.5,93,M_PI,false,127);
  move_to_target_async(122.5,35,M_PI,false,127);
  tracking.waitForDistance(20);
  move_to_target_sync(126,34,M_PI,false,127);
  angler.move_absolute(ANGLER_MID, 160);
  fBar.move_absolute(650, 200);
  move_to_target_sync(127.5,23,3*M_PI/4,false,127);
  tracking.LSLineup(true,false,1400,60);
  angler.move_absolute(ANGLER_TOP, 130);
  intakeL.move(45);
  intakeR.move(-45);
  delay(50);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  while(angler.get_position()<ANGLER_TOP-1150) delay(1);
  angler.move(90);
                  // while(angler.get_position()<ANGLER_TOP-800) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 85);
                  // while(angler.get_position()<ANGLER_TOP-300) delay(1);
                  // angler.move_absolute(ANGLER_TOP,160);
                  // while(angler.get_position()<ANGLER_TOP-50) delay(1);
                  // angler.move_absolute(ANGLER_TOP, 100);
                  // while(angler.get_position()<ANGLER_TOP-10) delay(1);
                  // delay(100);
                  // fBar.move_absolute(600,200);
                  // while(fBar.get_position()<300)delay(1);
  while(angler.get_position()<ANGLER_TOP-10) delay(1);
  angler.move(0);
  delay(100);
  fBar.move_absolute(600,200);
  while(fBar.get_position()<300)delay(1);
  move_drive(0,-60,0);
  delay(500);
  move_drive(0,0,0);
  // move_to_target_sync(98.5,20.5,M_PI,false,127);

}

void autonomous() {
  setDriveState(driveStates::Auto);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  delay(1);
  while(resetDone == false) delay(1);
  // intakeL.move(127);
  autotimer = pros::millis();
  log("global angle:%f",tracking.global_angle);
  switch(side) {
    case sides::blue:
      switch(cur_auto) {
        case auto1:
          blueLeft();
        break;
        case auto2:
          blue9();
        break;
        case auto3:
          blueFourFirst();
        break;
        case auto4:
          skills2();
        break;
      }
    break;
    case sides::red:
      switch(cur_auto) {
        case auto1:
          redProtect();
        break;
        case auto2:
          red9();
        break;
        case auto3:
          redFourFirst();
        break;
        case auto4:
          skills2();
        break;
      }
    break;
  }

  // skills2();

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
