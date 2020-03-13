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
		bool intakeReverse = false;


		double cur_coord;
		//tracking.setAngleHold(0);
		int lastTime = 0;
		setDriveState(driveStates::Auto);
		// Task driveUpdate(driveHandle);
		master.clear();

		if(pros::competition::is_connected() && !pros::competition::is_disabled() && false == true) {
			updateStopTask();
			tracking.ycoord = 9.5;
			tracking.xcoord = 31.5;
			tracking.global_angle = M_PI/2;
			updateStartTask(false);
			fBar.move_absolute(400, 200);
			while(fBar.get_position() < 395 ){delay(1);}
			delay(100);
			intakeL.move(-10);
			intakeR.move(10);
			fBar.move_absolute(1,200);
			delay(1);
			move_to_target_async(40,23.5, M_PI/2,false,127);
			tracking.waitForDistance(8);
			intakeOn();
			tracking.waitForDistance(1.5);
			move_to_target_sync(57,23.5, M_PI/2,false,127);
			tracking.waitForComplete();
			move_to_target_async(43,23.5, M_PI/2,false,127);
			fBar.move(127);
			tracking.waitForComplete();
			while(fBar.get_position()<FBAR_TOP-10) delay(1);
			fBar.move_absolute(FBAR_TOP, 200);
			move_drive(0,0,0);
			// move_to_target_sync(57.5,23.5, M_PI/2,false,45);
			move_drive(0,50,0);
			while(tracking.xcoord<57) delay(1);
			move_drive(0,0,0);

			intakeL.move(80);
			intakeR.move(-80);
			while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
			intakeL.tare_position();
			while(fabs(intakeL.get_position())<900) delay(1);
			intakeL.move(-8);
			intakeR.move(8);
			move_to_target_async(28,13,-M_PI/4,false,127, true);
			tracking.waitForDistance(3);
			fBar.move_absolute(FBAR_MID, 200);
			intakeOn();
			tracking.waitForDistance(1);
			move_to_target_async(14, 23, -M_PI/4,false,127, true);
			tracking.waitForDistance(15);
			fBar.move_absolute(FBAR_MID, 200);
			intakeOn();
			tracking.waitForComplete();
			intakeL.move(80);
			intakeR.move(-80);
			while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
			intakeL.tare_position();
			while(fabs(intakeL.get_position())<900) delay(1);
			intakeL.move(-8);
			intakeR.move(8);
			fBar.move_absolute(FBAR_MID+100, 200);
			delay(50);

			move_to_target_async(26.5, 10, 0,false,127,true);
			tracking.waitForDistance(6);
			fBar.move_absolute(1, 200);
			tracking.waitForComplete();
			tracking.LSLineup(true, false,1400,-60);
			printf("stuck A\n");
			updateStopTask();
			tracking.ycoord = 9.5;
			tracking.xcoord = tracking.xcoord;
			tracking.global_angle = 0;
			updateStartTask(false);
			printf("stuck B\n");
			delay(50);
			intakeOn();
			move_to_target_async(24.5,52.3,0,false,127);
			tracking.waitForDistance(1.2);
			move_to_target_async(20.5, 121, 0,false,127);
			tracking.waitForDistance(55);
			move_to_target_async(25.5, 121, 0,false,90);
			int LsCheck = 0;
			while(topLs.get_value() > 500 || bottomLs.get_value() > 2500) {
				if(bottomLs.get_value() > 2500 && tracking.moveComplete) LsCheck++;
				else LsCheck = 0;
				if (LsCheck >= 40) break;
				delay(1);
			}
			intakeL.move(-17);
			intakeR.move(17);
			fBar.move_absolute(700, 200);
			angler.move_absolute(ANGLER_MID, 160);
			tracking.waitForComplete();
			delay(300);
			move_to_target_sync(18.5, 124, -M_PI/4,false,127,true);
			tracking.LSLineup(true, true, 1500);
			angler.move_absolute(ANGLER_TOP, 130);
			intakeL.move(45);
			intakeR.move(-45);
			delay(50);
			while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
			fBar.move(5);
			while(angler.get_position()<ANGLER_TOP-1150) delay(1);
			angler.move(90);
											// while(angler.get_position()<ANGLER_TOP-800) delay(1);
											// angler.move_absolute(ANGLER_TOP, 85);
											// while(angler.get_position()<ANGLER_TOP-300) delay(1);
											// angler.move_absolute(ANGLER_TOP,160);
											// while(angler.get_position()<ANGLER_TOP-50) delay(1);
											// angler.move_absolute(ANGLER_TOP, 100);
											// while(angler.get_position()<ANGLER_TOP-10) delay(1);
											// delay(100);
											// fBar.move_absolute(600,200);
											// while(fBar.get_position()<300)delay(1);
			while(angler.get_position()<ANGLER_TOP-10) delay(1);
			angler.move(0);
			delay(300);
			fBar.move_absolute(600,200);
			while(fBar.get_position()<300)delay(1);
			move_drive(0,-60,0);
			while(tracking.xcoord<26) delay(1);
			move_drive(0,0,0);
			angler.move_absolute(1, 200);
			fBar.move_absolute(200, 200);
			move_to_target_sync(49, 131.5, -M_PI,false,127,true);
			tracking.LSLineup(true,false,1400,-60);
			updateStopTask();
			tracking.xcoord = tracking.xcoord;
			tracking.ycoord = 134.5;
			tracking.global_angle = -M_PI;
			updateStartTask(false);
			fBar.move_absolute(1, 200);
			intakeOn();
			move_to_target_async(49, 95, -M_PI,false,127);
			tracking.waitForDistance(1.5);
			fBar.move_absolute(FBAR_MID+200, 200);
			tracking.waitForComplete();

			move_to_target_async(10, 108,-M_PI/2, false, 127, true);
			fBar.move_absolute(FBAR_MID+200, 200);
			tracking.waitForComplete();
			tracking.LSLineup(true,false,1500,70);
			delay(75);
			updateStopTask();
			tracking.xcoord = 9.5;
			tracking.ycoord = tracking.ycoord;
			tracking.global_angle = -M_PI/2;
			updateStartTask(false);
			delay(75);
			move_to_target_async(21.5, 108, -M_PI/2, false, 45);
			tracking.waitForDistance(0.2);
			intakeL.move(80);
			intakeR.move(-80);
			while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
			intakeL.tare_position();
			while(fabs(intakeL.get_position())<900) delay(1);
			intakeL.move(-8);
			intakeR.move(8);
			fBar.move_absolute(FBAR_MID+400, 200);
			delay(50);
			while(fBar.get_position()<FBAR_MID+350) delay(1);
			intakeOn();
			tracking.waitForComplete();


			move_to_target_async(37.5, 94, -M_PI,false,127,true);
			tracking.waitForDistance(7);
			fBar.move_absolute(FBAR_MID, 200);
			tracking.waitForComplete();
			intakeL.move(127);
			intakeR.move(-127);
			while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
			intakeL.tare_position();
			while(fabs(intakeL.get_position())<900) delay(1);
			intakeL.move(-8);
			intakeR.move(8);


			fBar.move_absolute(FBAR_MID+400, 200);
			while(fBar.get_position()<FBAR_MID-250) delay(1);

			//
			// move_to_target_async(57, 127.5, -3*M_PI/2,false,127,true);
			// tracking.waitForDistance(42);
			// intakeOn();
			// fBar.move_absolute(FBAR_TOP,200);
			//
			// // tracking.waitForComplete();
			// // tracking.LSLineup(true,false,2500,70);
			// //
			// // double curX = tracking.xcoord;
			// //
			// // move_drive(0,-40,0);
			// // while((curX-tracking.xcoord)<2) delay(1);
			// // move_drive(0,0,0);
			//
			// intakeL.move(80);
			// intakeR.move(-80);
			// while(bottomLs.get_value()>2700 && fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)<10)) delay(1);
			// intakeL.tare_position();
			// while(fabs(intakeL.get_position())<900) delay(1);
			// intakeL.move(-8);
			// intakeR.move(8);

			move_to_target_async(44.5,132.5,-3*M_PI/2,false,127,true);
			tracking.waitForDistance(12);
			fBar.move_absolute(1,200);
			intakeOn();
			tracking.waitForComplete();
			while(fBar.get_position()>100) delay(1);


			move_to_target_async(75.5,134.5,-3*M_PI/2,false,127);
			tracking.waitForDistance(0.6);
			fBar.move_absolute(1300,200);
			move_to_target_sync(97.8, 132, -3*M_PI/2,false,127);
			move_to_target_sync(97.8, 137.5, -M_PI,false,127);
			tracking.waitForComplete();
			fBar.move_absolute(1, 200);
			while(fBar.get_position()>100) delay(1);
			move_to_target_sync(109.5, 123.5, -3*M_PI/2,false,127);
			move_to_target_sync(118.5, 123.5, -3*M_PI/2,false,127);
			move_to_target_async(120, 137, -3*M_PI/2,false,127);
			angler.move_absolute(ANGLER_MID,200);
			fBar.move_absolute(650, 200);
			tracking.waitForComplete();

			move_drive(-60,0,0);
			delay(100);
			bool tResetDone = false;
			int count = 0;
			while(tResetDone == false) {
				if(tracking.velocityB == 0.0) count++;
				else count = 0;
				if(count>60) tResetDone = true;
				delay(1);
			}
			updateStopTask();
			tracking.ycoord = 134.5;
			tracking.xcoord = tracking.xcoord;
			tracking.global_angle = M_PI/2;
			updateStartTask(false);
			tracking.LSLineup(true,true,1500,60);
			updateStopTask();
			tracking.ycoord = tracking.ycoord;
			tracking.xcoord = 123.5;
			tracking.global_angle = tracking.global_angle;
			updateStartTask(false);
			move_drive(0,0,0);
			intakeL.move(40);
			intakeR.move(-40);
			angler.move_absolute(ANGLER_TOP, 200);
			while(angler.get_position()<ANGLER_TOP-5) delay(1);
			move_drive(-30,-60,0);
			while(tracking.xcoord>120.0) delay(1);

			move_to_target_async(101.5, 122, M_PI,false,80);
			angler.move_absolute(1, 200);
			fBar.move_absolute(towerHeights[2] + 400, 75);
			tracking.waitForDistance(12);
			intakeOn();
			while(fBar.get_position()<towerHeights[2] +100) delay(1);
			fBar.move_absolute(towerHeights[2] + 400, 100);
			while(fBar.get_position()<towerHeights[2] + 200)delay(1);
			delay(50);
			tracking.waitForComplete();
			move_to_target_sync(100.5, 110.5,M_PI, false, 60);
			fBar.move_absolute(towerHeights[1]- 700, 100);
			move_to_target_async(100.5, 113.5,M_PI, false);
			while(fBar.get_position()>towerHeights[1]-550)delay(1);
			fBar.move_absolute(towerHeights[0]- 500, 100);
			move_to_target_async(100.5, 112.5,M_PI,false);
			while(fBar.get_position()>towerHeights[0]-350)delay(1);
			delay(50);
			fBar.move_absolute(1, 200);
			angler.move_absolute(1, 200);
			tracking.waitForComplete();
			while(fBar.get_position()>100) delay(1);
			move_to_target_sync(100.5,99,M_PI,false,127);
			move_to_target_sync(109.5,99,M_PI,false,127);
			move_to_target_sync(109.5,93,M_PI,false,80);
			move_to_target_sync(122.5,93,M_PI,false,127);
			move_to_target_async(122.5,35,M_PI,false,127);
			tracking.waitForDistance(20);
			move_to_target_sync(126,34,M_PI,false,127);
			angler.move_absolute(ANGLER_MID, 160);
			fBar.move_absolute(650, 200);
			move_to_target_sync(127.5,23,3*M_PI/4,false,127);
			tracking.LSLineup(true,false,1400,60);
			angler.move_absolute(ANGLER_TOP, 130);
			intakeL.move(45);
			intakeR.move(-45);
			delay(50);
			while((fabs(intakeL.get_actual_velocity())>1 || fabs(intakeR.get_actual_velocity())>1) && angler.get_position()<ANGLER_TOP-250) delay(1);
			fBar.move(5);
			while(angler.get_position()<ANGLER_TOP-1150) delay(1);
			angler.move(90);
											// while(angler.get_position()<ANGLER_TOP-800) delay(1);
											// angler.move_absolute(ANGLER_TOP, 85);
											// while(angler.get_position()<ANGLER_TOP-300) delay(1);
											// angler.move_absolute(ANGLER_TOP,160);
											// while(angler.get_position()<ANGLER_TOP-50) delay(1);
											// angler.move_absolute(ANGLER_TOP, 100);
											// while(angler.get_position()<ANGLER_TOP-10) delay(1);
											// delay(100);
											// fBar.move_absolute(600,200);
											// while(fBar.get_position()<300)delay(1);
			while(angler.get_position()<ANGLER_TOP-10) delay(1);
			angler.move(0);
			delay(100);
			fBar.move_absolute(600,200);
			while(fBar.get_position()<300)delay(1);
			move_drive(0,-60,0);
			delay(500);
			move_drive(0,0,0);
		}
		setDriveState(driveStates::Driver);
		//angler.move_absolute(1800, 100);
	  while (true){
			 //if(startNum == 0 && angler.get_position()>1750) {anglerCal(); startNum++;}
			 //printf("angler: %f\n", angler.get_position());
			 // printf("L: %f, R: %f\n", tracking.velocityB, tracking.velocityR);

			 // printf("global angle is: %f\n",rad_to_deg(tracking.global_angle));
			 // printf("x:%f y:%f, a:%f \n",tracking.xcoord,tracking.ycoord,rad_to_deg(tracking.global_angle));
			 if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
				 updateStopTask();
				 tracking.reset();
				 updateStartTask();
				 setDriveState(driveStates::Auto);
				 if(side == sides::blue) tracking.turn_to_angle(deg_to_rad(8.5),false,false);
				 else if(side == sides::red) tracking.turn_to_angle(deg_to_rad(-8.5),false,false);
				 setDriveState(driveStates::Driver);
			 }
			 anglerHandle();
			 fBarHandle();
			 gui_handle();
			 green.update();
			 // log_graph(front_L.get_actual_velocity());		 // printf("%d | %d\n",green.obj.height, green.obj.width);
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
			 green.update();
			 //printf("center: %d\n",green.obj.x_middle_coord);
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
