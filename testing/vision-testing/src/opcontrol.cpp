#include "main.h"
#include "vision.hpp"

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
void opcontrol()
{
	uint32_t timer = pros::millis();
		green.sig_num = 1;
		purple.sig_num = 2;
		drive_fl.move(30);
		drive_bl.move(30);
		drive_fr.move(-30);
		drive_br.move(-30);
		while(green.average_distance>30 || green.average_distance==0)
		{

			timer = pros::millis();

				while(pros::millis()-timer<20)
				{
					green.update();
				}


			printf("the green distance from the sensor is: %f\n", green.average_distance);
			printf("height being used was: %f\n", green.average_height);
			// printf("The top coord is:%d\n", green.ave);
			//green.reset();
		}
		drive_fl.move(-5);
		drive_bl.move(-5);
		drive_fr.move(5);
		drive_br.move(5);
	}
