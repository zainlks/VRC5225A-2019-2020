#include "angler.hpp"

anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;

void setAnglerState(anglerStates state) {
  printf("Going from %d", anglerState);
	anglerStateLast = anglerState;
	anglerState = state;
	anglerStateChangeTime = pros::millis();
  printf(" to %d\n", anglerState);
}

void anglerCal()
{
  uint32_t timeout_time = millis() + 100;
  bool success = true;
  angler.move(-25);
  delay(100);
  while (fabs(angler.get_actual_velocity()) < 12 && (success = (millis() < timeout_time)))
  {
    delay(10);
  }
  timeout_time = millis() + 3500;
  while (fabs(angler.get_actual_velocity()) > 10 && (success = (millis() < timeout_time)))
	{
		delay(10);
	}
  delay(100);
  angler.tare_position();
  angler.move(0);
  setAnglerState(anglerStates::Idle);
}

void anglerHandle() {
  switch(anglerState) {
    case anglerStates::Idle:
      if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
      if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Top:
      if((angler.get_target_position()-angler.get_position())<300){
        intakeL.move(0);
        intakeR.move(0);
      }
      if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Mid:
      if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
    break;
    case anglerStates::CubeOut:
        if(fabs(intakeL.get_position())>1000)
        {
          intakeL.move(0);
          intakeR.move(0);
          angler.move_absolute(ANGLER_TOP, 100);
          setAnglerState(anglerStates::Top);
        }
    break;
  }
}
