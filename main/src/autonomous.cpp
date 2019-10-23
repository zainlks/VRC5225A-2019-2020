#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
using namespace pros;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  tracking.reset();
  // printf("global angle:%f",tracking.global_angle);
  delay(1000);

  tracking.move_to_target(16, 15, -M_PI/4);
  tracking.flattenAgainstWall(true, true);
  move_drive(-25, 25, 0);
  double error;
  int target;
  while(true){
    error = target - ultrasonic.get_value();
    if(error > 335 && error < 355){
      brake();
      delay(300);
      move_drive(0, 0, 0);
      break;
    }
  }

}
