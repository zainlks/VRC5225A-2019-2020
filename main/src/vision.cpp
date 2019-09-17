#include "vision.hpp"
pros::Vision vision(6);
visionClass green;
visionClass purple;
int avg_height = 0;
const double FOCAL_LENGTH = 225.9649;
const double CUBE_HEIGHT = 5.7;
const double H_MID = 158;
//Equation to Calculate distance is Distance = (Actual-Width * Focal-Length) / Observed-Pixel-Width

// y/212 *47
void visionClass::reset()
{
  this->x = 0;
  this->y = 0;
  this->average_distance = 0;
  this->average_height = 0;
  this->cur_height = 0;
  this->last_height = 0;
  this->distance = 0;
  this->good_count = 0;
  this->sig_num = 1;
}
vector<double> visionClass::position(){
  return {this->x,this->y};
}
void visionClass::update()
{
  //Update Values - updating all properties of an object
  this->obj = vision.get_by_sig(0, this->sig_num);
  this->cur_height = this->obj.height;

  //Calculating the average height by using the value from the last cycle and filtering out bad values
  if(this->cur_height==this->last_height)
  {
    if(this->good_count==15)
    {
      if(this->average_height==0) this->average_height=this->obj.height;
      else this->average_height = (this->average_height + this->obj.height)/2;
      this->good_count=0;
    }
    else this->good_count++;
  }
  else this->good_count = 0;

  //Calculate Distance using average height
  if(this->average_height!=0) this->distance = (CUBE_HEIGHT*FOCAL_LENGTH)/this->average_height;

  //Update average distance
  if(this->average_distance==0 and this->distance!=0) this->average_distance=this->distance;
  else if(this->distance!=0) this->average_distance = (this->average_distance + this->distance)/2;

  //Update last height to current height
  this->last_height = this->cur_height;
  // 39_in 38px 5.7in
  this->line_dif = this->obj.x_middle_coord-H_MID;
}

void visionClass::lineMiddle(float kP) {
  double power = 0;
  this->update();
  if(abs(this->line_dif)>3) {
    if(fabs(kP*this->line_dif)>50) power = 50 * sgn(this->line_dif);
    else power = kP*this->line_dif;
    move_drive(power, 0, 0);
  }
 else brake();

}
