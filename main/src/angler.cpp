#include "angler.hpp"

pros::Task *dropOffTask = nullptr;
anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;
int stateCheck = 0;
uint32_t timer = 0;
bool dropOffHold = false;
void setAnglerState(anglerStates state) {
  log("Going from %d", anglerState);
	anglerStateLast = anglerState;
	anglerState = state;
	anglerStateChangeTime = pros::millis();
  log(" to %d\n", anglerState);
}
void intakeOn(){
  intakeL.move(-127);
  intakeR.move(127);
}
void anglerCal()
{
  uint32_t timeout_time = millis() + 1500;
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
  angler.move(-10);
  delay(100);
  while (fabs(angler.get_actual_velocity()) < 19 && (success = (millis() < timeout_time)))
  {
    delay(10);
  }
  //timeout_time = millis() + 3500;
  while (fabs(angler.get_actual_velocity()) > 16)
	{
		delay(10);

	}
  delay(100);
  angler.move(0);
  delay(100);
  angler.tare_position();
  setAnglerState(anglerStates::Idle);
}
double kP = 0.001;
bool taskComplete = false;

void dropOff(void *param) {
  tracking.reset();
  log("x is: %f, y is: %f\n", tracking.xcoord, tracking.ycoord);
  move_to_target_sync(0, -10.0, 0, 40, false, true);
  setDriveState(driveStates::Driver);
}

void anglerHandle() {
  switch(anglerState) {
    case anglerStates::Idle:
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 100);
        intakeR.move(15);
        intakeL.move(-15);
        setAnglerState(anglerStates::Push);
      }
      // if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
      //   angler.move_absolute(750, 200);
      //   setAnglerState(anglerStates::Push);
      // }
    break;
    case anglerStates::Push:
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 100);
        intakeR.move(-25);
        intakeL.move(25);
        delay(50);
        setAnglerState(anglerStates::Mid);
      }
      if(master.get_digital_new_press(ANGLER_DOWN)){
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
        if((ANGLER_TOP-angler.get_position())<5 && stateCheck == 0)
        {
            setDriveState(driveStates::Auto);
            log("hello");
            updateStopTask();
            log("hey there shordy");
            tracking.reset();
            updateStartTask();
            log("%d | global angle: %d, xcoord: %d, ycoord: %d", pros::millis(), tracking.global_angle, tracking.xcoord, tracking.ycoord);
            move_to_target_sync(0, -10.0, 0, false, 50, false, false);
            setDriveState(driveStates::Driver);
            log("done back");
            stateCheck++;
        }
      if(master.get_digital_new_press(ANGLER_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Mid:
      if((fabs(intakeL.get_actual_velocity())<20 || fabs(intakeR.get_actual_velocity())<20) && anglerStateLast == anglerStates::Push)
      {
        intakeL.move(0);
        intakeR.move(0);
      }
      if(master.get_digital_new_press(ANGLER_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DROPOFF_BUTTON) || doublePressCheck) {
        doublePressCheck = true;
        if(timer == 0) timer = pros::millis();
        if((pros::millis()-timer)>200)
        {
          if(master.get_digital(TOWER_HEIGHT))
          {
            intakeL.move_velocity(20);
            intakeR.move_velocity(-20);
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
      if(fabs(intakeL.get_position())>225)
      {
        intakeL.move(-10);
        intakeR.move(10);
        doublePressCheck = false;
        setAnglerState(anglerStates::Mid);
      }
      if(master.get_digital_new_press(ANGLER_DOWN)){
        angler.move_absolute(1, 200);
        setAnglerState(anglerStates::Idle);
      }
    break;
    case anglerStates::CubeOutFirst:
    // printf("here\n");
        delay(50);
        if(fabs(intakeL.get_actual_velocity())<20 || fabs(intakeR.get_actual_velocity())<20)
        {
          // intakeL.move_relative(0,100);
          // intakeR.move_relative(0,100);
          intakeL.move(7 * intakeL.get_direction());
          intakeR.move(7 * intakeR.get_direction());
          //intakeL.move(5)
          angler.move_absolute(ANGLER_TOP, 75);
          stateCheck = 0;
          setAnglerState(anglerStates::Top);
        }
        if(fabs(intakeL.get_position())>800)
        {
          intakeL.move(7 * intakeL.get_direction());
          intakeR.move(7 * intakeR.get_direction());
          angler.move_absolute(ANGLER_TOP, 75);
          stateCheck = 0;
          setAnglerState(anglerStates::Top);
        }
        if(master.get_digital_new_press(ANGLER_DOWN)){
          angler.move_absolute(1, 200);
          setAnglerState(anglerStates::Idle);
        }
    break;
  }
}
