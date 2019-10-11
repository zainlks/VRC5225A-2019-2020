#include "fBar.hpp"

fBarStates fBarState = fBarStates::Idle;
fBarStates fBarStateLast = fBarState;
int fBarStateChangeTime = 0;

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
  fBar.move(-12);
  setfBarState(fBarStates::Idle);
}

void fBarHandle() {
  switch(fBarState) {
    case fBarStates::Idle:
      if(master.get_digital(E_CONTROLLER_DIGITAL_X)) {
        fBar.move_absolute(FBAR_TOP, 200);
        setfBarState(fBarStates::Top);
      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
        fBar.move_absolute(FBAR_MID, 200);
        setfBarState(fBarStates::Mid);
      }
    case fBarStates::Top:
      if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
        fBar.move_absolute(FBAR_MID, 200);
        setfBarState(fBarStates::Mid);
      }
    case fBarStates::Mid:
      if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
        fBar.move_absolute(FBAR_TOP, 200);
        setfBarState(fBarStates::Top);
      }
      break;
  }
}
