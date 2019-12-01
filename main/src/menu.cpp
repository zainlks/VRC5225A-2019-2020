
#include "menu.hpp"
using namespace pros;


FILE* autoSideFile = NULL;

FILE* autoFile = NULL;


bool auto_set = false;
autos cur_auto = autos::auto1;
sides side = sides::red;
screens pages = screens::autos;
bool side_select = true;
bool done = false;



void menu_init() {
  autoSideFile = fopen("/usd/autoside.txt","r");
  if(autoSideFile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  char colourSide[80];
  if(autoSideFile != NULL){
    fscanf(autoSideFile, "%s", colourSide);
    if(!strcmp(colourSide,"red")) side = sides::red;
    if(!strcmp(colourSide,"blue")) side = sides::blue;
  }
  if(autoSideFile != NULL) fclose(autoSideFile);

  autoFile = fopen("/usd/auto.txt","r");
  if(autoFile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  char autoC[80];
  if(autoFile != NULL){
    fscanf(autoFile, "%s", autoC);
    if(!strcmp(autoC,"auto1")) cur_auto = autos::auto1;
    if(!strcmp(autoC,"auto2")) cur_auto = autos::auto2;
    if(!strcmp(autoC,"auto3")) cur_auto = autos::auto3;
  }
  if(autoSideFile != NULL) fclose(autoSideFile);
}

void autos_page(){
  if(!auto_set){
    if (side_select){
      switch(side){
        case sides::red:
          if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            side_select = false;
            autoSideFile = fopen("/usd/autoside.txt","w");
            if(autoSideFile != NULL){
              fprintf(autoSideFile, "red");
              fclose(autoSideFile);
            }
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
            autoSideFile = fopen("/usd/autoside.txt","w");
            if(autoSideFile != NULL){
              fprintf(autoSideFile, "blue");
              fclose(autoSideFile);
            }
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
            autoFile = fopen("/usd/auto.txt","w");
            if(autoFile != NULL){
              fprintf(autoFile, "auto1");
              fclose(autoFile);
            }
            done = true;
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
            autoFile = fopen("/usd/auto.txt","w");
            if(autoFile != NULL){
              fprintf(autoFile, "auto2");
              fclose(autoFile);
            }
            done = true;
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
              autoFile = fopen("/usd/auto.txt","w");
              if(autoFile != NULL){
                fprintf(autoFile, "auto3");
                fclose(autoFile);
              }
              done = true;
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
  menu_update();
  done = false;
  while(!done){
    delay(10);
    autos_page();
  }
}
