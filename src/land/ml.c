#include "ml.h"

void updateLand (planetaryEnvironment * pe, float dt)
{
  if(pe->playerIndex > -1) //player index
  {
    //printf("Checking the keys\n");
    float speed = 2500;
    float jumppower = 3000;
    if(IsKeyDown(KEY_J))
    {
      speed = speed * 2;
    }
    if(IsKeyDown(KEY_LEFT))
    {
      cpBodyApplyForceAtWorldPoint(pe->bodies[pe->playerIndex], cpv(-speed, 0), cpBodyGetPosition(pe->bodies[pe->playerIndex]));
      //applying the force
      printf("Going left\n");
    }
    if(IsKeyDown(KEY_RIGHT))
    {
      cpBodyApplyForceAtWorldPoint(pe->bodies[pe->playerIndex], cpv(speed, 0), cpBodyGetPosition(pe->bodies[pe->playerIndex]));
      printf("Going right\n");
    }
    if(IsKeyPressed(KEY_UP))
    {
      cpBodyApplyImpulseAtWorldPoint(pe->bodies[pe->playerIndex], cpv(0, -jumppower), cpBodyGetPosition(pe->bodies[pe->playerIndex]));
      printf("Going up\n");
    }

  }
  cpSpaceStep(pe->cpspace, dt);
}

void drawLand(planetaryEnvironment * pe)
{
  terraindata tdshort = pe->parentPlanet->td;
  float tdSpacing = tdshort.planetWidth/tdshort.phNum;

  BeginDrawing();
    ClearBackground(pe->sc);

    for (int tc = 0; tc < tdshort.phNum - 1; tc++)
    {
      Vector2 startpoint = (Vector2){tdSpacing * tc, tdshort.pointHeights[tc]};
      Vector2 endpoint = (Vector2){tdSpacing * (tc + 1), tdshort.pointHeights[tc+1]};
      DrawLineV(startpoint, endpoint, pe->gc);
    }
    for (int bc = 0; bc < pe->bodyCount; bc++)
    {
	  if (bc != pe->playerIndex)
	  {
        Color dc = RED;
        cpVect pos = cpBodyGetPosition(pe->bodies[bc]);
        cpVect vel = cpBodyGetVelocity(pe->bodies[bc]);
		cpFloat angle = cpBodyGetAngle(pe->bodies[bc]);
        DrawCircleLines(pos.x, pos.y, 20, dc);
        DrawLineV((Vector2){pos.x, pos.y}, (Vector2){pos.x + 20 * cos(angle), pos.y + 20 * sin(angle)}, BLACK);
  	  
	  }
	  else
	  {
		Color dc = BLUE;
		cpVect pos = cpBodyGetPosition(pe->bodies[bc]);
		cpVect vel = cpBodyGetVelocity(pe->bodies[bc]);
		cpFloat angle = cpBodyGetAngle(pe->bodies[bc]);
	
		DrawRectangleV((Vector2){pos.x - 10, pos.y - 43/2}, (Vector2){20, 43}, dc);
	  }
	}
    char tempstr[36];
    sprintf(tempstr, "FPS: %d", GetFPS());
    DrawText(tempstr, 20, 20, 16, RED);

  EndDrawing();
}
