#include "fBar.hpp"

fBarStates fBarState = fBarStates::Idle;
fBarStates fBarStateLast = fBarState;
int fBarStateChangeTime = 0;
int cubeHeightCounter = 0;
void setfBarState(fBarStates state) {
  printf("Going from %d", fBarState);
	fBarStateLast = fBarState;
	fBarState = state;
	fBarStateChangeTime = pros::millis();
  printf(" to %d\n", fBarState);
}

void fBarCal()
{
  uint32_t timeout_time = millis() + 100;
  bool success = true;
  fBar.move(-50);
  delay(100);
  while (fabs(fBar.get_actual_velocity()) < 12 && (success = (millis() < timeout_time)))
  {
    delay(10);
  }
  timeout_time = millis() + 3500;
  while (fabs(fBar.get_actual_velocity()) > 10 && (success = (millis() < timeout_time)))
	{
		delay(10);
	}
  delay(100);
  fBar.tare_position();
  fBar.move(-10);
  setfBarState(fBarStates::Idle);
}

void fBarHandle() {
  switch(fBarState) {
    case fBarStates::Idle:
      if(fBar.get_position()<20) fBar.move(-8);
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck) {
        fBar.move_absolute(FBAR_MID, 200);
        angler.move_absolute(ANGLER_MID-500, 40);
        setAnglerState(anglerStates::Mid);
        setfBarState(fBarStates::Mid);
      }
      if(master.get_digital_new_press(UP_CUBE_HEIGHT)) {
        fBar.move_absolute(towerHeights[0], 100);
        angler.move_absolute(600, 50);
        setfBarState(fBarStates::Tower);
        cubeHeightCounter++;
      }
      break;
    case fBarStates::Tower:
    if(master.get_digital_new_press(UP_CUBE_HEIGHT)) {
      fBar.move_absolute(towerHeights[cubeHeightCounter], 100);
      cubeHeightCounter++;
    }
    if(master.get_digital_new_press(DOWN_CUBE_HEIGHT)) {
      fBar.move_absolute(towerHeights[cubeHeightCounter], 100);
      cubeHeightCounter--;
    }
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
      fBar.move_absolute(1, 60);
      while(fBar.get_position()>towerHeights[1]) delay(1);
      setDriveState(driveStates::Auto);
      tracking.reset();
      tracking.move_to_target(0,3,0, false);
      tracking.reset();
      while(fBar.get_position()>50) delay(1);
      tracking.move_to_target(0, 5, 0, false);
      cubeHeightCounter = 0;
      setfBarState(fBarStates::Idle);
      setDriveState(driveStates::Driver);
    }
    case fBarStates::Top:
      if(fabs(FBAR_TOP - fBar.get_position()) < 10) fBar.move(15);
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck){
        fBar.move_absolute(1, 200);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
        setfBarState(fBarStates::Idle);
      }
      break;
    case fBarStates::Mid:
      if(fabs(FBAR_MID - fBar.get_position()) < 10) fBar.move(15);
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
      }
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck){
        fBar.move_absolute(FBAR_TOP, 150);
        setfBarState(fBarStates::Top);
      }
      break;
  }
}
