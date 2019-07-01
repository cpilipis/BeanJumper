#ifndef PLANET_H
#define PLANET_H
#include <raylib.h>
#include "../../land/terrain/t.h"
typedef struct planet
{
Vector2 pos;
float radius;
Color c;
terraindata td;
} planet;

planet * initPlanets();

void drawPlanet(planet * p);

#include "planet.c"
#endif
