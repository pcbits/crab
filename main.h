#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro.h>
#include "mappyal.h"

#define WHITE makecol(255, 255, 255)

typedef struct SPRITE
{
    int alive, x, y, width, height, xspeed, yspeed;
} SPRITE;
SPRITE player;
BITMAP *crab;
BITMAP *buffer;
int xoffset = 0;
int yoffset = 0;

#endif
