#include "planet.h"
#include "math.h"

#include <raylib.h>

planet * initPlanets()
{
  static planet p[5];
  p[0].pos = (Vector2) {0, 0};
  p[0].radius = 160;
  p[0].c = GREEN;
  p[0].td = initTerrain();

  for (int pc = 1; pc < 5; pc++)
  {
    p[pc].pos = (Vector2) {(float) GetRandomValue(-2000, 2000), (float) GetRandomValue(-2000, 2000)};
    p[pc].radius = (float) GetRandomValue(50, 225);
    int pccolorpicker = (int) GetRandomValue(0, 5);
    switch(pccolorpicker)
    {
      case 0:
        p[pc].c = PURPLE;
        break;
      case 1:
        p[pc].c = ORANGE;
        break;
      case 2:
        p[pc].c = BLUE;
        break;
      case 3:
        p[pc].c = GRAY;
        break;
      case 4:
        p[pc].c = YELLOW;
        break;
      case 5:
        p[pc].c = GREEN;
        break;
    }
  p[pc].td = initTerrain();
  }
  return p;
}

void drawPlanet(planet * p)
{
  DrawCircleLines(p->pos.x, p->pos.y, p->radius, p->c);
}
