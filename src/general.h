#ifndef GENERAL_H
#define GENERAL_H
#include <raylib.h>

typedef struct polygondata
{
unsigned int pCount; //The # of points on the polygon will always be positive
Vector2 points [500];
float radii [500];
double rotOffset [500]; //polygon point coordinates stored in polar, not cartesian.
} polygondata;

typedef struct tridata
{
Vector2 points [3];
float radii [3];
double rotOffset [3];
} tridata;

//Tridata is basically polygondata but for triangles, to save memory.
//sizeof(polygondata) = 10,008 bytes
//sizeof(tridata) = 64 bytes
//A polygon divided into tri datas will take up less space than the total structure of polygon data
//however, a polygondata with 500 points will still be smaller than the tridata equivatlent composition

typedef struct polytridata
{
unsigned int tCount;
tridata triangles[498];
polygondata * parentPoly;
} polytridata;

typedef struct physbody
{
  Vector2 pos;
  Vector2 vel;
  float rot;
  polygondata shape;
} physbody;

polygondata initPolygon(Vector2 points[], unsigned int pCount);
void drawPolygon(Vector2 pos, double rot, polygondata * p);
void drawPolyTri(Vector2 pos, double rot, polytridata * ptd);
tridata polygonToTri(polygondata * poly);

int mathsign(int i);
int orientLines(Vector2 * p1, Vector2 * p2, Vector2 * p3);
int lineIntersectTest(Vector2 * p1, Vector2 * p2, Vector2 * q1, Vector2 * q2);
polytridata polygonConvexSplit(polygondata * polyOriginal);
int collisionCheck(physbody b1, physbody b2);

#include "general.c"
#endif
