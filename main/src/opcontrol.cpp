#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
using namespace pros;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	  front_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  front_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  back_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  back_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
		double power = 0;
		double kP = 1.2;
	  delay(6000);
		green.sig_num = 1;
		purple.sig_num = 2;
	  Task tracking_task(update);
		tracking.setAngleHold(0);
		int lastTime = 0;
	  while (true){
			 fBarHandle();
			 anglerHandle();
			 driveHandle();
			 if(master.get_digital_new_press(INTK_IN_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>2)
				 {
					 intakeL.move(0);
					 intakeR.move(0);
				 }
				 else {
					 intakeL.move(-127);
					 intakeR.move(127);
				 }
			 }
			 if(master.get_digital_new_press(INTK_OUT_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>2)
				 {
					 intakeL.move(0);
					 intakeR.move(0);
				 }
				 else
				 {
					 intakeL.move(127);
					 intakeR.move(-127);
			 	 }
			 }
			 // tracking.move_to_target(0, 10, 0);
			 // green.update();
			 // printf("center: %d\n",green.obj.x_middle_coord);
			 // printf("global angle: %f\n", tracking.global_angle);
	     // green.lineMiddle(1.2);
			 // printf("L:%d R:%d G:%f\n",leftencoder.get_value(),rightencoder.get_value(),tracking.global_angle);


	   }
	}
