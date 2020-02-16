#include "tracking.hpp"


Tracking tracking;

bool trackingReset = false;
bool speedLimit = 0;
int offset = 0;
int updateCount = 0;
pros::Task *moveTask = nullptr;
pros::Task *updateTask = nullptr;
bool resetDone = false;
void* labelPointer = nullptr;
void* gotoPointers[10];
moveTargetParams moveParams;
//test without extra angle thing
//test which way negative mode turns
//print values every hundred millis after exit
//decrease angle threshold
//tune PID after adding intake stuff
//classes and cleaning code

double operator "" _deg(long double degree){
  return degree/180 *M_PI;
}
double operator "" _rad(long double radians){
  return radians/M_PI *180;
}

void moveStartTask() {
  moveTask = new Task(move_to_target);
}

void moveStopTask() {
  if(moveTask != nullptr)
  {
    moveTask->remove();
    delete moveTask;
    moveTask = nullptr;
  }
}

void updateStartTask(bool reset) {
  trackingReset = reset;
  updateTask = new Task(update);
}

void updateStopTask(){
  if(updateTask != nullptr)
  {
    updateTask->remove();
    delete updateTask;
    updateTask = nullptr;
  }
}

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

void clear_line(int line) {
  master.print(0, line, "                                                                                       ");

}


void update (void* param){
   double distance_LR = 14.65138; double distance_B = 7.25;
   double radiusR = 0;
   double radiusB = 0;
   double h = 0;
   double h2 = 0;
   double theta = 0; double beta = 0; double alpha = 0;
   double Xx = 0; double Xy = 0; double Yx = 0; double Yy = 0;
   double newleft = 0; double newright = 0; double newback = 0;
   double Right = 0; double Left = 0; double Back = 0;
   double lastleft = 0, lastright = 0, lastback = 0;
   uint32_t last_time = 0;
   double leftLastVel = 0; double rightLastVel=0; double backLastVel = 0;
   resetDone = false;
   if(trackingReset)tracking.reset();
   do {
     leftencoder.reset(); rightencoder.reset(); backencoder.reset();
     printf("%d | %d | %d\n", leftencoder.get_value(), rightencoder.get_value(), backencoder.get_value());
     delay(5);
   } while (leftencoder.get_value() != 0 || rightencoder.get_value() != 0 || backencoder.get_value() != 0);
         resetDone = true;
   printf("%d | %d | %d| x: %f | y: %f\n", leftencoder.get_value(), rightencoder.get_value(), backencoder.get_value(), tracking.xcoord, tracking.ycoord);
 // printf("%d | rightE: %d\n", millis(), rightencoder.get_value());
 // printf("%d | leftE: %d\n", millis(), leftencoder.get_value());
 // printf("%d | backE: %d\n", millis(), backencoder.get_value());

 while (true) {
//amount encoders moved (radians)
	 newleft = leftencoder.get_value() / 360.0* (2.75*M_PI);
	 newright = rightencoder.get_value() / 360.0* (2.75*M_PI);
	 newback = backencoder.get_value() / 360.0* (2.77*M_PI);
	 Right = newright - lastright;
	 Left = newleft - lastleft;
	 Back = newback - lastback;
   if(millis()-last_time >= 20) {
     tracking.velocityL = (newleft - leftLastVel)/(millis() - last_time);
     tracking.velocityR = (newright - rightLastVel)/(millis() - last_time);
     tracking.velocityB = (newback - backLastVel)/(millis() - last_time);
     leftLastVel = newleft;
     rightLastVel = newright;
     backLastVel = newback;
     last_time = millis();
   }
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
		 alpha = tracking.global_angle + beta;
//update global x, y and angle
		 Xx = h2 * cos(alpha);
		 Xy = h2 * -sin(alpha);
		 Yx = h * sin(alpha);
		 Yy = h * cos(alpha);
		 tracking.xcoord += Yx + Xx;
		 tracking.ycoord += Yy + Xy;
     tracking.global_angle += theta;

	// 	 if ((millis() - last_time) > 100){
	// 		 printf("%d | X: %f, Y: %f, A: %f\n", millis(), tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
	// 		 // printf("%d | Y: %f\n", millis(), ycoord);
	// 		 // printf("%d | A: %f\n", millis(), rad_to_deg(global_angle));
 //       // printf("%d | A2: %f\n", millis(), rad_to_deg((newleft - newright)/distance_LR));
 //       // printf("%d | rightE: %d\n", millis(), rightencoder.get_value());
 //       // printf("%d | leftE: %d\n", millis(), leftencoder.get_value());
 //       // printf("%d | backE: %d\n", millis(), backencoder.get_value());
	// 	 last_time = millis();
	// 	 }
	// 	 delay(10);
 // }
 delay(1);
}
}

void move_drive(int x, int y, int a){

  front_L.move(x + y + a);
  front_R.move(-x + y - a);
  back_L.move(-x + y + a);
  back_R.move(x + y - a);

}
void move_drive_side(int L, int R) {
  front_L.move(L);
  front_R.move(R);
  back_L.move(L);
  back_R.move(R);
}

void brake(){
  front_L.move_relative(0,200);
  front_R.move_relative(0,200);
  back_L.move_relative(0,200);
  back_R.move_relative(0,200);
}
void Tracking::reset() {
  tracking.xcoord = 0;
  tracking.ycoord = 0;
  tracking.global_angle = 0;
}
void move_to_target(void* params){
  tracking.target_x = moveParams.target_x;
  tracking.target_y = moveParams.target_y;
  tracking.target_a = moveParams.target_a;
  double power_d;
  bool debug = moveParams.debug;
  bool cubeLineUp = moveParams.cubeLineUp;
  bool brakeOn = moveParams.brakeOn;
  bool inDrive = moveParams.inDrive;
  log("%d | Started move to target: (%f, %f, %f)", pros::millis(),tracking.target_x,tracking.target_y, rad_to_deg(tracking.target_a));
  double max_power_a = 127.0, max_power_xy = moveParams.max_xy;
  double min_power_a = 12, min_power_xy = 25;
  double scale;
  double power_total;
  uint32_t maxCheck = millis();
  double last_power_a = max_power_a, last_power_x = max_power_xy, last_power_y = max_power_xy;
  double integral_a = 0.0, integral_d = 0.0;

  double error_a, error_x, error_y, error_d, errorLocalx, errorLocaly;
  double difference_a;
  double kP_a = 140, kP_d = 14;
  double kI_a = 0.01, kI_d = 0.015;
  double maxVel = 0.0;  // kI_a = 0.01, kI_d = 0.0022;
  int cycleCount = 0;
  tracking.safety = false;
  unsigned long last_time = millis();

  error_a =tracking.target_a - tracking.global_angle;
  error_x =tracking.target_x - tracking.xcoord;
  error_y =tracking.target_y - tracking.ycoord;
  error_d = sqrtf(powf(error_x, 2) + powf(error_y, 2));

  // for(int i = 0; i<max_power_xy; i++) {
  //   if(error_y<-5) tracking.power_y = -i;
  //   if(error_y>5) tracking.power_y = i;
  //   if(error_x<-5) tracking.power_x = i;
  //   if(error_x>5) tracking.power_x = -i;
  //
  //   move_drive(tracking.power_x,tracking.power_y,0);
  //
  //   delay(3);
  // }

  while (fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y))<5 || inDrive == false){


    error_a =tracking.target_a - tracking.global_angle;
    error_x =tracking.target_x - tracking.xcoord;
    error_y =tracking.target_y - tracking.ycoord;
    error_d = sqrtf(powf(error_x, 2) + powf(error_y, 2));
    tracking.driveError = error_d;

    difference_a = tracking.global_angle + atan(error_y/error_x);
    errorLocalx = cos(difference_a) * error_d;
    errorLocaly = sin(difference_a) * error_d;


    if (fabs(error_a) < 5){
      integral_a += error_a * (millis() - last_time);
    }

    // if (fabs(error_a) < deg_to_rad(0.5)){
    //   integral_a = 0;
    //   tracking.power_a  = 0;
    // }

    if (fabs(error_d) < 2.5){ // what triggers integral to start adding?
      integral_d += error_d * (millis() - last_time);
    }
    if(fabs(error_d)<=0.7) {
      integral_d = 0;
    }

    if(debug) {
    log("%d | %d | %d\n", leftencoder.get_value(), rightencoder.get_value(), backencoder.get_value());
    log("%d | X: %f, Y: %f, A: %f\n", millis(), tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
    log("%d | err_x: %f, err_y: %f, err_a: %f, err_d: %f\n", millis(), error_x, error_y, rad_to_deg(error_a), error_d);
    log("%d | difference_a: %f\n", millis(), rad_to_deg(difference_a));
    log("%d | I value %f \n", millis(), integral_d*kI_d);
    }

    // if (fabs(error_d) < 0.5){
    //   integral_d = 0;
    //   power_x = 0;
    //   power_y = 0;
    // }

//DOES MOD OF A NEGATIVE# RETURN POSTITIVE OR NEGATIVE VALUE? -- Negative!
    // tracking.power_a = error_a*kP_a + integral_a*kI_a;
    if(fabs(error_a)>deg_to_rad(0.5)){
      tracking.power_a = map_set(fabs(error_a),deg_to_rad(0.5), M_PI,12.0*sgn(error_a),127.0*sgn(error_a),
                        deg_to_rad(5), sgn(error_a)*20.0,
                        deg_to_rad(20),sgn(error_a)*50.0,
                        deg_to_rad(25),sgn(error_a)*70.0,
                        deg_to_rad(45),sgn(error_a)*85.0,
                        deg_to_rad(60), sgn(error_a)*110.0,
                        deg_to_rad(90),sgn(error_a)*120.0,
                        M_PI,sgn(error_a)*127.0);
    }
    else {
      tracking.power_a = 0;
    }

    power_d = map_set(fabs(error_d),0.5,200.0,15.0,127.0,
                      10.0,127.0,
                      15.0,127.0,
                      18.0, 127.0,
                      25.0,127.0,
                      200.0,127.0);

    if (error_x >= 0){
      tracking.power_x = error_d*cos(difference_a)*kP_d;
      tracking.power_y = error_d*sin(difference_a)*kP_d;
    }
    else{
      tracking.power_x = -error_d*cos(difference_a)*kP_d;
      tracking.power_y = -error_d*sin(difference_a)*kP_d;
    }
    tracking.power_x+= sgn(tracking.power_x) * integral_d * kI_d;
    tracking.power_y+= sgn(tracking.power_y) * integral_d * kI_d;
//controlling max power for a, x, and y
    if (fabs(tracking.power_a) > max_power_a){
      tracking.power_a = sgn(tracking.power_a)*max_power_a;
    }
    // need to scale x and y powers
    // if (fabs(tracking.power_x) > max_power_xy || fabs(tracking.power_y) > max_power_xy){
    //   if (fabs(tracking.power_x) > fabs(tracking.power_y)){
    //     scale = max_power_xy/fabs(tracking.power_x);
    //     tracking.power_x = max_power_xy *sgn(tracking.power_x);
    //     tracking.power_y = tracking.power_y *scale;
    //     tracking.power_a = tracking.power_a*scale;
    //   }
    //   else {
    //     scale = max_power_xy/fabs(tracking.power_y);
    //     tracking.power_y = max_power_xy *sgn(tracking.power_y);
    //     tracking.power_x = tracking.power_x *scale;
    //     tracking.power_a = tracking.power_a*scale;
    //   }
    // }
   if(fabs(tracking.power_a)+fabs(tracking.power_x)+fabs(tracking.power_y)>127) {
     power_total = fabs(tracking.power_a)+fabs(tracking.power_x)+fabs(tracking.power_y);
     tracking.power_a = tracking.power_a/power_total * max_power_xy;
     tracking.power_x = tracking.power_x/power_total * max_power_xy;
     tracking.power_y = tracking.power_y/power_total * max_power_xy;

   }
//setting min power if a, x, and y are not within target
    // if(fabs(tracking.power_a) < min_power_a){
    //   if (fabs(error_a) > deg_to_rad(0.5)){
    //     tracking.power_a = sgn(tracking.power_a)*min_power_a;
    //   }
    //   else{
    //     tracking.power_a = 0;
    //   }
    // }

    if (fabs(errorLocalx) > 0.5 || fabs(error_x) > 0.5){
        if (fabs(tracking.power_x) < min_power_xy){
        tracking.power_x = sgn(tracking.power_x)*min_power_xy;
      }
    }
    else {
      tracking.power_x = 0;
    }


    if (fabs(errorLocaly) > 0.5 || fabs(error_y) > 0.5){
      if(fabs(tracking.power_y) < min_power_xy){

      tracking.power_y = sgn(tracking.power_y)*min_power_xy;
      }
    }
    else{
      tracking.power_y = 0;
    }
    if(fabs(tracking.velocityL + tracking.velocityR)/2 > maxVel && millis()-maxCheck>75)
    {
      maxVel = fabs(tracking.velocityL + tracking.velocityR)/2;
    }

    if(debug) log("%d| pow_x: %f, pow_y: %f, pow: %f\n", millis(), tracking.power_x, tracking.power_y, tracking.power_a);
    move_drive(tracking.power_x, tracking.power_y, tracking.power_a);
    if(tracking.power_x != 0) last_power_x = tracking.power_x;
    if(tracking.power_y != 0) last_power_y = tracking.power_y;
    if(tracking.power_a != 0) last_power_a = tracking.power_a;
    last_time = millis();
    // printf("%f\n",(fabs(tracking.velocityL) + fabs(tracking.velocityR))/2);
    if(((fabs(tracking.velocityL) + fabs(tracking.velocityR))/2) < 0.007 && fabs(tracking.velocityB)<0.0005 && fabs(maxVel > 0.009) && error_d > 1.25){
      cycleCount++;
      if(cycleCount>60)
      {
        brake();
        move_drive(0, 0, 0);
        tracking.safety = true;
        tracking.moveComplete = true;
        log("Movement to (%f, %f, %f) saftied\n",tracking.target_x,tracking.target_y, rad_to_deg(tracking.target_a));
        moveStopTask();
        break;
      }
    }
    else cycleCount = 0;
    if (fabs(error_a) <= deg_to_rad(0.5) && fabs(error_x)<=0.5 && fabs(error_y)<=0.5 && !cubeLineUp){
      difference_a = 0;
      brake();
      if(brakeOn) {
        delay(600);
      }
      move_drive(0, 0, 0);
      log("Movement to (%f, %f, %f) ended\n",tracking.target_x,tracking.target_y, rad_to_deg(tracking.target_a));
      log("X : %f, Y : %f, A : %f\n", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 3, "X : %f, Y : %f, A : %f", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 5,"Movement to (%f, %f, %f) ended\n",tracking.target_x,tracking.target_y, rad_to_deg(tracking.target_a));
      tracking.moveComplete = true;
      moveStopTask();
      break;
    }
    delay(1);
  }
}

void move_to_target_sync(double target_x, double target_y, double target_a, bool brakeOn, double max_xy, bool cubeLineUp,  bool debug, bool inDrive) {
  if(!tracking.moveComplete) moveStopTask();
  if(moveTask != nullptr) moveTask = nullptr;
  moveParams = {target_x, target_y, target_a, brakeOn, max_xy, cubeLineUp, debug, inDrive};
  tracking.driveError = 0;
  tracking.moveComplete = false;
  move_to_target(nullptr);
}
void move_to_target_async(double target_x, double target_y, double target_a, bool brakeOn, double max_xy, bool cubeLineUp,  bool debug, bool inDrive) {
  if(moveTask != nullptr) moveTask = nullptr;
  moveParams = {target_x, target_y, target_a, brakeOn, max_xy, cubeLineUp, debug, inDrive};
  tracking.driveError = 0;
  tracking.moveComplete = false;
  moveStartTask();
}


void Tracking::trackingInput() {
    tracking.power_a = master.get_analog(JOY_TURN);
    tracking.power_x = master.get_analog(JOY_STRAFE);
    tracking.power_y = master.get_analog(JOY_FORWARD);


  if (fabs(tracking.power_a) < 7){
    tracking.power_a = 0;
  }
  if (fabs(tracking.power_x) < 7){
    tracking.power_x = 0;
  }
  if (fabs(tracking.power_y) < 7){
    tracking.power_y = 0;
  }

  move_drive(tracking.power_x, tracking.power_y, tracking.power_a);

  // if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
  //   tracking.x2 = tracking.xcoord;
  //   tracking.y2 = tracking.ycoord;
  //   tracking.a2 = tracking.global_angle;
  // }
  //
  // if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
  //   tracking.move_to_target(tracking.x2, tracking.y2, tracking.a2, false, true);
  // }

  // if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
  //   //tracking.move_to_target(5, 12.0, 0.0, false, true);
  //   tracking.move_to_target(0, 0, 0, false, true);
  //
  // }
}

void Tracking::waitForDistance(double distance) {
  while( ((fabs(driveError) - distance) > 1 || driveError == 0) && !tracking.moveComplete ) delay(1);
}
void Tracking::waitForComplete() {
  while(!moveComplete) delay(1);
}

// void Tracking::setAngleHold(double angle) {
//   holdAngle = angle;
// }
void pointToAngle(void *param) {
    double angle_hold = deg_to_rad(tracking.holdAngle);
    while(true){
      double angle_error = tracking.global_angle-angle_hold;
      if(fabs(angle_error)>(deg_to_rad(0.5)))
      {
        tracking.power_a = -30*sgn(angle_error);
      }
      else tracking.power_a = 0;
    }
}
void Tracking::turn_to_target(double target_x, double target_y, bool debug, bool brakeOn){
  double target_a = atan2((target_x - tracking.xcoord), (target_y - tracking.ycoord));
  double error_a;
  double kP_a = 137;
  double power_a;
  double min_power_a = 12, max_power_a = 55.0;

  while(true){
    error_a = fmod(target_a - tracking.global_angle, 2*M_PI);
    power_a = error_a*kP_a;
    if (fabs(power_a) > max_power_a){
      power_a = sgn(power_a)*max_power_a;
    }

    if(fabs(power_a) < min_power_a){
      if (fabs(error_a) > deg_to_rad(0.5)){
        power_a = sgn(power_a)*min_power_a;
      }
      else{
        power_a = 0;
      }
    }
    if(debug) log("%d| pow: %f, error: %f\n", millis(), power_a, error_a);
    move_drive(0, 0, power_a);
    if (fabs(error_a) <= deg_to_rad(0.5)){
      brake();
      if(brakeOn)delay(300);
      move_drive(0, 0, 0);
      // delay(500);
      log("Movement to (%f, %f, %f) ended\n", tracking.target_x, target_y, rad_to_deg(target_a));
      log("X : %f, Y : %f, A : %f\n", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 3, "X : %f, Y : %f, A : %f", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 2,"Movement to (%f, %f, %f) ended\n", target_x,tracking.target_y, rad_to_deg(target_a));
      break;
    }
    delay(1);
  }
}
void Tracking::turn_to_angle(double target_a, bool debug, bool brakeOn){
  double error_a;
  double kP_a = 137;
  double power_a;
  double min_power_a = 12, max_power_a = 127.0;
  tracking.target_a = target_a;
  while(true){
    error_a = target_a - tracking.global_angle;
    if(fabs(error_a)>deg_to_rad(0.5)){
      tracking.power_a = map_set(fabs(error_a),deg_to_rad(0.5), M_PI,12.0*sgn(error_a),127.0*sgn(error_a),
                        deg_to_rad(5), sgn(error_a)*20.0,
                        deg_to_rad(20),sgn(error_a)*50.0,
                        deg_to_rad(45),sgn(error_a)*85.0,
                        deg_to_rad(60), sgn(error_a)*110.0,
                        deg_to_rad(90),sgn(error_a)*120.0,
                        M_PI,sgn(error_a)*127.0);
    }
    else {
      tracking.power_a = 0;
    }
    if (fabs(power_a) > max_power_a){
      power_a = sgn(power_a)*max_power_a;
    }

    if(fabs(power_a) < min_power_a){
      if (fabs(error_a) > deg_to_rad(0.5)){
        power_a = sgn(power_a)*min_power_a;
      }
      else{
        power_a = 0;
      }
    }
    if(debug) log("%d| pow: %f, error: %f\n", millis(), power_a, error_a);
    move_drive(0, 0, tracking.power_a);
    if (fabs(error_a) <= deg_to_rad(0.5)){
      brake();
      if(brakeOn)delay(100);
      move_drive(0, 0, 0);
      //delay(500);
      printf("TURN TO TARGET to %f ended\n", rad_to_deg(target_a));
      log("Movement to (%f) ended\n", rad_to_deg(target_a));
      log("X : %f, Y : %f, A : %f\n", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 3, "X : %f, Y : %f, A : %f", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      master.print(0, 2,"Movement to (%f, %f, %f) ended\n", rad_to_deg(target_a));
      break;
    }
    delay(1);
  }
}

void Tracking::flattenAgainstWall(bool forward,bool hold) {
  if(forward) {
    move_drive(0, 40, 0);
    delay(100);
    while(fabs(back_L.get_actual_velocity()) > 4 || fabs(back_R.get_actual_velocity()) > 4) {
      if(fabs(back_L.get_actual_velocity()) < 4) {
        front_L.move(0);
        back_L.move(0);
      }
      if(fabs(back_R.get_actual_velocity()) < 4) {
        front_R.move(0);
        back_R.move(0);
      }
    }
    if(hold) move_drive(0,25,0);
  }
  else {
    move_drive(0, -60, 0);
    delay(100);
    while(velocityL != 0 || velocityR !=0) {
      delay(1);
    }
    if(hold) move_drive(0,-25,0);
  }
}
void Tracking::LSLineup(bool hold, bool intake_deposit, int timeoutTime, int speed) {
  bool left = false, right = false;
  int leftCount = 0,rightCount = 0;
  uint32_t startTime = pros::millis();
  int thresh;
  switch(side){
    case sides::blue:
      thresh = 600;
    break;
    case sides::red:
      thresh = 400;
    break;

  }
  move_drive(0, speed, 0);
  delay(300);
  while(!left && !right && (millis()-startTime)<timeoutTime) {
    if(velocityL==0) leftCount++;
    else leftCount = 0;
    if(velocityR==0) rightCount++;
    else rightCount = 0;
    if(leftCount>=60) left = true;
    if(rightCount>=60) right = true;
  }
  if(intake_deposit) {
  intakeL.move(20);
  intakeR.move(-20);
  }
  if(left) {
    if(speed>0)move_drive_side(25, 40);
    else move_drive_side(-25, -40);
    delay(50);
  }
  if(right) {
    if(speed>0)move_drive_side(40,25);
    else move_drive_side(-40,-25);
    delay(50);
  }
  while((!left || !right) && (millis()-startTime)<timeoutTime) {
    if(fabs(velocityL)<0.000002)  left = true;
    if(fabs(velocityR)<0.000002) right = true;
  }
  if(hold){
    if(speed>0)move_drive(0,20,0);
    else move_drive(0,-20,0);
  }
  else move_drive(0,0,0);
}
void Tracking::LSLineupSkills(bool hold, bool intake_deposit, int timeoutTime, int speed) {
  bool left = false, right = false;
  uint32_t startTime = pros::millis();
  int thresh;
  switch(side){
    case sides::blue:
      thresh = 600;
    break;
    case sides::red:
      thresh = 400;
    break;

  }
  move_drive(0, speed, 0);
  delay(300);
  while(!left && !right && (millis()-startTime)<timeoutTime) {
    if(velocityL==0)  left = true;
    if(velocityR==0) right = true;
  }
  if(intake_deposit) {
  intakeL.move(20);
  intakeR.move(-20);
  }
  if(left) {
    // move_drive(80,35,40);
    // delay(500);
    move_drive(55,0,0);
    delay(350);
    // move_drive(-55,0,0);
    // delay(100);
    move_drive(0,60,0);
    delay(100);
  }
  if(right) {
    // move_drive(-80,35,-40);
    // delay(500);
    move_drive(-55,0,0);
    delay(350);
    // move_drive(55,0,0);
    // delay(100);
    move_drive(0,60,0);
    delay(100);
  }
  while((!left || !right) && (millis()-startTime)<timeoutTime) {
    if(velocityL<0.000002)  left = true;
    if(velocityR<0.000002) right = true;
  }
  move_drive(0,60,0);
  delay(50);
  if(hold) move_drive(0,20,0);
  else move_drive(0,0,0);
}

void Tracking::move_xy(double distance, direction direct, bool brakeon, bool debug){
  double error_x, error_y, error_a, targetx, targety, power_x, power_y, power_a;
  // switch(static_cast<int>(tracking.global_angle) % 360){
  //   case 0:
  //   break;
  //   case 90:
  //   break;
  //   case 180:
  //   break;
  //   case 270:
  //   break;
  //   default:
  //     target_x = distance *
  //   break;
  if(direct == x){
    targetx = tracking.target_x + (sin(tracking.global_angle + M_PI/2) * distance);
    targety = tracking.target_y + (cos(tracking.global_angle + M_PI/2) * distance);
  }
  else{
    targetx = tracking.target_x + (sin(tracking.global_angle) * distance);
    targety = tracking.target_y + (cos(tracking.global_angle) * distance);
  }
  while(true){
    error_x = targetx - tracking.xcoord;
    error_y = targety - tracking.ycoord;
    error_a = tracking.target_a - tracking.global_angle;
    printf("%f", deg_to_rad(error_a));
    power_x = map_set(fabs(error_x),0.5,200.0,sgn(error_x)*25.0,sgn(error_x)*127.0,
                      2.0, sgn(error_x)*25.0,
                      5.0, sgn(error_x)*50.0,
                      10.0,sgn(error_x)*100.0,
                      18.0, sgn(error_x)*127.0,
                      200.0,sgn(error_x)*127.0);
    power_y = map_set(fabs(error_y),0.5,200.0,sgn(error_y)*25.0,sgn(error_y)*127.0,
                      2.0, sgn(error_y)*25.0,
                      5.0, sgn(error_y)*50.0,
                      10.0,sgn(error_y)*100.0,
                      18.0, sgn(error_y)*127.0,
                      200.0,sgn(error_y)*127.0);
    power_a = map_set(fabs(error_a),deg_to_rad(0.5), M_PI,7.0*sgn(error_a),127.0*sgn(error_a),
                      deg_to_rad(5), sgn(error_a)*7.0,
                      deg_to_rad(10), sgn(error_a)*10.0,
                      deg_to_rad(20),sgn(error_a)*20.0,
                      deg_to_rad(45),sgn(error_a)*85.0,
                      deg_to_rad(60), sgn(error_a)*110.0,
                      deg_to_rad(90),sgn(error_a)*120.0,
                      M_PI,sgn(error_a)*127.0);
    if (fabs(error_a) <= deg_to_rad(0.5)) power_a = 0;
    if (fabs(error_y) <= 0.5) power_y = 0;
    if (fabs(error_x) <= 0.5) power_x = 0;
    move_drive(power_x, power_y, power_a);
    //move_drive (error_x * 10, error_y * 10, error_a);
    if (fabs(error_a) <= deg_to_rad(0.5) && fabs(error_x)<=0.5 && fabs(error_y)<=0.5 ){
      brake();
      if(brakeon) {
        delay(600);
      }
      move_drive(0, 0, 0);
      log("Movement to (%f, %f, %f) ended\n",tracking.target_x,tracking.target_y, rad_to_deg(tracking.target_a));
      log("X : %f, Y : %f, A : %f\n", tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
      break;
    }
    delay(10);
  }
}
// void Tracking::straightLift(double height){

//   double length = 17.5;
//   double angle;
//   double bottom_angle = 50, bottom_dist;
//   double ticks_per_deg;
//   double distance;
//   double diff;
//   while (true){
//     angle = bottom_angle + (fBar.get_position() * ticks_per_deg);
//     distance = length * sin(angle);
//     diff = distance - bottom_dist;
//     move_drive(0, 60, 0);
//     while ()
//   }
//
// }
