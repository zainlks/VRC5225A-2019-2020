
#include "menu.hpp"
#include "stdio.h"
using namespace pros;


FILE* autoSideFile = NULL;

FILE* autoFile = NULL;


bool auto_set = false;
autos cur_auto = autos::auto1;
sides side = sides::red;
screens pages = screens::autos;
bool side_select = true;
bool done = false;

void auto_increase(){
  cur_auto = static_cast<autos>(static_cast<int>(cur_auto)+1);
  if(cur_auto == num_of_ele){
    cur_auto = auto1;
  }
}
void auto_decrease(){
  if(cur_auto == auto1){
    cur_auto = static_cast<autos>(static_cast<int>(num_of_ele)-1);
  }
  else{
    cur_auto = static_cast<autos>(static_cast<int>(cur_auto)-1);
  }
}

void menu_init() {
  autoSideFile = fopen("/usd/autoside.txt","r");
  if(autoSideFile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  int colourSide;
  if(autoSideFile != NULL){
    fscanf(autoSideFile, "%d", &colourSide);
    side = static_cast<sides>(colourSide);
  }
  if(autoSideFile != NULL) fclose(autoSideFile);

  autoFile = fopen("/usd/auto.txt","r");
  if(autoFile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  int file_auto;
  if(autoFile != NULL){
    fscanf(autoFile, "%d", &file_auto);
    cur_auto = static_cast<autos>(file_auto);
  }
  if(autoSideFile != NULL) fclose(autoSideFile);
}

void autos_page(){
  if(!auto_set){
    if (side_select){
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B) || master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
        side = static_cast<sides>(!static_cast<int>(side));
        menu_update();
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
        side_select = false;
        autoSideFile = fopen("/usd/autoside.txt","w");
        if(autoSideFile != NULL){
          fprintf(autoSideFile, "%d",static_cast<int>(side));
          fclose(autoSideFile);
        }
      }
    }
    else{
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
        auto_increase();
        menu_update();
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
        auto_decrease();
        menu_update();
      }
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) side_select = true;
      if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
        auto_set = true;
        autoFile = fopen("/usd/auto.txt","w");
        //char name[80]  = auto_names[static_cast<int>(cur_auto)];
        if(autoFile != NULL){
          fprintf(autoFile, "%d", static_cast<int>(cur_auto));
          fclose(autoFile);
        }
        done = true;
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
  menu_update();
  done = false;
  while(!done){
    delay(10);
    autos_page();
  }
}
