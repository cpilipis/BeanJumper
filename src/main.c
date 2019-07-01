//The basics
#define MATH_PI 3.14159265358979
#define SPACEMODE 0
#define PLANETMODE 1
#include <stdio.h>
#include <stdlib.h>
//Math
#include <math.h>
//Raylib, the library powering this project
//Provides window handling, input, audio and drawing, all sorts of stuff you need in a game
//Even comes with 3D redering via OpenGL
#include <raylib.h>

//Chipmunk Physics, the library powering the physics on each planet
#include <chipmunk/chipmunk.h>

//The headers for the other source files
#include "general.h"

#include "space/ms.h"
/* "ms" is for "main space" source code file
//#include "space/ship/ship.h"
//#include "space/planet/planet.h"
*/
#include "land/ml.h"
#include "land/terrain/t.h"
#include "land/player/p.h"
#include "land/terrain/t.h"
#include "land/terrain/pe.h"
//void updateSpace(ship * s);

//void updateLand(planet * p);

//void drawLand(planet * p);

//void drawSpace(ship * s, planet p[], Camera2D * spacecam, polygondata * test, polytridata * poopoo);

int main()
{
  int screenWidth = 800;
  int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Bean Jumper");
  //SetTargetFPS(60);

  //initialize the game
  int gamemode = SPACEMODE;
  int gmSwitch = 0;
  ship alpha = initShips();
  planet * alphaworlds;
  cpBody * alphaball;
  alphaworlds = initPlanets();
  planetaryEnvironment alphaland;
  Camera2D spacecam;

  spacecam.target = alpha.body.pos;
  spacecam.offset = (Vector2){0, 0};
  spacecam.rotation = 0.0f;
  spacecam.zoom = 1.0f;

  Vector2 m0 = (Vector2){-100, -100};
  Vector2 m1 = (Vector2){-200, 20};
  Vector2 m2 = (Vector2){-50, 112};
  Vector2 m3 = (Vector2){80, 76};
  Vector2 m4 = (Vector2){120, 90};
  Vector2 m5 = (Vector2){200, 167};
  Vector2 m6 = (Vector2){250, 100};

  Vector2 mPoints[] = {m0, m1, m2, m3, m4, m5, m6};
  polygondata mPolygon = initPolygon(mPoints, 7);
  polytridata mPolySplit = polygonConvexSplit(&mPolygon);
  printf("orientations: %d, %d, %d\n", orientLines(&m1, &m2, &m3), orientLines(&m1, &m3, &m5), orientLines(&m1, &m2, &m4));
  printf("line intersections: %d, %d, %d\n", lineIntersectTest(&m1, &m2, &m3, &m4), lineIntersectTest(&m1, &m3, &m2, &m4), lineIntersectTest(&m1, &m2, &m6, &m4));


  while(!WindowShouldClose())
  {
    float dt = GetFrameTime();
    if(IsKeyReleased(KEY_DOWN))
    {
      gmSwitch = 0;
    }
    if (gamemode == SPACEMODE)
    {
      //typical space loop
      updateSpace(&alpha, dt);
      drawSpace(&alpha, alphaworlds, &spacecam, &mPolygon, &mPolySplit);

      //code here to check if we need to land on a planet and switch gamemodes
      if(IsKeyPressed(KEY_DOWN) && gmSwitch == 0)
      {
        //gamemode = PLANETMODE;
        printf("Trying to land!\n");
        int planetSelection = -1;
        for (int e = 0; e < 5; e++)
        {
          float xdist = (alpha.body.pos.x - alphaworlds[e].pos.x);
          float ydist = (alpha.body.pos.y - alphaworlds[e].pos.y);
          float dist = sqrt(xdist * xdist + ydist * ydist);
          if(dist < alphaworlds[e].radius)
          {
            planetSelection = e;
            break;
            printf("Player is inside of planet %d.\n", e);
          }
        }
        if(planetSelection > -1)
        {
          printf("Switching gamemodes...\n");
          gamemode = PLANETMODE;
          alphaland = initPlanetEnv(&alphaworlds[planetSelection], 100, 0.8, RAYWHITE);
          addBall(&alphaland, 350, 200);
          addPlayer(&alphaland, 450, 400);
          gmSwitch = 1;
        }
      }
    }
    else if (gamemode == PLANETMODE)
    {
      updateLand(&alphaland, dt);
      drawLand(&alphaland);
      //printf("Welcome to PLANETMODE\n");

      //testing if we need to go back to space mode
      if(IsKeyPressed(KEY_DOWN) && gmSwitch == 0)
      {
        gamemode = SPACEMODE;
        printf("Switching to spacemode . . . \n");
        gmSwitch = 1;
      }
    }
  }
  CloseWindow();
}
