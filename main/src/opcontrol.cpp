#include "main.h"
#include "tracking.hpp"
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
	  delay(6000);
	  Task tracking_task(update);

	  while (true){

	     tracking.power_a = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
	     tracking.power_x = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
	     tracking.power_y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

	     if (fabs(tracking.power_a) < 5){
	       tracking.power_a = 0;
	     }
	     if (fabs(tracking.power_x) < 5){
	       tracking.power_x = 0;
	     }
	     if (fabs(tracking.power_y) < 5){
	       tracking.power_y = 0;
	     }

	     move_drive(tracking.power_x, tracking.power_y, tracking.power_a);

	     if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
	       tracking.x2 = tracking.xcoord;
	       tracking.y2 = tracking.ycoord;
	       tracking.a2 = tracking.global_angle;
	     }
	     if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
	       tracking.xcoord = 0;
	       tracking.ycoord = 0;
	       tracking.global_angle = 0;
	     }

			 if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
	       tracking.move_to_target(tracking.x2, tracking.y2, tracking.a2);
			 }

	     if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
	       tracking.move_to_target(-13.0, 0.0, 0.0);
	       delay(500);
	       tracking.move_to_target(-13.0, 60.0, 0.0);
	       tracking.move_to_target(-13.0, 80.0, M_PI/2);
	       delay(500);
	       tracking.move_to_target(6.0, 80.0, M_PI/2);
	       delay(500);
	       tracking.move_to_target(6.0, 80.0, M_PI);
	       delay(500);
	       tracking.move_to_target(-13.0, 80.0, M_PI);
	       delay(500);
	       tracking.move_to_target(0.0, 0.0, M_PI);
	       delay(1000);
	     }

	  }
	}
