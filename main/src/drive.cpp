#include "drive.hpp"

driveStates driveState = driveStates::Driver;
driveStates driveStateLast = driveState;
int driveStateChangeTime = 0;

void setDriveState(driveStates state) {
  printf("Going from %d", driveState);
	driveStateLast = driveState;
	driveState = state;
	driveStateChangeTime = pros::millis();
  log(" to %d\n", driveState);
}

void driveHandle(void *param) {
  while(true){
    switch(driveState) {
      case driveStates::Driver:
        tracking.trackingInput();
        break;
      case driveStates::Auto:
      break;
    }
    delay(1);
  }
}
