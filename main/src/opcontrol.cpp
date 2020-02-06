#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
#include "fBar.hpp"
#include "angler.hpp"
#include "drive.hpp"
#include "controller.hpp"
#include "logging.hpp"
#include "menu.hpp"
#include "gui.hpp"

using namespace pros;
int startNum = 0;


void opcontrol() {
	  double start_x;
		double start_y;
		double start_a;
		double power = 0;
		double kP = 1.2;
		uint32_t stoptime = 0;
		uint32_t LTimer = millis();
		uint32_t nineCubeTime = 0;
		bool nineCubeSafety = false;
		bool nineCube = false;
		bool intk_stop = false;
		double fBar_height = 0;
		green.sig_num = 1;
		orange.sig_num = 2;
		bool intakeReverse = false;


		double cur_coord;
		//tracking.setAngleHold(0);
		int lastTime = 0;
		setDriveState(driveStates::Auto);
		// Task driveUpdate(driveHandle);
		master.clear();



		if(pros::competition::is_connected() && !pros::competition::is_disabled() && cur_auto ==  auto4 && false == true) {
			updateStopTask();
			tracking.reset();
			updateStartTask();
			bool outtakeState = false;
		  uint32_t outtakeTime = 0;
			fBar.move_absolute(400, 200);
		  while(fBar.get_position() < 395 ){delay(1);}
		  delay(100);

		  intakeL.move(-15);
		  intakeR.move(15);
		  fBar.move_absolute(1,200);
		  //delay(50);
		  while(fBar.get_position()> 50) {delay(1);}
		  fBar.move(-25);
			move_to_target_async(0, 16, 0, false, 50,false,true);
		  intakeOn();
		  tracking.waitForDistance(12);

		  fBar.move_absolute(towerHeights[2] + 400, 200);
		  while(fBar.get_position()<towerHeights[2] +100) delay(1);
		  fBar.move_absolute(towerHeights[2] + 400, 100);
		  while(fBar.get_position()<towerHeights[2] + 200)delay(1);
		  delay(50);
		  tracking.waitForComplete();
		  move_to_target_sync(0, 24,0, false, 60);
		  fBar.move_absolute(towerHeights[1]- 700, 100);
		  move_to_target_async(0, 20,0, false);
		  while(fBar.get_position()>towerHeights[1]-550)delay(1);
		  fBar.move_absolute(towerHeights[0]- 500, 100);
		  move_to_target_async(0, 22,0,false);
		  while(fBar.get_position()>towerHeights[0]-350)delay(1);
		  delay(50);
		  fBar.move_absolute(1, 200);
		  while(fBar.get_position()> 1000)delay(1);
		}
		setDriveState(driveStates::Driver);
		//angler.move_absolute(1800, 100);
	  while (true){
			 //if(startNum == 0 && angler.get_position()>1750) {anglerCal(); startNum++;}
			 //printf("angler: %f\n", angler.get_position());
			 printf("L: %f, R: %f\n", tracking.velocityB, tracking.velocityR);

			 // printf("global angle is: %f\n",rad_to_deg(tracking.global_angle));
			 anglerHandle();
			 fBarHandle();
			 gui_handle();
			 green.update();
			 log_graph(front_L.get_actual_velocity());		 // printf("%d | %d\n",green.obj.height, green.obj.width);
			 // printf("%d | %d \n", topLs.get_value(), bottomLs.get_value());

			 // printf("left%d right %d\n", leftLs.get_value(), rightLs.get_value());
			//  for(int x = 0; x < 50; x++){
			//  	intakeL.move_velocity(-x);
			// 	intakeR.move_velocity(x);
			// 	printf("%d \n", x);
			// 	delay(500);
			// }
			// if(intakeR.get_actual_velocity() > 50 && topLs.get_value() < 500 && bottomLs.get_value() > 2500 && angler.get_position() < 400){
			// 	if(!nineCubeSafety){
			// 		nineCubeTime = millis();
			// 		nineCubeSafety = true;
			// 	}
			// 	if(nineCubeSafety && nineCubeTime + 200 < millis()){
			// 		intakeR.move(15);
			// 		intakeL.move(-15);
			// 		nineCubeSafety = false;
			// 		nineCube = true;
			// 		angler.move_absolute(3500, 200);
			// 	}
			//
			//
			// }
			if(nineCube && master.get_digital_new_press(INTK_IN_BUTTON)){
				nineCube = false;
				intakeOn();
				angler.move_absolute(1,200);
			}
				if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
					fBar.move_absolute(400, 200);
				  while(fBar.get_position() < 395 ){delay(1);}
				  delay(100);
				  intakeL.move(-10);
				  intakeR.move(10);
				  fBar.move_absolute(1,200);
					setfBarState(fBarStates::Idle);
				  delay(50);

				}
			if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
				 fBar_height += 150;
				 fBar.move_absolute(fBar_height, 80);
				 master.print(2,0, "Height is: %f", fBar_height);
			}
			if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) menu();
			 if(master.get_digital_new_press(SPEED_LIMIT))
			 {
				 if(speedLimit)speedLimit = false;
				 else speedLimit = true;
			 }
			 if(master.get_digital_new_press(INTK_IN_BUTTON)) {
				 if(fabs(intakeL.get_actual_velocity())>25)
				 {
					 intakeR.move(8);
					 intakeL.move(-8);
				 }
				 else {
					 intakeL.move(-127);
					 intakeR.move(127);
				 }
			 }
			 if(master.get_digital_new_press(INTK_OUT_BUTTON)) {
				 if(fBar.get_position()>200)
				 {
					 intakeL.move(127);
					 intakeR.move(-127);
					 while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)&& !master.get_digital_new_press(INTK_IN_BUTTON)&& !master.get_digital_new_press(INTK_OUT_BUTTON))delay(1);
					 intakeL.tare_position();
					 while(fabs(intakeL.get_position())<900 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10) && !master.get_digital_new_press(INTK_IN_BUTTON)&& !master.get_digital_new_press(INTK_OUT_BUTTON)) delay(1);
					 intakeL.move(-8);
					 intakeR.move(8);
					 intakeReverse = true;
					 updateStopTask();
					 tracking.reset();
				   updateStartTask(true);
				 }
				 else {
					 if(fabs(intakeL.get_actual_velocity())>10)
					 {
						 intakeL.move(-5);
							intakeR.move(5);
					 }
					 else
					 {
						 intakeL.move(127);
						 intakeR.move(-127);
					 }
				 }
		 	}
			if(intakeReverse && (fabs(tracking.ycoord)>3 || fabs(tracking.xcoord)>3)) {
				intakeL.move(-127);
				intakeR.move(127);
				intakeReverse = false;
			}
			 // tracking.move_to_target(0, 10, 0);
			 // green.update();
			 // printf("center: %d\n",green.obj.x_middle_coord);
			 // printf("global angle: %f\n", tracking.global_angle);
	     // green.lineMiddle(1.2);
			  //printf("L:%d R:%d G:%d\n",leftencoder.get_value(),rightencoder.get_value(),backencoder.get_value());

			 delay(1);
			// fBar.move_absolute(2250, 200);
 		 	// while (fBar.get_position() < 2230) delay(1);
 		 	// intakeL.move(-127);
 		 	// intakeR.move(127);
 			// if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
			// 	start_y = tracking.ycoord;
			// 	start_x = tracking.xcoord;
			// 	start_a = tracking.global_angle;
			// 	// master.print(2,0,"hit button");
			// 	// updateStopTask();
			//   // tracking.reset();
			//   // updateStartTask();
			// 	// delay(10);
			// 	// master.print(1,0,"here");
 		 	// 	move_to_target_sync(start_x , start_y+4, start_a, false, 127);
 		 	// 	fBar.move_absolute(1600, 125);
			// 	while (fBar.get_position() >  1620) delay(1);
 		 	// 	move_to_target_async(start_x , start_y+6, start_a, false, 127);
 		 	// 	fBar.move_absolute(1050, 125);
			// 	while (fBar.get_position() >  1070) delay(1);
 		 	// 	tracking.waitForComplete();
 		 	// 	fBar.move_absolute(1, 125);
			// 	while (fBar.get_position() > 1000) delay(1);
			// 	move_to_target_sync(start_x , start_y+9, start_a, false, 127);
			// 	while (fBar.get_position() > 10) delay(1);
			// 	delay(500);
 	 		// }


	   }


		//menu();
}
