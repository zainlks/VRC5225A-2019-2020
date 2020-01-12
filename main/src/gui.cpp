#include "gui.hpp"

lv_obj_t * scr1;
lv_obj_t * titleLabel;
lv_obj_t * liftTestButton;
lv_obj_t * liftTestLabel;
lv_obj_t * upTimeLabel;
lv_obj_t * downTimeLabel;

// Motor Position Labels:
lv_obj_t * resetEncoders;
lv_obj_t * resetEncodersLable;

lv_obj_t * leftEncoder;
lv_obj_t * leftEncoderValue;

lv_obj_t * rightEncoder;
lv_obj_t * rightEncoderValue;

lv_obj_t * backEncoder;
lv_obj_t * backEncoderValue;

lv_obj_t * posX;
lv_obj_t * posXValue;

lv_obj_t * posY;
lv_obj_t * posYValue;

lv_obj_t * fbarPos;
lv_obj_t * fbarPosValue;

lv_obj_t * anglerPos;
lv_obj_t * anglerPosValue;

lv_obj_t * motorResets;
lv_obj_t * motorResetsLable;

char stringToPrint[30];

bool gui_running = false;

void gui_init() {
  scr1 = lv_obj_create(NULL, NULL);
  lv_scr_load(scr1);
  lv_obj_t *tabview;
  tabview = lv_tabview_create(lv_scr_act(), NULL);

  //lv_obj_t *ourTeam = lv_tabview_add_tab(tabview, "Our Team");
  lv_obj_t *motorTemp = lv_tabview_add_tab(tabview, "Motor Temp");
  lv_obj_t *posTab = lv_tabview_add_tab(tabview, "Pos");
  lv_obj_t *autoTab = lv_tabview_add_tab(tabview, "Autos");
  lv_obj_t *testingTab = lv_tabview_add_tab(tabview, "Testing");

  leftEncoder = lv_label_create(posTab, NULL);
  lv_label_set_align(leftEncoder, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(leftEncoder, "Left Enc:");
  lv_obj_set_pos(leftEncoder, 0,0);
  lv_obj_align(leftEncoder, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  leftEncoderValue = lv_label_create(posTab, NULL);
  lv_label_set_align(leftEncoderValue, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(leftEncoderValue, "0");
  lv_obj_set_pos(leftEncoderValue, 85,20);

  rightEncoder = lv_label_create(posTab, NULL);
  lv_label_set_align(rightEncoder, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(rightEncoder, "Right Enc:");
  lv_obj_align(rightEncoder, leftEncoder, LV_ALIGN_OUT_TOP_MID, 2, 50);

  rightEncoderValue = lv_label_create(posTab, NULL);
  lv_label_set_align(rightEncoderValue, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(rightEncoderValue, "0");
  lv_obj_align(rightEncoderValue, leftEncoderValue, LV_ALIGN_OUT_TOP_MID, 2, 50);

  backEncoder = lv_label_create(posTab, NULL);
  lv_label_set_align(backEncoder, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(backEncoder, "Back Enc:");
  lv_obj_align(backEncoder, rightEncoder, LV_ALIGN_OUT_TOP_MID, 2, 50);

  backEncoderValue = lv_label_create(posTab, NULL);
  lv_label_set_align(backEncoderValue, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(backEncoderValue, "0");
  lv_obj_align(backEncoderValue, rightEncoderValue, LV_ALIGN_OUT_TOP_MID, 2, 50);

  posX = lv_label_create(posTab, NULL);
  lv_label_set_align(posX, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(posX, "X:");
  lv_obj_align(posX, backEncoder, LV_ALIGN_OUT_TOP_MID, -30, 50);

  posXValue = lv_label_create(posTab, NULL);
  lv_label_set_align(posXValue, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(posXValue, "0");
  lv_obj_align(posXValue, backEncoderValue, LV_ALIGN_OUT_TOP_MID, -60, 50);

  posY = lv_label_create(posTab, NULL);
  lv_label_set_align(posY, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(posY, "Y:");
  lv_obj_align(posY, posX, LV_ALIGN_OUT_TOP_MID, 2, 50);

  posYValue = lv_label_create(posTab, NULL);
  lv_label_set_align(posYValue, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(posYValue, "0");
  lv_obj_align(posYValue, posXValue, LV_ALIGN_OUT_TOP_MID, 2, 50);

  resetEncoders = lv_btn_create(posTab, NULL);
  lv_btn_set_action(resetEncoders, LV_BTN_ACTION_LONG_PR, resetClicked);
  lv_obj_align(resetEncoders, NULL, LV_ALIGN_CENTER, 150, -40);
  resetEncodersLable = lv_label_create(resetEncoders, NULL);
  lv_label_set_text(resetEncodersLable, "tracking reset");

  fbarPos = lv_label_create(posTab, NULL);
  lv_label_set_align(fbarPos, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(fbarPos, "Four Bar:");
  lv_obj_set_pos(fbarPos, 0, -100);
  lv_obj_align(fbarPos, NULL, LV_ALIGN_CENTER, 0, 0);

  fbarPosValue = lv_label_create(posTab, NULL);
  lv_label_set_align(fbarPosValue, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(fbarPosValue, "0");
  lv_obj_set_pos(fbarPosValue, 50,-100);
  lv_obj_align(fbarPosValue, NULL, LV_ALIGN_CENTER, 50, 0);

  anglerPos = lv_label_create(posTab, NULL);
  lv_label_set_align(anglerPos, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(anglerPos, "Angler:");
  lv_obj_align(anglerPos, fbarPos, LV_ALIGN_CENTER, 0, 20);

  anglerPosValue = lv_label_create(posTab, NULL);
  lv_label_set_align(anglerPosValue, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(anglerPosValue, "0");
  lv_obj_align(anglerPosValue, fbarPosValue, LV_ALIGN_CENTER, 0, 20);

  motorResets = lv_btn_create(posTab, NULL);
  lv_btn_set_action(motorResets, LV_BTN_ACTION_LONG_PR, MotorClicked);
  lv_obj_align(motorResets, NULL, LV_ALIGN_CENTER, 150, 60);
  motorResetsLable = lv_label_create(motorResets, NULL);
  lv_label_set_text(motorResetsLable, "Motor Reset");



  titleLabel = lv_label_create(motorTemp, NULL);
  lv_label_set_align(titleLabel, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(titleLabel, "The PiLons Menu");
  lv_obj_set_pos(titleLabel, 10,0);




  liftTestButton = lv_btn_create(testingTab, NULL);
  lv_obj_align(liftTestButton, NULL, LV_ALIGN_CENTER, 0, 0);
  liftTestLabel = lv_label_create(liftTestButton, NULL);
  lv_label_set_text(liftTestLabel, "Lift Test");
  lv_btn_set_action(liftTestButton, LV_BTN_ACTION_LONG_PR, liftTestButtonClicked);


}


void gui_handle() {
  sprintf(stringToPrint,"%d",leftencoder.get_value());
  lv_label_set_text(leftEncoderValue,stringToPrint);
  sprintf(stringToPrint,"%d",rightencoder.get_value());
  lv_label_set_text(rightEncoderValue,stringToPrint);
  sprintf(stringToPrint,"%d",backencoder.get_value());
  lv_label_set_text(backEncoderValue,stringToPrint);
  sprintf(stringToPrint,"%f",tracking.xcoord);
  lv_label_set_text(posXValue,stringToPrint);
  sprintf(stringToPrint,"%f",tracking.ycoord);
  lv_label_set_text(posYValue,stringToPrint);
  sprintf(stringToPrint,"%d",static_cast<int>(fBar.get_position()));
  lv_label_set_text(fbarPosValue,stringToPrint);
  sprintf(stringToPrint,"%d",static_cast<int>(angler.get_position()));
  lv_label_set_text(anglerPosValue,stringToPrint);
}

lv_res_t resetClicked(lv_obj_t* button) {
  updateStopTask();
  tracking.reset();
  updateStartTask();
  return LV_RES_OK;
}
lv_res_t MotorClicked(lv_obj_t* button) {
  fBarCal();
	anglerCal();
  return LV_RES_OK;
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
