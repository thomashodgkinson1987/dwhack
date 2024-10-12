#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

enum enemy_direction { ENEMY_NORTH, ENEMY_EAST, ENEMY_SOUTH, ENEMY_WEST };

struct enemy
{
    int x;
    int y;
    enum enemy_direction facing;
    int health;
    Color color;
};

struct enemy enemy_create(int x, int y, enum enemy_direction facing, int health, Color color);
void enemy_free(struct enemy *enemy);

#endif
