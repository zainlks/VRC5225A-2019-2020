#include "angler.hpp"
Angler angler(4,false);
pros::Task *dropOffTask = nullptr;
anglerStates anglerState = anglerStates::Idle;
anglerStates anglerStateLast = anglerState;
int anglerStateChangeTime = 0;
int stateCheck = 0;
uint32_t timer = 0;
bool dropOffHold = false;
uint32_t shitTimer = pros::millis();

double Angler::getTarget() {
  return this->target;
}
int32_t Angler::move_absolute(double target, int32_t velocity ) {
  this->target = target;
  this->velocityCap = velocity;
  return 0;
}
int32_t Angler::getMaxVelocity() {
  return this->velocityCap;
}

void anglerMovement(void *param) {
  double kP = 0.1;
  double kI = 0.005;
  double error;
  double integral = 0;
  uint32_t lastTime = millis();
  while(true) {
    if(fabs(angler.getTarget()-angler.get_position())<75) {
      if(angler.getTarget()-angler.get_position()>35) angler.move(25);
      else angler.move(0);
    }
    else {
      error = angler.getTarget() - angler.get_position();
      if(fabs(error)<1400) kP = 0.28;
      else if(fabs(error)<800) kP = 0.07;
      else kP = 0.1;
      if(fabs(error) <= 150) {
        integral += error * (millis()-lastTime);
      }
      else integral = 0;

      angler.speed = ((error*kP + integral*kI)*angler.getMaxVelocity()/200)/angler.getMaxVelocity()*127;
      angler.move(angler.speed);
      printf("speed is:%f error is: %f integral is: %f\n",angler.speed, error, integral);
      log_graph(0,angler.speed,error,integral);
    }
    lastTime = millis();
    delay(1);
  }
}

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

void intakeReverse() {
  intakeL.move(70);
  intakeR.move(-70);
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
      if(angler.get_position()<65) angler.move(-10);
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        printf("start| %d", millis());
        angler.move_absolute(ANGLER_MID, 145);
        fBar.move_absolute(780,100);
        intakeR.move(40);
        intakeL.move(-40);
        while (angler.get_position() < ANGLER_MID -50)delay(1);
        setfBarState(fBarStates::Mid);
        printf("end| %d", millis());
        setAnglerState(anglerStates::Push);
      }
      if(topLs.get_value() < 500 && bottomLs.get_value() < 2500) {
        intakeR.move(15);
				intakeL.move(-15);
				angler.move_absolute(3500, 200);
        setAnglerState(anglerStates::DriveAround);
      }
      if(master.get_digital_new_press(DOWN_CUBE_HEIGHT)) {
        angler.move(127);
        fBar.move_absolute(650,100);
        intakeR.move(-35);
				intakeL.move(35);
        setfBarState(fBarStates::Top);
        setAnglerState(anglerStates::Top);
      }
      // if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
      //   angler.move_absolute(750, 200);
      //   setAnglerState(anglerStates::Push);
      // }
    break;
    case anglerStates::DriveAround:
    if(master.get_digital_new_press(DROPOFF_BUTTON)){
      printf("start| %d", millis());
      fBar.move_absolute(550,100);
      angler.move_absolute(ANGLER_MID, 145);
      intakeR.move(30);
      intakeL.move(-30);
      while (angler.get_position() < ANGLER_MID -50)delay(1);
      setfBarState(fBarStates::Mid);
      printf("end| %d", millis());
      setAnglerState(anglerStates::Push);
    }
    if(master.get_digital_new_press(ANGLER_DOWN)){
      angler.move_absolute(1, 200);
      setAnglerState(anglerStates::Idle);
    }
    break;
    case anglerStates::Push:
      if(fBar.get_position()>650  && fBar.get_position() < 750) fBar.move(30);
      if(fBar.get_position()>750) fBar.move(0);
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID+200, 100);
        intakeR.move(-35);
        intakeL.move(35);
        delay(60);
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
      if(fabs(ANGLER_TOP-angler.get_position())<600) angler.move_absolute(ANGLER_TOP,75);
        if((ANGLER_TOP-angler.get_position())<5 && stateCheck == 0 && anglerStateLast!=anglerStates::Idle)
        {
          printf("time is:%d", millis() - shitTimer);
            setDriveState(driveStates::Auto);
            updateStopTask();
            tracking.reset();
            updateStartTask();
            log("%d | global angle: %d, xcoord: %d, ycoord: %d", pros::millis(), tracking.global_angle, tracking.xcoord, tracking.ycoord);

            move_to_target_sync(0, -10.0, 0, false, 80, false, false, true);
           setDriveState(driveStates::Driver);
            // angler.move_absolute(1,200);
            log("done back");
            stateCheck++;
        }
      if(master.get_digital_new_press(ANGLER_DOWN)){
        angler.move_absolute(1,200);
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DOWN_CUBE_HEIGHT)){
        angler.move(-127);
        fBar.move_absolute(1, 200);
        setfBarState(fBarStates::Idle);
        setAnglerState(anglerStates::Idle);
      }
      if(master.get_digital_new_press(DROPOFF_BUTTON)){
        angler.move_absolute(ANGLER_MID, 200);
        setAnglerState(anglerStates::Mid);
      }
    break;
    case anglerStates::Mid:
    if(fBar.get_target_position()<1000){
      if(fBar.get_position()>650  && fBar.get_position() < 750) fBar.move(30);
      if(fBar.get_position()>750) fBar.move(0);
    }
      if((fabs(intakeL.get_actual_velocity())<5 || fabs(intakeR.get_actual_velocity())<5) && anglerStateLast == anglerStates::Push)
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
          shitTimer = pros::millis();
          printf("start angle, %d", millis());
          angler.move_absolute(ANGLER_TOP, 160);
          fBar.move(10);
          stateCheck = 0;
          while (angler.get_position() < ANGLER_MID -50)delay(1);
          printf("end| %d", millis());
          setAnglerState(anglerStates::BetweenTop);
        }
        if(fabs(intakeL.get_position())>800)
        {
          intakeL.move(7 * intakeL.get_direction());
          intakeR.move(7 * intakeR.get_direction());
          shitTimer = pros::millis();
          angler.move_absolute(ANGLER_TOP, 200);
          stateCheck = 0;
          setAnglerState(anglerStates::BetweenTop);
        }
        if(master.get_digital_new_press(ANGLER_DOWN)){
          angler.move_absolute(1, 200);
          setAnglerState(anglerStates::Idle);
        }
    break;
    case anglerStates::BetweenTop:
      if(angler.get_position()>ANGLER_TOP-800)
      {
        angler.move_absolute(ANGLER_TOP, 75);
        setAnglerState(anglerStates::Top);
      }
    break;
  }
}
