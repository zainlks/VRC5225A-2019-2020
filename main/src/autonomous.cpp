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

void blueFourFirst() {
  //angler.move_absolute(1700, 200);
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  // angler.move_absolute(1700, 200);
  intakeOn();
  move_drive(0, 127, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(0, 38, 0, false, 90); //60
  tracking.waitForDistance(18);
  move_to_target_sync(0, 39, 0, false, 90); //50
  tracking.waitForComplete();
  delay(70);
  // move_drive(-30,-70,0);
  // while(tracking.ycoord>36.5) delay(1);
   move_to_target_sync(7.5, 39, 0, false, 127);
  move_to_target_sync(7.5, 46, 0,false);
  delay(70);
  move_to_target_async(0, 39, 0,false,127);
  tracking.waitForDistance(2.5); //80
  move_to_target_sync(23.5, 2, 0, false,127);
  move_to_target_async(23.5, 38.5, 0,false,90);
  tracking.waitForDistance(17);
  move_to_target_sync(23.5, 38.5, 0, false, 127);
  move_to_target_async(-6,11.5, deg_to_rad(-135),false,127);
  tracking.waitForDistance(12);
  intakeL.move(-15);
  intakeR.move(15);
  tracking.waitForDistance(7);
  angler.move_absolute(ANGLER_MID-1800, 150);
  fBar.move_absolute(650,100);
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  return;
  intakeL.move(25);
  intakeR.move(-25);
  delay(50);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP-1000, 135);
  while(angler.get_position()<ANGLER_TOP-1100) delay(1);
  // angler.move_absolute(ANGLER_TOP-800,80);
  // while(angler.get_position()<ANGLER_TOP-1000) delay(1);
  angler.move_absolute(ANGLER_TOP,110);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  // fBar.move_absolute(600,200);
  // while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_to_target_sync(0,-10, 0,false);
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
  while(fBar.get_position()<towerHeights[0]) delay(1);
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
  move_to_target_async(-24, 40, 0, false, 115); //60
  tracking.waitForDistance(15);
  move_to_target_sync(-24, 40, 0, false, 70); //50
  tracking.waitForComplete();
  while(lsFilter <20){
    if(topLs.get_value() < 500 || bottomLs.get_value() < 2500)lsFilter ++;
    else lsFilter = 0;
  }
  //while(topLs.get_value() > 500 && bottomLs.get_value() > 2500) delay(1);
  delay(100);
  intakeR.move(15);
  intakeL.move(-15);
  if(tracking.safety) goto dropOff;
  dropOff:
  move_to_target_async(-30,11.5, deg_to_rad(-135),false,127);
  intakeR.move(15);
  intakeL.move(-15);
  angler.move_absolute(ANGLER_MID, 160);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  fBar.move_absolute(650,100);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
    tracking.LSLineup(true, true, 1500);
    angler.move_absolute(ANGLER_TOP, 160);
    intakeL.move(27);
    intakeR.move(-27);
    while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
    fBar.move(5);
    while(angler.get_position()<ANGLER_TOP-800) delay(1);
    angler.move_absolute(ANGLER_TOP, 75);
    while(angler.get_position()<ANGLER_TOP-50) delay(1);
    angler.move_absolute(ANGLER_TOP, 100);
    delay(50);
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
  while(fBar.get_position()> 50) {delay(1);};
  fBar.move(-25);
  master.print(1,0,"%d",millis()-autotimer);
  move_to_target_async(0, 16, 0, false, 50,false,true);
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
  move_to_target_sync(14, 20, (3*M_PI/4),false, 127);
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
  delay(50);
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
  angler.move_absolute(1700, 200);
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(1,200);
  angler.move_absolute(1700, 200);
  intakeOn();
  move_drive(0, 90, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(0, 38, 0, false, 80); //60
  tracking.waitForDistance(18);
  move_to_target_sync(0, 39, 0, false, 70); //50
  tracking.waitForComplete();
  delay(70);
  move_drive(-70,0,0);
  while(tracking.xcoord>-4) delay(1);
  // move_to_target_sync(7.5, 39, 0, false, 127);
  move_to_target_sync(-7.5, 45, 0,false);
  delay(70);
  move_to_target_async(0, 39, 0,false,127);
  tracking.waitForDistance(2.5); //80
  move_to_target_sync(-23.5, 2, 0, false,127);
  move_to_target_async(-23.5, 38.5, 0,false,90);
  tracking.waitForDistance(17);
  move_to_target_sync(-23.5, 38.5, 0, false, 55);
  move_to_target_async(6,11.5, deg_to_rad(135),false,127);
  tracking.waitForDistance(12);
  intakeL.move(-15);
  intakeR.move(15);
  tracking.waitForDistance(7);
  angler.move_absolute(ANGLER_MID-1800, 150);
  tracking.waitForComplete();
  brake();
  delay(75);
  move_drive(0,0,0);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
  intakeL.move(15);
  intakeR.move(-15);
  delay(50);
  tracking.LSLineup(true, true, 1500);
  angler.move_absolute(ANGLER_TOP-1000, 135);
  while(angler.get_position()<ANGLER_TOP-1100) delay(1);
  // angler.move_absolute(ANGLER_TOP-800,80);
  // while(angler.get_position()<ANGLER_TOP-1000) delay(1);
  angler.move_absolute(ANGLER_TOP,110);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  // fBar.move_absolute(600,200);
  // while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_to_target_sync(0,-10, 0,false);
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
  while(fBar.get_position()<towerHeights[0]) delay(1);
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
  move_to_target_sync(24, 2, 0, false,127);
  move_drive(0, 80, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(24, 40, 0, false, 115); //60
  tracking.waitForDistance(15);
  move_to_target_sync(24, 40, 0, false, 70); //50
  tracking.waitForComplete();
  while(lsFilter <15){
    if(topLs.get_value() < 500 || bottomLs.get_value() < 2500)lsFilter ++;
    else lsFilter = 0;
  }
  // while(topLs.get_value() > 500 && bottomLs.get_value() > 2500) delay(1);
  delay(100);
  intakeR.move(15);
  intakeL.move(-15);
  if(tracking.safety) goto dropOff;
  dropOff:
  move_to_target_async(30,11.5, deg_to_rad(135),false,127);
  intakeR.move(15);
  intakeL.move(-15);
  angler.move_absolute(ANGLER_MID, 160);
  // tracking.waitForDistance(7);
  //angler.move_absolute(ANGLER_MID-1800, 110);
  fBar.move_absolute(650,100);
  outtakeTime = millis();
  tracking.waitForComplete();
  move_drive(0,0,0);
  fBar.move(30);
  // angler.move_absolute(ANGLER_TOP-2000, 100);
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

void redProtect(){

  bool outtakeState = false;
  uint32_t outtakeTime = 0;
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(100);

  intakeL.move(-15);
  intakeR.move(15);
  fBar.move_absolute(1,200);
  //delay(50);
  while(fBar.get_position()> 50) {delay(1);};
  fBar.move(-25);
  master.print(1,0,"%d",millis()-autotimer);
  move_to_target_async(0, 16, 0, false, 50,false,true);
  intakeOn();
  // tracking.waitForDistance(12);
  // fBar.move_absolute(towerHeights[2], 200);
  // while(fBar.get_position()<towerHeights[2]-200)delay(1);
  // tracking.waitForComplete();
  // move_to_target_sync(0, 22,0, false, 60);
  // fBar.move_absolute(towerHeights[1]- 500, 150);
  // move_to_target_sync(0, 20,0, false);
  // while(fBar.get_position()>towerHeights[1]-350)delay(1);
  // fBar.move_absolute(towerHeights[0]- 500, 200);
  // move_to_target_sync(0, 22,0,false);
  // while(fBar.get_position()>towerHeights[0]-400)delay(1);
  // delay(50);
  // fBar.move_absolute(1, 200);
  tracking.waitForDistance(12);
  fBar.move_absolute(towerHeights[2] + 400, 200);
  while(fBar.get_position()<towerHeights[2] + 200)delay(1);
  tracking.waitForComplete();
  move_to_target_sync(0, 24, 0, false, 60);
  fBar.move_absolute(towerHeights[1]- 700, 100);
  move_to_target_async(0, 20, 0, false);
  while(fBar.get_position()>towerHeights[1]-550)delay(1);
  fBar.move_absolute(towerHeights[0]- 500, 100);
  move_to_target_async(0, 22, 0,false);
  while(fBar.get_position()>towerHeights[0]-350)delay(1);
  delay(50);
  fBar.move_absolute(1, 200);
  while(fBar.get_position()> 1000)delay(1);

  move_to_target_sync(-4, 46, deg_to_rad(-45), false);
  move_drive(0,-65,0);
  delay(300);
  move_to_target_sync(-14, 28, deg_to_rad(-135), false, 127);
  move_to_target_async(-23.5, 17, deg_to_rad(-135), false, 80);
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
    if (outtakeState && bottomLs.get_value() < 2000){
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
  intakeL.move(20);
  intakeR.move(-20);
  while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  fBar.move(5);
  // intakeL.move(-10);
  // intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);
  delay(100);
  // fBar.move_absolute(600,200);
  // while(fBar.get_position()<300)delay(1);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  move_to_target_sync(0, -10, 0, false, 127, false, false);

  return;
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
  updateStopTask();
  tracking.global_angle = deg_to_rad(-45);
  updateStartTask(false);
  angler.move_absolute(1, 200);
  fBar.move_absolute(300, 200);
  while(fBar.get_position() < 295 ){delay(1);}
  delay(100);
  master.print(1,0,"%d",millis()-autotimer);
  intakeL.move(-10);
  intakeR.move(10);
  fBar.move_absolute(FBAR_MID+200,200);
  angler.move_absolute(ANGLER_MID-2700, 150);
  while(fBar.get_position() < FBAR_MID) delay(1);
  move_to_target_sync(-12,12,-M_PI/4,false);
  intakeReverse();
  delay(800);
  fBar.move_absolute(1,200);
  angler.move_absolute(1, 200);
  move_to_target_sync(0,2.5,0,false);
  intakeOn();
  move_drive(0, 90, 0); //80
  while(tracking.ycoord<9)delay(1);
  move_to_target_async(0, 38, 0, false, 80); //60
  tracking.waitForDistance(18);
  move_to_target_sync(0, 39, 0, false, 70); //50
  tracking.waitForComplete();

  delay(70);
  move_drive(70,0,0);
  while(tracking.xcoord<4) delay(1);
  // move_to_target_sync(7.5, 39, 0, false, 127);
  move_to_target_sync(7.5, 45, 0,false);
  delay(70);
  move_to_target_async(7.5,38,0,false);
  tracking.waitForDistance(3);
  fBar.move_absolute(FBAR_MID+100,200);
  angler.move_absolute(ANGLER_MID-2700, 150);
  tracking.waitForComplete();
  while(fBar.get_position() < FBAR_MID-20) delay(1);
  move_to_target_sync(7.5, 44, 0,false);

  intakeL.move(80);
  intakeR.move(-80);
  while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.tare_position();
  while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
  intakeL.move(-8);
  intakeR.move(8);

  move_to_target_async(7.5,32,0,false);
  tracking.waitForDistance(5);
  intakeOn();
  fBar.move_absolute(1,200);
  angler.move_absolute(1,200);
  tracking.waitForComplete();
  while(fBar.get_position()>200) delay(1);
  move_to_target_sync(0,48,0,false);
  delay(100);
  move_to_target_sync(-4,38,0,false);
  move_to_target_sync(-4,71,0,false);
  move_to_target_sync(-3,71,0,false);
  move_to_target_sync(-3,115,0,false,70);
  delay(100);
  move_to_target_sync(-3,108,0,false);
  angler.move_absolute(ANGLER_MID-2000,120);
  move_to_target_sync(-8,106,-M_PI/4,false);
  tracking.LSLineupSkills(true,false);
  updateStopTask();
  tracking.global_angle = tracking.global_angle;
  tracking.xcoord = 0;
  tracking.ycoord = 0;
  updateStartTask(false);
  intakeL.move(25);
  intakeR.move(-25);
  delay(100);
  angler.move_absolute(ANGLER_TOP, 100);
  while((intakeL.get_actual_velocity()>1 || intakeR.get_actual_velocity()>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
  intakeL.move(-10);
  intakeR.move(10);
  while(angler.get_position()<ANGLER_TOP-50) delay(1);

  move_to_target_sync(10,-10,-M_PI/4,false);
  angler.move_absolute(1,200);
  intakeOn();
  move_to_target_sync(21.5,-28,-M_PI,false);
  move_to_target_sync(21.5,-40,-M_PI,false);
  move_to_target_sync(13,-22,-M_PI/2,false);
  fBar.move_absolute(FBAR_MID+200,200);
  angler.move_absolute(ANGLER_MID-2700, 150);
  while(fBar.get_position() < FBAR_MID) delay(1);
  move_to_target_sync(5,-22,-M_PI/2,false);
  intakeReverse();
  delay(800);
  move_to_target_sync(16,-22,-M_PI/2,false);
  fBar.move_absolute(1,200);
  move_drive(70,0,0);
  while(tracking.ycoord<-7) delay(1);
  intakeOn();
  move_to_target_sync(30,-6,M_PI/2,false);
  move_to_target_sync(40,-6,M_PI/2,false);
  move_to_target_sync(32,-6,M_PI/2,false);
  fBar.move_absolute(FBAR_TOP+100,200);
  angler.move_absolute(ANGLER_MID-2700, 150);
  while(fBar.get_position() < FBAR_TOP) delay(1);
  move_to_target_sync(41.5,-6,M_PI/2,false);
  intakeReverse();
  delay(800);
  move_to_target_async(30,-6,M_PI,false);
  tracking.waitForDistance(6);
  fBar.move_absolute(1,200);


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
          skills();
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
          skills();
        break;
      }
    break;

  }



  // intakeOn();
  // fBar.move_absolute(towerHeights[2], 200);
  // while(fBar.get_position()<towerHeights[2]-200)delay(1);
  // move_to_target_sync(0, 11.5,0, false, 60);
  // fBar.move_absolute(towerHeights[1]- 500, 150);
  // move_to_target_sync(0, 9.5,0, false);
  // while(fBar.get_position()>towerHeights[1]-350)delay(1);
  // fBar.move_absolute(towerHeights[0]- 500, 200);
  // move_to_target_sync(0, 11.5,0,false);
  // while(fBar.get_position()>towerHeights[0]-400)delay(1);
  // delay(50);
  // fBar.move_absolute(1, 200);
  // move_to_target_async(0, 15,0,false);
  // while(fBar.get_position()>50)delay(1);
  // fBar.move(-13);
  // tracking.waitForComplete();



  // angler.move_absolute(2000,200);
  // tracking.waitForComplete();
  // move_drive(0,17,0);
  // while(fBar.get_position() < (towerHeights[2]-50)){delay(2);}
  //
  // move_to_target_sync(0, 23.5, 0,false,127);
  // fBar.move_absolute(1, 120);
  // while(fBar.get_position()>towerHeights[1]) delay(1);
  // move_to_target_sync(0,25.5,0, false);
  // while(fBar.get_position()>50) delay(1);
  // move_to_target_sync(0, 30.5, 0, false);
  // tracking.turn_to_angle(deg_to_rad(90));
  // delay(500);
  // printf("%f", deg_to_rad(tracking.global_angle));

  // newSkills();

  // tracking.turn_to_angle(deg_to_rad(225));
  // tracking.move_xy(10, y);
  //move_to_target_sync(10,10,0,)


  // move_to_target_sync(-32,13.5, deg_to_rad(-135),false,127);
  // tracking.LSLineupSkills(true,false, 1500);
  // delay(5000);
  // updateStopTask();
  // tracking.ycoord=0;
  // tracking.xcoord = 0;
  // updateStartTask(false);
  // delay(50);
  // move_to_target_sync(10, 10, 0,true);
  // delay(200);
  // move_to_target_sync(0, 0, M_PI/2,false,127);
  // delay(200);
  // printf("global angle is: %f\n", rad_to_deg(tracking.global_angle));
  // delay(500);
  // move_to_target_sync(0, 0, 0,false,127);
  // delay(200);
  // printf("global angle is: %f\n", rad_to_deg(tracking.global_angle));
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
