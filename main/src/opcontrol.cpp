#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "controller.hpp"
using namespace pros;
int startNum = 0;
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
		double power = 0;
		double kP = 1.2;
		green.sig_num = 1;
		purple.sig_num = 2;
		tracking.setAngleHold(0);
		int lastTime = 0;
		printf("done\n");
		angler.move_absolute(1800, 100);
	  while (true){
			 if(startNum == 0 && angler.get_position()>1750) {anglerCal(); startNum++;}
			 printf("angler: %f\n", angler.get_position());
			 anglerHandle();
			 fBarHandle();
			 driveHandle();
			 if(master.get_digital_new_press(INTK_IN_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>10)
				 {
					 intakeL.move_relative(0,50);
           intakeR.move_relative(0,50);
				 }
				 else {
					 intakeL.move(-127);
					 intakeR.move(127);
				 }
			 }
			 if(master.get_digital_new_press(INTK_OUT_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>10)
				 {
					 intakeL.move_relative(0,50);
           intakeR.move_relative(0,50);
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
