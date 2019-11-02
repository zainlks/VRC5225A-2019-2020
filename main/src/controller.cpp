#include "controller.hpp"
bool doublePressCheck = false;

void printTemp(void* param) {
  master.clear();
  delay(50);
  while(true)
  {
    master.print(2, 0, "L:%d, R:%d, FB:%d", int(intakeL.get_temperature()), int(intakeR.get_temperature()), int(fBar.get_temperature()));
    printf("%d, %d, %d\n", int(intakeL.get_temperature()), int(intakeR.get_temperature()), int(angler.get_temperature()));
    delay(1500);
  }
}
