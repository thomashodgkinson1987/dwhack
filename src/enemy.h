#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct enemy_impl Enemy;

enum enemy_direction
{
    ENEMY_NORTH,
    ENEMY_EAST,
    ENEMY_SOUTH,
    ENEMY_WEST
};


Enemy *enemy_create(int x, int y, enum enemy_direction facing, int health, Color color);
void enemy_free(Enemy *enemy);

int enemy_get_x(const Enemy *enemy);
int enemy_get_y(const Enemy *enemy);
enum enemy_direction enemy_get_facing(const Enemy *enemy);
int enemy_get_health(const Enemy *enemy);
Color enemy_get_color(const Enemy *enemy);

void enemy_set_x(Enemy *enemy, int x);
void enemy_set_y(Enemy *enemy, int y);
void enemy_set_facing(Enemy *enemy, enum enemy_direction facing);
void enemy_set_health(Enemy *enemy, int health);
void enemy_set_color(Enemy *enemy, Color color);

#endif
