#include "config.hpp"

ADIEncoder leftencoder (1, 2, true);
ADIEncoder rightencoder (5, 6, false);
ADIEncoder backencoder (3, 4, false);
Motor angler(4, true);
Motor intakeL(18, false), intakeR(2, false);
Motor front_L(1, false), front_R(10, true), back_L(11, false), back_R(20, true);
Controller master(E_CONTROLLER_MASTER);
