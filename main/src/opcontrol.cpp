#include "main.h"
using namespace pros;

void opcontrol() {
		Motor front_L(20, false);
		Motor front_R(12, true);
		Motor back_L(10, false);
		Motor back_R(1, true);
		Controller master(E_CONTROLLER_MASTER);
		int power_x = 0;
		int power_y = 0;
		int power_a = 0;
	  while (true){
			power_x = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
			power_y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			power_a = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

			if (abs(power_x) < 5){
				power_x = 0;
			}
			if (abs(power_y) < 5){
				power_y = 0;
			}
			if (abs(power_a) < 5){
				power_a = 0;
			}

			front_L.move(power_x + power_y + power_a);
			front_R.move(-power_x + power_y - power_a);
			back_L.move(power_x + power_y - power_a);
			back_R.move(-power_x + power_y + power_a);
	   }
}
