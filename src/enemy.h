#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef enum { ENEMY_NORTH, ENEMY_EAST, ENEMY_SOUTH, ENEMY_WEST } EnemyDirection;

struct enemy
{
    int x;
    int y;
    EnemyDirection facing;
    int health;
    Color color;
};

struct enemy enemy_create(int x, int y, EnemyDirection facing, int health, Color color);
void enemy_free(struct enemy *enemy);

#endif
