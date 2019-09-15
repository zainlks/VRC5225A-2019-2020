#include "main.h"
#include "config.hpp"
using namespace pros;
#include <iostream>
#include <cmath>

typedef enum _IntakeState {
	intakeIn,
	intakeOut,
	intakeStopped,
	intakeJammed
} IntakeState;


 void intake(int speed){
	 if (speed != 0){
		 intake_L.move(speed);
		 intake_R.move(-1 * speed);
	 }
	 else{
		 intake_L.move(speed);
		 intake_R.move(speed);
	 }

 }


void opcontrol() {
	bool toggle_R2 = false, toggle_R1 = false, jammed = false;;
	IntakeState intk_state = intakeStopped;
	double intk_min_velocity = 55.0;
	unsigned long btn_start_time = 0, jammed_time = 0, fix_length = 500;
	while(true){
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
			toggle_R2 = true;
		}
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
			toggle_R1 = true;
		}


		if (toggle_R2 && intk_state != intakeIn){
			intake(127);
			printf("pushed");
			btn_start_time = millis();
			intk_state = intakeIn;
			toggle_R2 = false;
		}
		else if (toggle_R2 && intk_state == intakeIn ){
			intake(0);
			printf("off");
			intk_state = intakeStopped;
			toggle_R2 = false;
		}

		if (toggle_R1 && intk_state != intakeOut){
			intake(-127);
			printf("pushed");
			btn_start_time = millis();
			intk_state = intakeOut;
			toggle_R1 = false;
		}
		else if (toggle_R1 && intk_state == intakeOut ){
			intake(0);
			printf("off");
			intk_state = intakeStopped;
			toggle_R1 = false;
		}
		if(intk_state == intakeIn || intk_state == intakeJammed){

			printf("%d | L = %f      R = %f \n", millis(), intake_L.get_actual_velocity(), intake_R.get_actual_velocity());
		}
		if(intk_state == intakeIn && (millis() - btn_start_time) > 100){
			if (intake_L.get_actual_velocity() < intk_min_velocity || intake_R.get_actual_velocity() > (-1* intk_min_velocity)){
				//stop motors                   go back for 1/2 seconds
				intake(-20);
				intk_state = intakeJammed;
				jammed_time = millis();
			}
		}
		if(intk_state == intakeJammed && (millis() - jammed_time) > fix_length){
			toggle_R2 = true;
			intake(0);
			intk_state = intakeStopped;
		}
	}
}
