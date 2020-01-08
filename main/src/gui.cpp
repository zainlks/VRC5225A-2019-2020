#include "gui.hpp"

lv_obj_t * scr1;
lv_obj_t * titleLabel;
lv_obj_t * liftTestButton;
lv_obj_t * liftTestLabel;
lv_obj_t * upTimeLabel;
lv_obj_t * downTimeLabel;

bool gui_running = false;

void gui_init() {
  scr1 = lv_obj_create(NULL, NULL);
  lv_scr_load(scr1);

  titleLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_align(titleLabel, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(titleLabel, "The PiLons Menu");
  lv_obj_set_pos(titleLabel, 10,10);


  liftTestButton = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(liftTestButton, NULL, LV_ALIGN_CENTER, 0, 0);
  liftTestLabel = lv_label_create(liftTestButton, NULL);
  lv_label_set_text(liftTestLabel, "Lift Test");
  lv_btn_set_action(liftTestButton, LV_BTN_ACTION_LONG_PR, liftTestButtonClicked);


}

lv_res_t liftTestButtonClicked(lv_obj_t* button) {
  printf("im pressed\n");
  gui_running = true;
  if(fBar.get_position()<200)
  {
    uint32_t timer = millis();
    fBar.move_absolute(FBAR_TOP,200);
    while(fBar.get_position()<FBAR_TOP-10) delay(1);
    upTimeLabel = lv_label_create(lv_scr_act(),NULL);
    lv_label_set_align(upTimeLabel, LV_LABEL_ALIGN_LEFT);



    char stringToPrint[30];
    sprintf(stringToPrint, "Up Time is: %d", pros::millis()-timer);

    lv_label_set_text(upTimeLabel, stringToPrint);
    lv_obj_set_pos(upTimeLabel, 10,65);
  }
  else {
    uint32_t timer = millis();
    fBar.move_absolute(1,200);
    downTimeLabel = lv_label_create(lv_scr_act(),NULL);
    lv_label_set_align(downTimeLabel, LV_LABEL_ALIGN_LEFT);

    while(fBar.get_position()>10) delay(1);

    char stringToPrint[30];
    sprintf(stringToPrint, "Down Time is: %d", pros::millis()-timer);

    lv_label_set_text(downTimeLabel, stringToPrint);
    lv_obj_set_pos(downTimeLabel, 10,90);
  }
  gui_running = false;
  // lv_label_set_text(upTimeLabel, "Hello");
  return LV_RES_OK;
}
