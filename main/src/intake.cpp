#include "intake.hpp"

void intake(int speed){
  intake_L.move(speed);
  intake_R.move(-1 * speed);
}


void intk_ctrl(IntakeState state){
  switch (state){
    case intakeIn:
      intake(127);
      printf("intake in");
      break;
    case intakeOut:
      intake(-127);
      printf("intake out");
      break;
    case intakeStopped:
      intake(0);
      printf("intake stopped");
      break;
    case intakeJammed:
      intake(-20);
      jammed_time = millis();
      printf("intake jammed");
      break;
    default:
      printf("error");
    }
}

void intk (void* param){
  bool toggle_R2 = false, toggle_R1 = false, jammed = false;;
  intk_state = intakeStopped;
  IntakeState lst_intk_state = intakeStopped;
  double intk_min_velocity = 100.0; //this number will have to be checked with intake log, see min velocity when not jammed
  unsigned long btn_start_time = 0,fix_length = 500;
  jammed_time = 0;
  while(true){
    intk_ctrl(intk_state);
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
      toggle_R2 = true;
    }
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
      toggle_R1 = true;
    }
    if (toggle_R2){
      if (intk_state != intakeIn){
        btn_start_time = millis();
        intk_state = intakeIn;
      }
      else{intk_state = intakeStopped;}
      toggle_R2 = false;
    }


    if (toggle_R1){
      if (intk_state != intakeOut){
        btn_start_time = millis();
        intk_state = intakeOut;
      }
      else {intk_state = intakeStopped;}
      toggle_R1 = false;
    }

    if(intk_state == intakeIn && (millis() - btn_start_time) > 100){
      if (intake_L.get_actual_velocity() < intk_min_velocity || intake_R.get_actual_velocity() > (-1* intk_min_velocity)){
        intk_state = intakeJammed;
      }
    }
    if(intk_state == intakeJammed && (millis() - jammed_time) > fix_length){
      intk_state = intakeIn;
    }
    delay(2);
  }
}
