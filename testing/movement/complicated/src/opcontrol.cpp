#include "main.h"
#include "config.hpp"
using namespace pros;
#include <iostream>
#include <cmath>

double xcoord = 0, ycoord = 0;
double global_angle = 0;

double x2 = 0, y2 = 0, a2 = 0;
bool toggle_target = false, toggle_cube = false;
double power_a, power_x, power_y;
bool target, cube;

//test without extra angle thing
//test which way negative mode turns
//print values every hundred millis after exit
//decrease angle threshold
//tune PID after adding intake stuff
//classes and cleaning code

double deg_to_rad(double degrees){
  return degrees/180 *M_PI;
}

double rad_to_deg(double radians){
  return radians/M_PI *180;
}

int sgn(double num){
  if (num < 0){
    return -1;
  }
  else if (num > 0){
    return 1;
  }
  else{
    return 0;
  }
}

void tracking (void* param){
 double distance_LR = 14.5; double distance_B = 7.25;
 double radiusR = 0;
 double radiusB = 0;
 double h = 0;
 double h2 = 0;
 double theta = 0; double beta = 0; double alpha = 0;
 double Xx = 0; double Xy = 0; double Yx = 0; double Yy = 0;

 leftencoder.reset(); rightencoder.reset(); backencoder.reset();
 double newleft = 0; double newright = 0; double newback = 0;
 double Right = 0; double Left = 0; double Back = 0;
 double lastleft = 0, lastright = 0, lastback = 0;

 while (true) {
//amount encoders moved (radians)
	 newleft = leftencoder.get_value() / 360.0* (2.75*M_PI);
	 newright = rightencoder.get_value() / 360.0* (2.75*M_PI);
	 newback = backencoder.get_value() / 360.0* (2.77*M_PI);
	 Right = newright - lastright;
	 Left = newleft - lastleft;
	 Back = newback - lastback;

//update last
	 lastright = newright;
	 lastleft = newleft;
	 lastback = newback;
	 theta = (Left - Right) / distance_LR;
//if robot turned in any direction
	 if (theta != 0){
		 radiusR = Right / theta;
		 beta = theta / 2.0;
		 h = (radiusR + distance_LR/2) * 2 *sin(beta);
		 radiusB = Back / theta;
		 h2 = (radiusB + distance_B) * 2 *sin(beta);
	 }
//if robot moved straight or didn't move
	 else {
		 h = Right;
		 h2 = Back;
		 beta = 0;
	 }
		 alpha = global_angle + beta;
//update global x, y and angle
		 Xx = h2 * cos(alpha);
		 Xy = h2 * -sin(alpha);
		 Yx = h * sin(alpha);
		 Yy = h * cos(alpha);
		 xcoord += Yx + Xx;
		 ycoord += Yy + Xy;

     global_angle += theta;

		 delay(10);
 }
}

void move_drive(int x, int y, int a){

  front_L.move(x + y + a);
  front_R.move(-x + y - a);
  back_L.move(-x + y + a);
  back_R.move(x + y - a);

}

void brake(){
  front_L.move_velocity(0);
  front_R.move_velocity(0);
  back_L.move_velocity(0);
  back_R.move_velocity(0);
  delay(300);
}

void move_to_target(double target_x, double target_y, double target_a){
  // one %f missing in next print statment
  printf("%d | Started move to target: (%f, %f, %f)", pros::millis(), target_x, target_y, rad_to_deg(target_a));
  double max_power_xy = 90.0, max_power_a = 55.0;
  double min_power_a = 12, min_power_xy = 13;
  double scale;

  double last_power_a = max_power_a, last_power_x = max_power_xy, last_power_y = max_power_xy;
  double integral_a = 0.0, integral_x = 0.0, integral_y = 0.0;

  double error_a, error_x, error_y;
  double kP_x = 11.8, kP_a = 134.4; //13, 135
  double kI_a = 0.01, kI_x = 0.0022, kI_y = 0.0022;
  double p_val_x, p_val_y, p_val_a;
  double i_val_x, i_val_y, i_val_a;
  double power_1, power_2;
  unsigned long last_time = millis();
  double integral = 0;
  while (true){

    printf("%d | X: %f, Y: %f, A: %f\n", millis(), xcoord, ycoord, rad_to_deg(global_angle));

    error_a = target_a - global_angle;
    error_x = target_x - xcoord;
    error_y = target_y - ycoord;


    if (fabs(last_power_a) < max_power_a){
      integral_a += error_a * (millis() - last_time);
      printf("A is less \n");
    }
    if (fabs(error_a) < deg_to_rad(0.5)){
      integral_a = 0;
      power_a  = 0;
    }

    if (fabs(last_power_x) < max_power_xy){
      integral_x += error_x * (millis() - last_time);
      printf("X is less \n");
    }

    if (fabs(error_x) < 0.5){
      integral_x = 0;
      power_x = 0;
    }

    if (fabs(last_power_y) < max_power_xy){
      integral_y += error_y * (millis() - last_time);
      printf("Y is less\n");
    }

    if (fabs(error_y) < 0.5){
      integral_y = 0;
      power_y = 0;
    }


    p_val_x = error_x*kP_x;
    p_val_y = error_y*kP_x;
    p_val_a = error_a*kP_a;

    i_val_x = integral_x*kI_x;
    i_val_y = integral_y*kI_y;
    i_val_a = integral_a*kI_a;

    power_1 = p_val_x + i_val_x;
    power_2 = p_val_y + i_val_y;
    power_a = error_a*kP_a + integral_a * kI_a;
    power_x = power_1*cos(global_angle) - power_2*sin(global_angle);
    power_y = power_2*cos(global_angle) + power_1*sin(global_angle);

    if (fabs(power_a) > max_power_a){
      power_a = sgn(power_a)*max_power_a;
    }

    if(fabs(power_a) < min_power_a){
      //printf("Entered if: %f\n", power_a);
      if (fabs(error_a) > deg_to_rad(0.5)){
        power_a = sgn(power_a)*min_power_a;
        //printf("Entered second if: %f\n", power_a);
      }
      else{
        power_a = 0;
      }
    }

    if (fabs(error_x) < 0.5) {
      power_x = 0;
    }
    else if (fabs(power_x) < min_power_xy){
      power_x = sgn(power_x)*min_power_xy;
    }


    if (fabs(error_y) < 0.5) {
      power_y = 0;
    }
    else if (fabs(power_y) < min_power_xy){
      power_y = sgn(power_y)*min_power_xy;
    }


    if (fabs(power_x) > max_power_xy || fabs(power_y) > max_power_xy){
      if (fabs(power_x) > fabs(power_y)){
        scale = max_power_xy/fabs(power_x);
        power_x = max_power_xy *sgn(power_x);
        power_y = power_y *scale;
      }
      else {
        scale = max_power_xy/fabs(power_y);
        power_y = max_power_xy *sgn(power_y);
        power_x = power_x *scale;
      }
    }

    move_drive(power_x, power_y, power_a);

    last_power_x = power_x;
    last_power_y = power_y;
    last_power_a = power_a;
    last_time = millis();

    printf("%d | power_x: %f, power_y: %f, power_a: %f\n", millis(), power_x, power_y, rad_to_deg(power_a));
    printf("%d | error_x: %f, error_y: %f, error_a: %f\n", millis(), error_x, error_y, rad_to_deg(error_a));
    printf("%d | target_x: %f,target_y: %f, target_a: %f\n", millis(), target_x, target_y, rad_to_deg(target_a));
    printf("%d | p_val_x: %f, i_val_x: %f, p_val_y: %f, i_val_y: %f, p_val_a: %f, i_val_a: %f\n", millis(), p_val_x, i_val_x, p_val_y, i_val_y, p_val_a, i_val_a);

    if (fabs(error_a) <= deg_to_rad(0.5) && fabs(error_x) < 0.5 && fabs(error_y) < 0.5){
      brake();
      delay(300);
      printf("Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      printf("%d | error_x: %f, error_y: %f, error_a: %f\n", millis(), error_x, error_y, rad_to_deg(error_a));
      break;
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_X)){
      brake();
      delay(300);
      printf("Movement to (%f, %f, %f\n) ended", target_x, target_y, rad_to_deg(target_a));
      printf("%d | error_x: %f, error_y: %f, error_a: %f\n", millis(), error_x, error_y, rad_to_deg(error_a));
      break;
    }
    delay(3);
  }
}


void opcontrol() {
  front_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  front_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  back_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  back_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  delay(6000);
  Task tracking_task(tracking);

  while (true){

     power_a = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
     power_x = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
     power_y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

     if (fabs(power_a) < 5){
       power_a = 0;
     }
     if (fabs(power_x) < 5){
       power_x = 0;
     }
     if (fabs(power_y) < 5){
       power_y = 0;
     }

     move_drive(power_x, power_y, power_a);

     if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
       x2 = xcoord;
       y2 = ycoord;
       a2 = global_angle;
     }
     if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
       xcoord = 0;
       ycoord = 0;
       global_angle = 0;
     }

		 if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
       move_to_target(x2, y2, a2);
		 }

     if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
       move_to_target(-13.0, 0.0, 0.0);
       delay(500);
       move_to_target(-13.0, 60.0, 0.0);
       move_to_target(-13.0, 80.0, M_PI/2);
       delay(500);
       move_to_target(6.0, 80.0, M_PI/2);
       delay(500);
       move_to_target(6.0, 80.0, M_PI);
       delay(500);
       move_to_target(-13.0, 80.0, M_PI);
       delay(500);
       move_to_target(0.0, 0.0, M_PI);
       delay(1000);
     }

  }
}
