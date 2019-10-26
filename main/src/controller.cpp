#include "controller.hpp"
bool doublePressCheck = false;

void printTemp(void* param) {
  while(true)
  {
    master.clear_line(2);
    master.print(2, 0, "%d, %d, %d", int(intakeL.get_temperature()), int(intakeR.get_temperature()), int(angler.get_temperature()));
    printf("%d, %d, %d\n", int(intakeL.get_temperature()), int(intakeR.get_temperature()), int(angler.get_temperature()));
    delay(1500);
  }
}
