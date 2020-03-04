#include "config.hpp"
ADIEncoder leftencoder (1, 2, true);
ADIEncoder rightencoder (5, 6, false);
ADIEncoder backencoder (3, 4, true);
ADIAnalogIn topLs(7);
ADIAnalogIn bottomLs(8);
Vision vision(16);
Motor intakeR(15,false), intakeL(12,false);
Motor fBar(5, true);
Motor angler(13,false);
Motor front_L(1, false), front_R(10, true), back_L(11, false), back_R(20, true);
Controller master(E_CONTROLLER_MASTER);
