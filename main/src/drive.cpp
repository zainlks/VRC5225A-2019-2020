#include "drive.hpp"

driveStates driveState = driveStates::Driver;
driveStates driveStateLast = driveState;
int driveStateChangeTime = 0;

void setDriveState(driveStates state) {
  printf("Going from %d", driveState);
	driveStateLast = driveState;
	driveState = state;
	driveStateChangeTime = pros::millis();
  printf(" to %d\n", driveState);
}

void driveHandle() {
  switch(driveState) {
    case driveStates::Driver:
      tracking.trackingInput();
      break;
    case driveStates::Auto:
    break;
  }
}