#include "main.h"
#include "fBar.hpp"
#include "angler.hpp"
#include "controller.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	Task controllerUpdate(printTemp);
	//fBarCal();
	//anglerCal();
	// front_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	// front_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	// back_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	// back_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	// delay(6000);
	Task tracking_task(update);

	//Task driveUpdate(driveHandle);
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
