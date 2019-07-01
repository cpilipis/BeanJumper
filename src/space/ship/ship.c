#include "ship.h"
#include <stdlib.h>
#include "../../general.h"
#include <math.h>

ship initShips()
{
  ship myShip;
  myShip.body.pos = (Vector2){400, 300};
  myShip.body.vel = (Vector2){0, 0};
  myShip.thrust = 0;
  myShip.maxThrust = 100;
  myShip.body.rot = 0;
  myShip.thrustBuild = 80; //buildup of the thrust. If thrust is acceleration, this is the jerk.
  /*myShip.body.shape.pCount = 3;
  myShip.body.shape.radii[0] = 22;
  myShip.body.shape.radii[1] = 8;
  myShip.body.shape.radii[2] = 8;
  myShip.body.shape.rotOffset[0] = 0;
  myShip.body.shape.rotOffset[1] = MATH_PI/2;
  myShip.body.shape.rotOffset[2] = 3 * MATH_PI/2;
  */
  Vector2 p1 = (Vector2){22, 0};
  Vector2 p2 = (Vector2){0, 8};
  Vector2 p3 = (Vector2){0, -8};

  Vector2 pts [] = {p1, p2, p3};
  myShip.body.shape = initPolygon(pts, 3);
  ship * sp;
  int cnt = myShip.body.shape.pCount;
  unsigned long size = (sizeof(float) * 4 + sizeof(float) * cnt + sizeof(double) * cnt + sizeof(Vector2) * 2 + sizeof(Vector2) * cnt + sizeof(cnt));
  sp = (ship *) malloc (size);
  ship snp = *sp;
  printf("This ship takes %lu bytes of memory\nThe allocated filesize for the pointer ideally is %lu bytes.\nThe actual size of the data the pointer points to is %lu bytes\n", sizeof(myShip), size, sizeof(snp));
  return myShip;
}

void updateShips(ship * s, float dt)
{
  for (int pint = 0; pint < s->body.shape.pCount; pint++)
  {
    s->body.shape.points[pint] = (Vector2)
    {
      s->body.shape.radii[pint] * cos(s->body.rot) + s->body.pos.x,
      s->body.shape.radii[pint] * sin(s->body.rot) + s->body.pos.y
    };
  }

    if (IsKeyDown(KEY_UP) && s->thrust < s->maxThrust)
    {
      s->thrust += s->thrustBuild*dt;
    }
    else if(s->thrust > 0 && !IsKeyDown(KEY_UP))
    {
      s->thrust = 0;
    }
    if (IsKeyDown(KEY_LEFT))
    {
      s->body.rot -= MATH_PI * dt;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
      s->body.rot += MATH_PI * dt;
    }


  Vector2 thrustActual = (Vector2) {s->thrust * cos(s->body.rot), s->thrust * sin(s->body.rot)};
  s->body.vel.x += thrustActual.x * dt;
  s->body.vel.y += thrustActual.y * dt;

  s->body.pos.y += s->body.vel.y * dt;
  s->body.pos.x += s->body.vel.x * dt;
}

void drawShip(ship * s)
{
  /*Vector2 tp1 = (Vector2) {s->body.pos.x + 8 * cos(s->body.rot + 3 * (MATH_PI/2)), s->body.pos.y + 8 * sin(s->body.rot + 3 * (MATH_PI/2))};
  Vector2 tp2 = (Vector2) {s->body.pos.x + 8 * cos(s->body.rot + MATH_PI/2), s->body.pos.y + 8 * sin(s->body.rot + MATH_PI/2)};
  Vector2 tp3 = (Vector2) {s->body.pos.x + 22 * cos(s->body.rot), s->body.pos.y + 22 * sin(s->body.rot)};
  DrawTriangleLines(tp1, tp2, tp3, GREEN);*/

  /*for (int i = 0; i < s->body.shape.pCount; i++)
  {
    //if i+1 is greater than the point count, the next point for the line to go to is point 0.
    int np = i + 1 >= s->body.shape.pCount ? 0 : i+1; //np means Next Point
    //printf("Drawing from p%d to p%d...\n", i, np);
    Vector2 p1 = (Vector2)
      {s->body.pos.x + s->body.shape.radii[i] * cos(s->body.rot + s->body.shape.rotOffset[i]),
      s->body.pos.y + s->body.shape.radii[i] * sin(s->body.rot + s->body.shape.rotOffset[i])};
    Vector2 p2 = (Vector2)
      {s->body.pos.x + s->body.shape.radii[np] * cos(s->body.rot + s->body.shape.rotOffset[np]),
      s->body.pos.y + s->body.shape.radii[np] * sin(s->body.rot + s->body.shape.rotOffset[np])};
    DrawLineV(p1, p2, WHITE);
    DrawPixelV(s->body.shape.points[i], RED);
  }*/
  drawPolygon(s->body.pos, s->body.rot, &s->body.shape);
}

void drawShipHud(ship * s)
{
  //thrust indicator
  DrawRectangleV((Vector2){40, 500 - s->thrust * 3}, (Vector2){30, s->thrust * 3}, RED);
  DrawLineV((Vector2){40, 500}, (Vector2){30, 500}, RED);
  DrawLineV((Vector2){40, 500 - s->maxThrust * 3}, (Vector2){30, 500 - s->maxThrust * 3}, RED);
  DrawText("Thrust", 10, 525, 16, RED);
  char thrustStr[30];
  sprintf(thrustStr, "%f", s->thrust);
  DrawText(thrustStr, 42, 490, 10, BLACK);
  //TODO: velocity indicator
  double velangle = atan(s->body.vel.y/s->body.vel.x);
  velangle = s->body.vel.x < 0 ? velangle + MATH_PI : velangle;
  float velLen = sqrt(s->body.vel.x * s->body.vel.x + s->body.vel.y * s->body.vel.y);
  //sometimes the actual thrust line is so short because the ship is moving slow that the player can't see their direction of movement
  //So, there's two. One at a fixed length (the blue one), and one that changes length based on speed, drawn one on top of another.
  DrawLineV((Vector2){400, 300}, (Vector2){400 + (cos(velangle) * 15), 300 + (sin(velangle) * 15)}, BLUE);
  DrawLineV((Vector2){400, 300}, (Vector2){400 + (cos(velangle) * velLen/10), 300 + (sin(velangle) * velLen/10)}, GREEN);
  //I'm reusing Thrust Str to print the velocity of the ship. Why not? Just put text on screen with it, wipe it, and reuse it.
  sprintf(thrustStr, "%f", velLen);
  DrawText(thrustStr, 430, 320, 10, GREEN);
}
