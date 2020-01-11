#include "fBar.hpp"

fBarStates fBarState = fBarStates::Idle;
fBarStates fBarStateLast = fBarState;
int fBarStateChangeTime = 0;
int cubeHeightCounter = 0;
void setfBarState(fBarStates state) {
  log("Going from %d", fBarState);
	fBarStateLast = fBarState;
	fBarState = state;
	fBarStateChangeTime = pros::millis();
  log(" to %d\n", fBarState);
}

void fBarCal()
{
  uint32_t timeout_time = millis() + 100;
  bool success = true;
  fBar.move(-50);
  delay(100);
  while (fabs(fBar.get_actual_velocity()) < 17 && (success = (millis() < timeout_time)))
  {
    delay(10);
  }
  timeout_time = millis() + 3500;
  while (fabs(fBar.get_actual_velocity()) > 15 && (success = (millis() < timeout_time)))
	{
		delay(10);
	}
  delay(100);
  fBar.tare_position();
  fBar.move(-13);
  setfBarState(fBarStates::Idle);
}

void fBarHandle() {
  switch(fBarState) {
    case fBarStates::Idle:
      if(fBar.get_position()<20 && !gui_running) fBar.move(-13);
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck) {
        fBar.move_absolute(FBAR_MID-50, 200);
        angler.move_absolute(ANGLER_MID-2700, 150);
        setAnglerState(anglerStates::Mid);
        setfBarState(fBarStates::Mid);
      }
      if(master.get_digital_new_press(UP_CUBE_HEIGHT)) {
        fBar.move_absolute(towerHeights[0], 100);
        // angler.move_absolute(600, 50);
        setfBarState(fBarStates::Tower);
        cubeHeightCounter = 1;
      }
      break;
    case fBarStates::Tower:
      if(master.get_digital_new_press(UP_CUBE_HEIGHT)) {
          printf("pressed!\n");
          fBar.move_absolute(towerHeights[cubeHeightCounter], 100);
          printf("pos is: %d\n", towerHeights[cubeHeightCounter]);
          printf("i am here now\n");
          cubeHeightCounter++;
      }
      if(master.get_digital_new_press(DOWN_CUBE_HEIGHT)) {
        fBar.move_absolute(towerHeights[cubeHeightCounter], 100);
        cubeHeightCounter--;
      }
      if(master.get_digital_new_press(FBAR_DOWN)) {
        fBar.move_absolute(1, 120);
        while(fBar.get_position()>towerHeights[1]) delay(1);
        // setDriveState(driveStates::Auto);
        // tracking.reset();
        // move_to_target_sync(0,2,0, false);
        // tracking.reset();
        while(fBar.get_position()>50) delay(1);
        cubeHeightCounter = 0;
        setfBarState(fBarStates::Idle);
        // setDriveState(driveStates::Driver);
      }
    break;
    case fBarStates::Top:
      if(fabs(FBAR_TOP - fBar.get_position()) < 10) fBar.move(15);
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck){
        fBar.move_absolute(1, 200);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
        setfBarState(fBarStates::Idle);
      }
      if(master.get_digital_new_press(FBAR_DOWN)){
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
      }
      // if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      //   updateStopTask();
      //   tracking.reset();
      //   updateStartTask();
      //   move_drive(0,-70,0);
      //   delay(250);
      //   fBar.move_absolute(FBAR_TOP+200,200);
      //   setDriveState(driveStates::Auto);
      //   move_to_target_sync(0, 8, 0, false, 80, false, false, true);
      //   intakeL.move(80);
      //   intakeR.move(-80);
      //   while(rightLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.tare_position();
      //   while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.move(-8);
      //   intakeR.move(8);
      //   move_to_target_async(0,0,0,false,80,false,false,true);
      //   tracking.waitForDistance(2);
      //   intakeL.move(-127);
      //   intakeR.move(127);
      //   tracking.waitForComplete();
      //   intakeL.move(80);
      //   intakeR.move(-80);
      //   while(rightLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.tare_position();
      //   while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.move(-8);
      //   intakeR.move(8);
      //   setDriveState(driveStates::Driver);
      // }
      break;
    case fBarStates::Mid:
      if(fabs(FBAR_MID - fBar.get_position()) < 10) fBar.move(15);
      if(master.get_digital_new_press(FBAR_DOWN)){
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
      }
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck){
        fBar.move_absolute(FBAR_TOP-50, 150);
        setfBarState(fBarStates::Top);
      }
      // if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      //   updateStopTask();
      //   tracking.reset();
      //   updateStartTask();
      //   move_drive(0,-70,0);
      //   delay(250);
      //   fBar.move_absolute(FBAR_MID+200,200);
      //   setDriveState(driveStates::Auto);
      //   move_to_target_sync(0, 7, 0, false, 80, false, false, true);
      //   intakeL.move(80);
      //   intakeR.move(-80);
      //   while(rightLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.tare_position();
      //   while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.move(-8);
      //   intakeR.move(8);
      //   move_to_target_async(0,0,0,false,80,false,false,true);
      //   tracking.waitForDistance(2);
      //   intakeL.move(-127);
      //   intakeR.move(127);
      //   tracking.waitForComplete();
      //   intakeL.move(80);
      //   intakeR.move(-80);
      //   while(rightLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.tare_position();
      //   while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
      //   intakeL.move(-8);
      //   intakeR.move(8);
      //   setDriveState(driveStates::Driver);
      // }
      break;
  }
}
