#include "config.hpp"
ADIEncoder leftencoder (1, 2, true);
ADIEncoder rightencoder (5, 6, false);
ADIEncoder backencoder (3, 4, true);
ADIAnalogIn topLs(7);
ADIAnalogIn bottomLs(8);
Vision vision(5);
Motor intakeR(18,false), intakeL(2,false);
Motor fBar(5, true);
Motor angler(4,false);
Motor front_L(1, false), front_R(10, true), back_L(11, false), back_R(20, true);
Imu gyro(15);
Controller master(E_CONTROLLER_MASTER);
