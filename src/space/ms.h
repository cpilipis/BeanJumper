#ifndef MAINSPACE_H
#define MAINSPACE_H
#include <raylib.h>
#include <math.h>
#include "ship/ship.h"
#include "planet/planet.h"

void updateSpace(ship * s, float dt);

void drawSpace(ship * s, planet p[], Camera2D * spacecam, polygondata * test, polytridata * poopoo);

#include "ms.c"
#endif
