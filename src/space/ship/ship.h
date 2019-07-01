#ifndef SHIP_H
#define SHIP_H
#include <raylib.h>

typedef struct ship
{
  physbody body;
  float thrust;
  float maxThrust;
  float thrustBuild;
} ship;

ship initShips();

void updateShips(ship * fartknocker, float dt);

void drawShip(ship * s);

void drawShipHud(ship * s);
#include "ship.c"
#endif
