#include "angler_move.hpp"


void angler_move(double degrees, int move_power) {
  while(true){
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
        angler.move_absolute(degrees, 200);
        intakeR.move(-25);
        intakeL.move(25);
    }
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
      front_L.move(move_power);
      back_R.move(move_power);
      front_R.move(move_power);
      back_L.move(move_power);
    }
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
      front_L.move(0);
      back_R.move(0);
      front_R.move(0);
      back_L.move(0);
      intakeR.move(-45);
      intakeL.move(45);
    }
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
        intakeR.move(-55);
        intakeL.move(55);
    }
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
      angler.move_absolute(7500, 100);
      while(angler.get_position() > 5700){
        intakeR.move(-25);
        intakeL.move(25);
      }
      if (angler.get_position() >= 7450) {
        intakeR.move(40);
        intakeL.move(-40);
      }
    }
  }
}
