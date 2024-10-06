#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

struct enemy
{
    int x;
    int y;
    int f;
    Color color;
};

struct enemy enemy_create(int x, int y, int f, Color color);
void enemy_free(struct enemy *enemy);

#endif
