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
  // fBar.move(0);
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
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
				fBar.move_absolute(550,100);
        setfBarState(fBarStates::InZone);
			 }
      if(master.get_digital_new_press(UP_CUBE_HEIGHT)) {
        fBar.move_absolute(towerHeights[0], 100);
        // angler.move_absolute(600, 50);
        setfBarState(fBarStates::Tower);
        cubeHeightCounter = 1;
      }
      break;
    case fBarStates::InZone:
    if(master.get_digital_new_press(FBAR_DOWN)){
      fBar.move_absolute(1, 200);
      setfBarState(fBarStates::Idle);
      angler.move_absolute(1, 200);
      setAnglerState(anglerStates::Idle);
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
        angler.move_absolute(1, 200);
        while(fBar.get_position()>towerHeights[1]) delay(1);
        // setDriveState(driveStates::Auto);
        // tracking.reset();
        // move_to_target_sync(0,2,0, false);
        // tracking.reset();
        while(fBar.get_position()>50) delay(1);
        cubeHeightCounter = 0;
        setfBarState(fBarStates::Idle);
        setAnglerState(anglerStates::Idle);
        // setDriveState(driveStates::Driver);
      }
    break;
    case fBarStates::Top:
      if(fabs(FBAR_TOP - fBar.get_position()) < 10) fBar.move(8);
      if(master.get_digital_new_press(TOWER_HEIGHT)){
        fBar.move_absolute(1, 200);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
        setfBarState(fBarStates::Idle);
      }
      if(master.get_digital_new_press(FBAR_DOWN)){
        angler.move_absolute(1, 200);
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      break;
    case fBarStates::Mid:
      if(fabs(FBAR_MID - fBar.get_position()) < 10) fBar.move(8);
      if(master.get_digital_new_press(FBAR_DOWN)){
        angler.move_absolute(1, 200);
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(TOWER_HEIGHT) && !doublePressCheck){
        fBar.move_absolute(FBAR_TOP-50, 150);
        setfBarState(fBarStates::Top);
      }
      if(master.get_digital_new_press(DOWN_CUBE_HEIGHT)) {
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      break;
  }
}
