#include "ms.h"

void updateSpace(ship * s, float dt)
{
  updateShips(s, dt);
  //printf("%lu bytes, %lu bytes, %lu bytes, %lu bytes\n", sizeof(Vector2), sizeof(polygondata), sizeof(tridata), sizeof(physbody));

}
void drawSpace(ship * s, planet p[], Camera2D * spacecam, polygondata * test, polytridata * poopoo)
{
  spacecam->offset.x = -1 * s->body.pos.x + 400;
  spacecam->offset.y = -1 * s->body.pos.y + 300;
  BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(*spacecam);
      drawPolygon((Vector2){0, 0}, 0, test);
      drawPolyTri((Vector2){0, 0}, 0, poopoo);
      drawShip(s);
      for (int pc = 0; pc < 5; pc++)
      {
        drawPlanet(&p[pc]);
        DrawLineV(s->body.pos, p[pc].pos, RED);
      }
    EndMode2D();
    char tempstr[36];
    sprintf(tempstr, "FPS: %d", GetFPS());
    DrawText(tempstr, 20, 20, 16, RED);
    drawShipHud(s);
  EndDrawing();
}
