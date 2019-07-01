#ifndef MAINLAND_H
#define MAINLAND_H
#include "player/p.h"
#include "terrain/t.h"
#include "terrain/pe.h"

void updateLand(planetaryEnvironment * pe, float dt);
void drawLand(planetaryEnvironment * pe);

#include "ml.c"
#endif
