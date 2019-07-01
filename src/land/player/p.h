#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

typedef struct creatureLimits
{
  float health;
  float maxHealth; //self explanatory
  float stamina;
  float maxStamina; //Used for special abilities, like sprinting or flying, that have to be limited
  float hunger;
  float maxHunger; //Starts at the max, ticks down to zero. Creature takes damage and starves at 0.
  //Maybe it'll tick down faster to replenish stamina?
  //Maybe stamina can't recover if hunger number is too low?
  float idleHungerDrain;
  float maxHungerDrain; //values to clamp hunger drain over time or over physical exertion
} creatureLimits;

typedef struct creature
{
  physbody body;
  float walkspeed;
  float jumpheight;
  creatureLimits cl;
} creature;


creature initPlayer();

#include "p.c"
#endif
