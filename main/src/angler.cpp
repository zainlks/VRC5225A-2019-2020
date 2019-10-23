#include "angler.hpp"

pros::Task *dropOffTask = nullptr;
anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;
int stateCheck = 0;
bool dropOffHold = false;
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
double kP = 0.001;
bool taskComplete = false;

void dropOff(void *param) {
  tracking.reset();
  printf("x is: %f, y is: %f\n", tracking.xcoord, tracking.ycoord);
  tracking.move_to_target(0, -10.0, 0, 40, false, true);
  setDriveState(driveStates::Driver);
}

void anglerHandle() {
  switch(anglerState) {
    case anglerStates::Idle:
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 100);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Top:
      if(master.get_digital(DROPOFF_BUTTON)) dropOffHold = true;
      if(dropOffHold)
      {
        if((ANGLER_TOP-angler.get_position())<1300 && (ANGLER_TOP-angler.get_position())>600)
        {
          intakeL.move(-30);
          intakeR.move(30);
        }
        if((ANGLER_TOP-angler.get_position())<599)
        {
          intakeL.move(-60);
          intakeR.move(60);
        }
      }
        if((ANGLER_TOP-angler.get_position())<25 && stateCheck == 0)
        {
          setDriveState(driveStates::Auto);
          tracking.reset();
          tracking.move_to_target(0, -10.0, 0, 50, false, false);
          setDriveState(driveStates::Driver);
          stateCheck++;
        }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Mid:
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DROPOFF_BUTTON)) {
        intakeL.tare_position();
        intakeL.move(70);
        intakeR.move(-70);
        setAnglerState(anglerStates::CubeOut);
      }
    break;
    case anglerStates::CubeOut:
    // printf("here\n");
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
