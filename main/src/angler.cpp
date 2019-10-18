#include "angler.hpp"

pros::Task *dropOffTask = nullptr;
anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;
int stateCheck = 0;

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
  angler.move(-10);
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
double kP = 0.001;
bool taskComplete = false;

void startDropOff() {
  dropOffTask = new Task(dropOff);
}
void stopDropOff() {
  dropOffTask->remove();
  delete dropOffTask;
  dropOffTask = nullptr;
}
void dropOff(void *param) {
  tracking.reset();
  printf("x is: %f, y is: %f\n", tracking.xcoord, tracking.ycoord);
  tracking.move_to_target(0, 3.0, 0);
  setDriveState(driveStates::Driver);
  stopDropOff();
}

void anglerHandle() {
  switch(anglerState) {
    case anglerStates::Idle:
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        angler.move_absolute(ANGLER_FIRST, 200);
        setAnglerState(anglerStates::First);
      }
    break;
    case anglerStates::First:
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        angler.move_absolute(ANGLER_FIRST, 200);
        setAnglerState(anglerStates::Mid);
      }
    case anglerStates::Top:
      if((ANGLER_TOP-angler.get_position())<1300 && (ANGLER_TOP-angler.get_position())<600)
      {
        intakeL.move(-30);
        intakeR.move(30);
      }
      if((ANGLER_TOP-angler.get_position())<599)
      {
        intakeL.move(-60);
        intakeR.move(60);
      }
      if((ANGLER_TOP-angler.get_position())<25 && stateCheck == 0)
      {
        startDropOff();
        setDriveState(driveStates::Auto);
        stateCheck++;
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        angler.move_absolute(ANGLER_FIRST, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Mid:
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        angler.move_absolute(ANGLER_FIRST, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::CubeOut:
        if(fabs(intakeL.get_position())>800)
        {
          intakeL.move(0);
          intakeR.move(0);
          angler.move_absolute(ANGLER_TOP, 75);
          stateCheck = 0;
          setAnglerState(anglerStates::Top);
        }
    break;
  }
}
