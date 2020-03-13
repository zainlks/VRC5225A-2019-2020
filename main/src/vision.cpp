#include "vision.hpp"
pros::vision_object_s_t obj = vision.get_by_sig(0, 1);
double FOV_WIDTH = 0;
double FOV_HEIGHT =0;
double FOV = 62;
double test_angle = 0;
double test_pixel = 0;
double test_fov = 0;
// #define VISION_FOV_WIDTH 316
// #define VISION_FOV_HEIGHT 212
// horizontal FOV of 75 degrees and a vertical FOV of 47 degrees.
// 0.2373417721519 per pixel on vertical 0.22169811320755‬ per pixel on horizontal
VisionClass green;
void VisionClass::update() {

  uint32_t timer = millis();
  while(millis()-timer<100){
    vision.set_exposure(50);
    vision.set_white_balance(1);
    obj = vision.get_by_sig(0, 1);
   int16_t temp_x = obj.x_middle_coord;
   int16_t temp_y = vision.get_by_sig(0, 1).y_middle_coord;
   x_middle = temp_x;
   y_middle = temp_y;
   double distance_in = 30;
   //distance_in = distance_in * 2;
   test_angle =  1.57079632675 - (atan(distance_in / camera_height)) ; //devide
   if(vision.get_by_sig(0, 1).y_middle_coord< 106 ) {
     test_pixel = 106 - vision.get_by_sig(0, 1).y_middle_coord;
   }
   else{
     test_pixel = vision.get_by_sig(0, 1).y_middle_coord - 106;
   }
   test_fov = (test_angle / test_pixel) * 180/3.1415926535;


   double feild_of_view_in_height = (212 * 5.5) / vision.get_by_sig(0, 1).height;
   double feild_of_view_in_width = (316 * 5.5) / vision.get_by_sig(0, 1).width;
   FOV_WIDTH = ((atan(feild_of_view_in_width/distance_in))*2) * 180/3.1415926535;

   FOV_HEIGHT = (atan(feild_of_view_in_height /(2 * distance_in)))  * 180/3.1415926535;

   if(temp_y < 106){
     this->vertical_angle = ((106 - temp_y) * (0.543440) ); // calculates alfa
   }
   else{
     this->vertical_angle = ((temp_y - 106)*(0.543440)) * -1;
   }
  if(temp_x < 158){
    this->horizontal_angle = (158 - temp_x)*(FOV / 316 );
  }
  else{
    this->horizontal_angle = ((temp_x - 158)*(FOV / 316 )) * -1;
  }
  this->x = cos(deg_to_rad(horizontal_angle));
  this->x = x * (-camera_height/sin(deg_to_rad(vertical_angle)));

  this->y = sin(deg_to_rad(horizontal_angle));
  this->y = y * (-camera_height / sin(deg_to_rad(vertical_angle)));
 }
printf("our x %f our y %f horizontal_angle %f vertical_angle %f y_middle %f x_middle %f vertical_fov%f horizontal_fov %f test_angle%f: \n", x , y, horizontal_angle, vertical_angle, y_middle, x_middle, FOV_HEIGHT, FOV_WIDTH, test_fov);

//printf("h: %f w: %f \n", double(vision.get_by_sig(0, 1).height), double(vision.get_by_sig(0, 1).width));
//delay(50);
}
