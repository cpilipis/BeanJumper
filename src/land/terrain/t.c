#include "t.h"
#include <chipmunk/chipmunk.h>
#include <math.h>

terraindata initTerrain()
{
  terraindata td;
  td.phNum = 50;
  td.planetWidth = 800;
  float phs[] = {500.0f, 497.7f, 494.2f, 480.0f, 483.3f, 485.5f, 479.9f, 470.0f, 485.4f, 500.0f, 510.0f, 522.0f, 488.0f, 480.0f, 476.0f, 460.0f, 466.0f, 460.0f, 461.0f, 463.0f, 462.0f, 450.0f, 453.0f, 455.0f, 420.0f, 430.0f, 450.0f, 465.0f, 473.0f, 485.0f, 490.0f, 500.0f, 500.0f, 497.7f, 494.2f, 480.0f, 483.3f, 485.5f, 460.0f, 400.0f, 460.0f, 440.0f, 432.0f, 420.0f, 450.0f, 460.0f, 470.0f, 480.0f, 500.0f, 500.0f};
  for (int i = 0; i < td.phNum; i++)
  {
    td.pointHeights[i] = phs[i];
  }
  return td;
}
