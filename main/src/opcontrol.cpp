#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "controller.hpp"
#include "logging.hpp"
#include "menu.hpp"
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
		uint32_t stoptime = 0;
		uint32_t LTimer = millis();
		bool intk_stop = false;
		green.sig_num = 1;
		orange.sig_num = 2;
		bool intakeReverse = false;
		double cur_coord;
		//tracking.setAngleHold(0);
		int lastTime = 0;
		setDriveState(driveStates::Driver);
		// Task driveUpdate(driveHandle);
		//angler.move_absolute(1800, 100);
	  while (true){
			 //if(startNum == 0 && angler.get_position()>1750) {anglerCal(); startNum++;}
			 //printf("angler: %f\n", angler.get_position());
			 // printf("L: %f, R: %f\n", tracking.velocityL, tracking.velocityR);

			 // printf("global angle is: %f\n",rad_to_deg(tracking.global_angle));
			 anglerHandle();
			 fBarHandle();
			 green.update();
			 // printf("%d | %d\n",green.obj.height, green.obj.width);
			 // printf("%d | %d | %d\n", leftencoder.get_value(), rightencoder.get_value(), backencoder.get_value());

			 // printf("left%d right %d\n", leftLs.get_value(), rightLs.get_value());
			//  for(int x = 0; x < 50; x++){
			//  	intakeL.move_velocity(-x);
			// 	intakeR.move_velocity(x);
			// 	printf("%d \n", x);
			// 	delay(500);
			// }

				if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
					fBar.move_absolute(300, 200);
				  while(fBar.get_position() < 295 ){delay(1);}
				  delay(100);
				  intakeL.move(-10);
				  intakeR.move(10);
				  fBar.move_absolute(1,200);
				  delay(50);
				}
			if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) menu();
			 if(master.get_digital_new_press(SPEED_LIMIT))
			 {
				 if(speedLimit)speedLimit = false;
				 else speedLimit = true;
			 }
			 if(master.get_digital_new_press(INTK_IN_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>25)
				 {
					 intakeR.move(8);
					 intakeL.move(-8);
				 }
				 else {
					 intakeL.move(-127);
					 intakeR.move(127);
				 }
			 }
			 if(master.get_digital_new_press(INTK_OUT_BUTTON)) {
				 if(fBar.get_position()>200)
				 {
					 intakeL.move(127);
					 intakeR.move(-127);
					 while(rightLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
					 intakeL.tare_position();
					 while(fabs(intakeL.get_position())<650 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
					 intakeL.move(-8);
					 intakeR.move(8);
					 intakeReverse = true;
					 updateStopTask();
					 tracking.reset();
				   updateStartTask(true);
				 }
				 else {
					 if(fabs(intakeL.get_actual_velocity())>10)
					 {
						 intakeL.move(-5);
							intakeR.move(5);
					 }
					 else
					 {
						 intakeL.move(127);
						 intakeR.move(-127);
					 }
				 }
			 }
			 if(intakeReverse && fabs(tracking.ycoord)>3) {
				 intakeL.move(-127);
				 intakeR.move(127);
				 intakeReverse = false;
			 }

			 // tracking.move_to_target(0, 10, 0);
			 // green.update();
			 // printf("center: %d\n",green.obj.x_middle_coord);
			 // printf("global angle: %f\n", tracking.global_angle);
	     // green.lineMiddle(1.2);
			  //printf("L:%d R:%d G:%d\n",leftencoder.get_value(),rightencoder.get_value(),backencoder.get_value());

			 delay(1);
	   }
		//menu();
}
