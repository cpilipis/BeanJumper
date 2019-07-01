#include "pe.h"
#include <chipmunk/chipmunk.h>
#include <math.h>


planetaryEnvironment initPlanetEnv(planet * p, float g, float f, Color sc)
{
  planetaryEnvironment pe;
  printf("Establishing planetary environment control . . . standby . . . \n"); //Yes, that's a command and conquer reference
  pe.parentPlanet = p;
  pe.gravity = g;
  pe.groundFriction = f;
  pe.sc = sc;
  pe.gc = p->c;
  pe.bodyCount = 0;
  pe.playerIndex = 0;


  pe.cpspace = cpSpaceNew();
  cpVect gravity = cpv(0, pe.gravity);
  cpSpaceSetGravity(pe.cpspace, gravity);
  terraindata tdshort = pe.parentPlanet->td;
  printf("phnum is %d\n", tdshort.phNum);
  printf("the actual one is %d\n", pe.parentPlanet->td.phNum);
  float tdSpacing = tdshort.planetWidth/tdshort.phNum;
  for(int tc = 0; tc < tdshort.phNum - 1; tc++)
  {
    pe.terrainShape[tc] = cpSegmentShapeNew(cpSpaceGetStaticBody(pe.cpspace), cpv(tdSpacing * tc, tdshort.pointHeights[tc]), cpv(tdSpacing * (tc + 1), tdshort.pointHeights[tc + 1]), 0);

  }
  for(int t = 0; t < p->td.phNum - 1; t++)
  {
    cpShapeSetFriction(pe.terrainShape[t], 1);
    cpSpaceAddShape(pe.cpspace, pe.terrainShape[t]);
  }



  return pe;
}

void addBall(planetaryEnvironment * pe, float x, float y)
{
  /*
  add a physics ball
  what's a physics ball, I hear you ask?
  it's a ball . . . OF PHYSICS!
  */
  cpFloat radius = 20;
  cpFloat mass = 10;
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

  pe->bodies[pe->bodyCount] = cpSpaceAddBody(pe->cpspace, cpBodyNew(mass, moment));
  cpBodySetPosition(pe->bodies[pe->bodyCount], cpv(350, 100));

  cpShape *ballShape = cpSpaceAddShape(pe->cpspace, cpCircleShapeNew(pe->bodies[pe->bodyCount], radius, cpvzero));
  cpShapeSetFriction(ballShape, 0.7);
  cpShapeSetElasticity(ballShape, 0.5);
  pe->playerIndex = pe->bodyCount;
  pe->bodyCount++;
}

void addPlayer(planetaryEnvironment * pe, float x, float y)
{
  /*
  add a player-controlled rectangle
  this rectangle will have forces and impulses applied to it based on keystrokes,
  and will be drawn differently than the others because it's a rectangle, not a circle
  */
  printf("Defining player body and shape\n");
  cpFloat width = 20;
  cpFloat height = 43;
  cpFloat radius = 20;
  cpFloat mass = 25;
  cpFloat cornerRadius = 2;
  cpFloat moment = INFINITY;//cpMomentForBox(mass, width, height);
  pe->bodies[pe->bodyCount] = cpSpaceAddBody(pe->cpspace, cpBodyNew(mass, moment));
  cpBodySetPosition(pe->bodies[pe->bodyCount], cpv(x, y));
  cpShape *playerShape = cpSpaceAddShape(pe->cpspace, cpBoxShapeNew(pe->bodies[pe->bodyCount], width, height, cornerRadius));
  cpShapeSetFriction(playerShape, 0.2);
  cpShapeSetElasticity(playerShape, 0.4);
  pe->playerIndex = pe->bodyCount;
  pe->bodyCount++;
  printf("Defined sucessfully!\n");
}

/*polygondata loadPlanet()
{
  USE THIS LATER
}*/
