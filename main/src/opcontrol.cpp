#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "controller.hpp"
using namespace pros;
int startNum = 0;

void intk_break(int maxVel){
	double errorL, errorR, integralL, integralR, powerL, powerR;
	double kP = 0.1;
	uint32_t lastTime = millis();

	while(true){
		lastTime = millis();
		errorL = -1 * intakeL.get_actual_velocity();
		errorR = -1 * intakeR.get_actual_velocity();
		integralL = errorL * (millis() - lastTime);
		integralR = errorR * (millis() - lastTime);
		powerL = errorL * kP;
		powerR = errorR * kP;


		if(powerL > maxVel) powerL = maxVel * -sgn(intakeL.get_actual_velocity());
		if(powerR > maxVel) powerR = maxVel * -sgn(intakeR.get_actual_velocity());

		intakeL.move_velocity(powerL);
		intakeR.move_velocity(powerR);


		if (abs(intakeL.get_actual_velocity()) < 5 && abs(intakeR.get_actual_velocity()) < 5)break;
	}
}
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
		purple.sig_num = 2;
		//tracking.setAngleHold(0);
		int lastTime = 0;
		printf("done\n");
		//angler.move_absolute(1800, 100);
	  while (true){

			 //if(startNum == 0 && angler.get_position()>1750) {anglerCal(); startNum++;}
			 printf("angler: %f\n", angler.get_position());
			 //anglerHandle();
			 //fBarHandle();
			//  for(int x = 0; x < 50; x++){
			//  	intakeL.move_velocity(-x);
			// 	intakeR.move_velocity(x);
			// 	printf("%d \n", x);
			// 	delay(500);
			// }
			 if(millis() - stoptime >= 500 && intk_stop){
				 // intakeL.move_relative(0,50);
				 // intakeR.move_relative(0,50);
				 intakeL.move(-5);
				 intakeR.move(5);
				 //intk_break(50);
				 intk_stop = false;
			 }
			 if(master.get_digital_new_press(INTK_IN_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>10)
				 {
					 intakeR.move(25);
					 intakeL.move(-25);
					 stoptime = millis();
					 intk_stop = true;
				 }
				 else {
					 intakeL.move(-127);
					 intakeR.move(127);
				 }
			 }
			 if(master.get_digital_new_press(INTK_OUT_BUTTON)) {
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


			 // tracking.move_to_target(0, 10, 0);
			 // green.update();
			 // printf("center: %d\n",green.obj.x_middle_coord);
			 // printf("global angle: %f\n", tracking.global_angle);
	     // green.lineMiddle(1.2);
			 // printf("L:%d R:%d G:%f\n",leftencoder.get_value(),rightencoder.get_value(),tracking.global_angle);

			 delay(1);
	   }
	}
