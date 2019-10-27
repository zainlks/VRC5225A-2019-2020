#include "angler.hpp"

pros::Task *dropOffTask = nullptr;
anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;
int stateCheck = 0;
uint32_t timer = 0;
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
  // angler.move(-15);
  // delay(100);
  // while (fabs(angler.get_actual_velocity()) < 12 && (success = (millis() < timeout_time))){
  //   delay(10);
  // }
  // timeout_time = millis() + 3500;
  // while (fabs(angler.get_actual_velocity()) > 10 && (success = (millis() < timeout_time))){
	// 	delay(10);
	// }
  // delay(100);
  //angler.move_absolute(,);
  angler.move(-15);
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
        angler.move_absolute(ANGLER_MID, 50);
        intakeL.move_relative(0,50);
        intakeR.move_relative(0,50);
        setAnglerState(anglerStates::Mid);
      }
      // if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
      //   angler.move_absolute(750, 200);
      //   setAnglerState(anglerStates::Push);
      // }
    break;
    case anglerStates::Push:
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
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
          intakeL.move(-40);
          intakeR.move(40);
        }
      }
        if((ANGLER_TOP-angler.get_position())<25 && stateCheck == 0)
        {
          fBar.move_absolute(FBAR_MID, 75);
          if(fabs(fBar.get_position()-FBAR_MID)<10 && stateCheck == 0)
          {
            setDriveState(driveStates::Auto);
            tracking.reset();
            tracking.move_to_target(0, -10.0, 0, false, 50, false, false);
            setDriveState(driveStates::Driver);
            stateCheck++;
          }
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
      if(master.get_digital_new_press(DROPOFF_BUTTON) || doublePressCheck) {
        doublePressCheck = true;
        printf("i am doing this \n");
        if(timer == 0) timer = pros::millis();
        if((pros::millis()-timer)>200)
        {
          if(master.get_digital(TOWER_HEIGHT))
          {
            intakeL.move(30);
            intakeR.move(-30);
            intakeL.tare_position();
            timer = 0;
            setAnglerState(anglerStates::CubeOutLast);
          }
          else
          {
            intakeL.tare_position();
            intakeL.move(30);
            intakeR.move(-30);
            doublePressCheck = false;
            timer = 0;
            setAnglerState(anglerStates::CubeOutFirst);
          }
        }
      }
    break;
    case anglerStates::CubeOutLast:
      if(fabs(intakeL.get_position())>600)
      {
        intakeL.move_relative(0,50);
        intakeR.move_relative(0,50);
        doublePressCheck = false;
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::CubeOutFirst:
    // printf("here\n");
        delay(50);
        if(fabs(intakeL.get_actual_velocity())<5 || fabs(intakeR.get_actual_velocity())<5)
        {
          intakeL.move(-25);
          intakeR.move(25);
          angler.move_absolute(ANGLER_TOP, 150);
          stateCheck = 0;
          setAnglerState(anglerStates::Top);
        }
        if(fabs(intakeL.get_position())>800)
        {
          intakeL.move(-25);
          intakeR.move(25);
          angler.move_absolute(ANGLER_TOP, 150);
          stateCheck = 0;
          setAnglerState(anglerStates::Top);
        }
    break;
  }
}
