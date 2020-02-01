#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "controller.hpp"
#include "logging.hpp"
#include "menu.hpp"
#include "gui.hpp"
#include "autonomous.hpp"
uint32_t autotimer;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	fBarCal();
	anglerCal();
	// log_init();
	gui_init();
	menu_init();
	front_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	front_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	back_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	back_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	fBar.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	angler.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	updateStartTask();

	Task driveUpdate(driveHandle);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


void autonomous() {
	setDriveState(driveStates::Auto);
  updateStopTask();
  tracking.reset();
  updateStartTask();
  delay(1);
  while(resetDone == false) delay(1);
  // intakeL.move(127);
  green.sig_num = 1;
  orange.sig_num = 2;
  autotimer = pros::millis();
  log("global angle:%f",tracking.global_angle);
  switch(side) {
    case sides::blue:
      switch(cur_auto) {
        case auto1:
          blueProtect();
        break;
        case auto2:
          blue9();
        break;
        case auto3:
          blue10();
        break;
        case auto4:
          skills();
        break;
      }
    break;
    case sides::red:
      switch(cur_auto) {
        case auto1:
          redProtect();
        break;
        case auto2:
          red9();
        break;
        case auto3:
          red10();
        break;
        case auto4:
          skills();
        break;
      }
    break;

  }
  log("autotime is %d\n", autotimer-pros::millis());
  master.clear();
  delay(50);
  master.print(2,0,"%d",millis()-autotimer);
}


void opcontrol() {
	double start_x;
	double start_y;
	double start_a;
	double power = 0;
	double kP = 1.2;
	uint32_t stoptime = 0;
	uint32_t LTimer = millis();
	uint32_t nineCubeTime = 0;
	bool nineCubeSafety = false;
	bool nineCube = false;
	bool intk_stop = false;
	double fBar_height = 0;
	green.sig_num = 1;
	orange.sig_num = 2;
	bool intakeReverse = false;


	double cur_coord;
	int lastTime = 0;
	setDriveState(driveStates::Driver);
	master.clear();


	while (true){
		 anglerHandle();
		 fBarHandle();
		 gui_handle();
		 green.update();
		 log_graph(front_L.get_actual_velocity());

		if(nineCube && master.get_digital_new_press(INTK_IN_BUTTON)){
			nineCube = false;
			intakeOn();
			angler.move_absolute(1,200);
		}
			if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
				fBar.move_absolute(400, 200);
				while(fBar.get_position() < 395 ){delay(1);}
				delay(100);
				intakeL.move(-10);
				intakeR.move(10);
				fBar.move_absolute(1,200);
				setfBarState(fBarStates::Idle);
				delay(50);

			}
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
			 fBar_height += 150;
			 fBar.move_absolute(fBar_height, 80);
			 master.print(2,0, "Height is: %f", fBar_height);
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
				 while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)&& !master.get_digital_new_press(INTK_IN_BUTTON)&& !master.get_digital_new_press(INTK_OUT_BUTTON))delay(1);
				 intakeL.tare_position();
				 while(fabs(intakeL.get_position())<900 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10) && !master.get_digital_new_press(INTK_IN_BUTTON)&& !master.get_digital_new_press(INTK_OUT_BUTTON)) delay(1);
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
		if(intakeReverse && (fabs(tracking.ycoord)>3 || fabs(tracking.xcoord)>3)) {
			intakeL.move(-127);
			intakeR.move(127);
			intakeReverse = false;
		}
		 delay(1);


 }
}
