
#include "menu.hpp"
using namespace pros;

bool auto_set;
autos cur_auto;
sides side;
screens pages;
bool side_select;

void autos_page(){
  if(!auto_set){
    if (side_select){
      switch(side){
        case sides::red:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            side_select = false;
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
            side = sides::blue;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            side = sides::blue;
            menu_update();
          }
        break;
        case sides::blue:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            side_select = false;
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            side = sides::red;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
            side = sides::red;
            menu_update();
          }
        break;
      }
    }
    else{
      switch(cur_auto){
        case autos::auto1:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            cur_auto  = autos::auto2;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
            cur_auto  = autos::auto3;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            auto_set = true;
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) side_select = true;
        break;
        case autos::auto2:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            cur_auto  = autos::auto3;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
            cur_auto  = autos::auto1;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            auto_set = true;
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) side_select = true;
        break;
        case autos::auto3:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            cur_auto  = autos::auto1;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
            cur_auto  = autos::auto2;
            menu_update();
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
              auto_set = true;
          }
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) side_select = true;
        break;
      }
    }
  }
}

void menu_update(){
  switch(pages){
    case screens::motor_temps:

    break;
    case screens::autos:
      master.print(0, 0,"side: %s    ",side_colour[(int)side]);
      delay(50);
      master.print(1,0,"auto: %s      ",auto_names[(int)cur_auto]);
    break;
  }
}


void menu(){
  side = sides::red;
  side_select = true;
  auto_set = false;
  cur_auto = autos::auto1;
  pages = screens::autos;
  menu_update();
  while(true){
    delay(10);
    autos_page();
  }
}
