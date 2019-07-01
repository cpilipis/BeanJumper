#ifndef TERRAIN_H
#define TERRAIN_H
#include <raylib.h>
#include <chipmunk/chipmunk.h>
#include <math.h>

typedef struct terraindata
{
float pointHeights [720];
unsigned int phNum;
unsigned int planetWidth;
} terraindata;

terraindata initTerrain();

#include "t.c"
#endif
