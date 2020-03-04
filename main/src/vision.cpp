#include "vision.hpp"
pros::vision_object_s_t obj = vision.get_by_sig(0, 1);

// #define VISION_FOV_WIDTH 316
// #define VISION_FOV_HEIGHT 212
// horizontal FOV of 75 degrees and a vertical FOV of 47 degrees.
VisionClass green;
void VisionClass::update() {
  uint32_t timer = millis();
  while(millis()-timer<1000)
  {
    obj = vision.get_by_sig(0, 1);
    int16_t temp_x = obj.x_middle_coord;
    int16_t temp_y = vision.get_by_sig(0, 1).y_middle_coord;
    if(temp_y==last_middle) {
      this->good_count++;
    }
    else good_count = 0;
    if(good_count>=25){
      if(this->avg_middle!=0) this->avg_middle = (this->avg_middle+temp_y)/2;
      else this->avg_middle = temp_y;
     }

    if(temp_y < 106) {
      this->angle = (double)this->avg_middle/106.0*(47.0/2.0)+19;
    }
    else {
      this->angle = -1.0*(((double)this->avg_middle/212.0)*47.0-23.5+19);
    }
    double slope = sin(angle*M_PI/180)/cos(angle*M_PI/180);
    this->distance = (2.75-19.8)/slope;
    if(this->avg_distance != 0)this->avg_distance = (this->avg_distance+this->distance)/2;
    else this->avg_distance = this->distance;
    // if(this->distance==last_middle) {
    //   this->distance_good_count++;
    // }
    // else this->distance_good_count = 0;
    // if(distance_good_count>=25){
    //   if(this->avg_distance!=0) this->avg_distance = (this->avg_distance+this->distance)/2;
    //   else this->avg_distance = this->distance;
    //  }
    this->last_middle = temp_y;
    this->last_distance = this->distance;
    delay(1);
  }
  printf("distance is: %f\n",this->avg_distance);
}
