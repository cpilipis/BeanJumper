#include <math.h>
#include "general.h"

polygondata initPolygon(Vector2 points[], unsigned int pCount)
{
  polygondata p;
  p.pCount = pCount;
  for (unsigned int f = 0; f < pCount; f++)
  {
    p.points[f] = points[f];
  }
  for (unsigned int r = 0; r < pCount; r++)
  {
    p.radii[r] = sqrt(p.points[r].x*p.points[r].x + p.points[r].y*p.points[r].y);
    p.rotOffset[r] = atan(p.points[r].y/p.points[r].x);
    if (p.points[r].x < 0){p.rotOffset[r] = p.rotOffset[r] + MATH_PI;}
    //printf("%f\n", p.rotOffset[r]);
    //printf("%f\n", (p.points[r].x/p.points[r].y));
  }
  return p;
}
tridata initTriangle(Vector2 points[])
{
  tridata t;
  for (unsigned int f = 0; f < 3; f++)
  {
    t.points[f] = points[f];
  }
  for (unsigned int r = 0; r < 3; r++)
  {
    t.radii[r] = sqrt(t.points[r].x*t.points[r].x + t.points[r].y*t.points[r].y);
    t.rotOffset[r] = atan(t.points[r].y/t.points[r].x);
    if (t.points[r].x < 0){t.rotOffset[r] = t.rotOffset[r] + MATH_PI;}
    //printf("%f\n", t.rotOffset[r]);
    //printf("%f\n", (t.points[r].x/t.points[r].y));
  }
  return t;
}

void drawPolygon(Vector2 pos, double rot, polygondata * p)
{
  for (int i = 0; i < p->pCount; i++)
  {
    //if i+1 is greater than the point count, the next point for the line to go to is point 0.
    int np = i + 1 >= p->pCount ? 0 : i+1; //np means Next Point
    //printf("Drawing from p%d to p%d...\n", i, np);
    Vector2 p1 = (Vector2)
      {pos.x + p->radii[i] * cos(rot + p->rotOffset[i]),
      pos.y + p->radii[i] * sin(rot + p->rotOffset[i])};
    Vector2 p2 = (Vector2)
      {pos.x + p->radii[np] * cos(rot + p->rotOffset[np]),
      pos.y + p->radii[np] * sin(rot + p->rotOffset[np])};
    DrawLineV(p1, p2, WHITE);
    DrawPixelV(p->points[i], RED);
  }
}

void drawPolyTri(Vector2 pos, double rot, polytridata * ptd)
{
  for(int a = 0; a < ptd->tCount; a++)
  {
    Vector2 tPointsDraw [] = {ptd->triangles[a].points[0], ptd->triangles[a].points[1], ptd->triangles[a].points[2]};
    /*for(int e = 0; e < 3; e++)
    {
      printf("Triangle %d point %d coordinates at (%f, %f).\n", a, e, tPointsDraw[e].x, tPointsDraw[e].y);
    }*/
    DrawTriangleLines(tPointsDraw[0], tPointsDraw[1], tPointsDraw[2], GREEN);
  }
}

//this function returns the sign of an integer (1, -1, or 0)
int mathsign(int i) //I wish C's standard math lib came with this function. Until then, this'll do.
{
  if (i == 0) {return 0;}
  return i > 0 ? 1 : -1;
}

//this function takes 3 points and returns the orientation from point 1 to point 3
//used later for checking if two lines lines intersect
//returns 0 if collinear, 1 if clockwise, -1 if counterclockwise.
int orientLines(Vector2 * p1, Vector2 * p2, Vector2 * p3)
{
  int val = ((p2->y - p1->y)*(p3->x - p2->x) - (p3->y - p2->y)*(p2->x - p1->x));
  return mathsign(val);
}

//returns 1 on intersection, 0 if there is no intersection
int lineIntersectTest(Vector2 * p1, Vector2 * p2, Vector2 * q1, Vector2 * q2)
{
  if (orientLines(p1, p2, q1) != orientLines(p1, p2, q2) && orientLines(q1, q2, p1) != orientLines(q1, q2, p2)){return 1;}
  return 0;
}

tridata polygonToTri(polygondata * poly)
{
  if (poly->pCount > 3){printf("MAJOR ERROR: tried to convert non-triangle polygon into triangle!\n");}
  tridata tri;
  for (int g = 0; g < 2; g++)
  {
    tri.points[g] = poly->points[g];
    tri.radii[g] = poly->radii[g];
    tri.rotOffset[g] = poly->rotOffset[g];
  }
  return tri;
}


//split a non-convex polygon into a triangles, returning a
polytridata polygonConvexSplit(polygondata * polyOriginal)
{
  polytridata ptd;
  ptd.parentPoly = polyOriginal;
  //define a polygon based on polyOriginal. We will whittle this one down while we take care of the triangles.
  //we have to whittle this one down because we don't want to mess with the original. We're only whittling it to separate the parts to return them all.
  polygondata newPoly = *polyOriginal;
  int earcount = 0;
  while (newPoly.pCount > 3)
  {
    //pick a point. We'll start with point 0 and work our way up
    //I could increment it on each continue statement, or I can increment it on the start of each while loop iteration
    //I chose the latter, and set eartest to -1 to compensate
    int eartest = -1;
    int earsuccess = 0;
    Vector2 earpoint;
    int n1i;
    int n2i;
    Vector2 n1;
    Vector2 n2;

    while (earsuccess == 0)
    {
      eartest++;
      earpoint = newPoly.points[eartest];
      n1i = eartest - 1;
      if (n1i < 0){n1i = newPoly.pCount - 1;}
      n2i = eartest + 1;
      n1 = newPoly.points[n1i];
      n2 = newPoly.points[n2i];
      //n is for neighbor
      //these store the neighboring points
      //n1i and n2i are indices
      //side point: both "indexes" and "indices" are acceptable plural forms of the word "index".
      //find the minimum y value of the points on the polygon
      //I'll need these neighbors later

      float min = newPoly.points[0].y;
      for (int f = 1; f < newPoly.pCount; f++)
      {
        float thisY = newPoly.points[f].y;
        if (min > thisY){min = thisY;}
      }
      //I need to check if the midpoint of the line between n1 and n2 is in the polygon
      //if not, this isn't a valid triangle of the polygon
      Vector2 midpoint = (Vector2){(n2.x + n1.x)/2, (n2.y + n1.y)/2};

      Vector2 toppoint = midpoint;
      toppoint.y = min;
      //count how many lines this midpoint intersects with, to determine if it's in the polygon or not
      unsigned int intersections = 0;
      for (int l = 0; l < newPoly.pCount; l++)
      {
        int lastP = l - 1;
        if (lastP < 0){lastP = newPoly.pCount - 1;}
        intersections = intersections + lineIntersectTest(&midpoint, &toppoint, &newPoly.points[lastP], &newPoly.points[l]);
      }
      if (intersections%2 == 0){continue;} //this midpoint isn't in the polygon. Look for a new ear.
      /*
      check if there are any points from the rest of the polygon in this triangle.
      if so, this triangle inaccurately represents the triangle and we need to forget about it, because it's an inacceptable ear
      We can still segment it apart, but we need to use a different ear.
      there's a multitude of reasons for the weird conditions for this for loop:
      - We shouldn't check if the verticies of the triangle are in the triangle
      - When checking each point on the polygon, we're going to loop back around to 0, so a greater than/less than sign will fail because we won't check every single points
      - We need to use the ternary operator in the for loop to loop o back to 0 if it becomes too big.
      */
      int chipped = 0;
      for (int o = n2i; o != n1i; o >= newPoly.pCount ? o = 0 : o++)
      {
        //good thing Raylib comes with a really cool and easy collision function for checking if a point's in a triangle!
        if(CheckCollisionPointTriangle(newPoly.points[o], n1, earpoint, n2)){chipped = 1;}
      }
      if (chipped == 1){continue;}

      //looks like this one's a winner if we've gotten this far without hitting a "continue"!
      earsuccess = 1;
    }
    Vector2 triPoints[] = {n1, earpoint, n2};
    ptd.triangles[earcount] = initTriangle(triPoints);
    //We need to remove the ear from the polygon, so we leave everything before the ear alone and set the ear and everything after to the one in front of it
    //the point count is decreased and the last one is manually clipped to (0, 0).
    //We don't need to touch the last one, but if we do, any bugs that cause functions to access the last one will make it plainly obvious something's wrong when we go to draw the polygon
    for (int h = 0; h < newPoly.pCount - 1; h++)
    {
      if (h < eartest){continue;}
      newPoly.points[h] = newPoly.points[h + 1];
    }
    newPoly.points[newPoly.pCount - 1] = (Vector2){0, 0}; //FINISH IT
    newPoly.pCount--;
    /*printf("New ear at %f, %f\n", earpoint.x, earpoint.y);
    printf("Neighbor one at %f, %f\n", n1.x, n1.y);
    printf("Neighbor two at %f, %f\n", n2.x, n2.y);*/
    printf("Triangle number %d\n", earcount);
    earcount++;
    //We can go back around now. This will stop when the new polygon only has 3 points, and thus, is a triangle
  }
  //BUT WAIT! While the while loop is finally over, the final triangle we're left with isn't a part of the collection of the other triangles
  //We should add it to the thingy and return the thingy!
  Vector2 triPoints[] = {newPoly.points[0], newPoly.points[1], newPoly.points[2]};
  ptd.triangles[earcount] = initTriangle(triPoints);
  ptd.tCount = earcount + 1;
  printf("Triangle number %d\n", earcount);
  return ptd; //It's finally over . . .
}
