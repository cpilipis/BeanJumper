#ifndef PLANETENV_H
#define PLANETENV_H
#include <raylib.h>
#include <chipmunk/chipmunk.h>
#include <math.h>
#include "../../space/planet/planet.h"

typedef struct planetaryEnvironment
{
planet * parentPlanet; //the planet this terrain is on
cpSpace * cpspace;
cpShape * terrainShape[720]; //based on the terraindata, must be initialized via Chipmunk Physics
float gravity;
float groundFriction;
Color gc;
Color sc; //ground and sky Color
cpBody * bodies[100];
unsigned int bodyCount;
int playerIndex;
} planetaryEnvironment;
//planetaryEnvironment takes a little while to type, but it also sounds cool to say.
//So, in a way, it balances out
//Hell, it might be a great name for a band

planetaryEnvironment initPlanetEnv(planet * p, float g, float f, Color sc);
void updatePlanet();

#include "pe.c"
#endif
