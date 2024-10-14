#ifndef ENEMY_H
#define ENEMY_H

#include "cardinal_directions.h"

#include "raylib.h"

typedef struct enemy_impl Enemy;

Enemy *enemy_create(int x, int y, CardinalDirection facing, int health, Color color);

void enemy_free(Enemy *enemy);

int enemy_get_x(const Enemy *enemy);

int enemy_get_y(const Enemy *enemy);

CardinalDirection enemy_get_facing(const Enemy *enemy);

int enemy_get_health(const Enemy *enemy);

Color enemy_get_color(const Enemy *enemy);

void enemy_set_x(Enemy *enemy, int x);

void enemy_set_y(Enemy *enemy, int y);

void enemy_set_facing(Enemy *enemy, CardinalDirection facing);

void enemy_set_health(Enemy *enemy, int health);

void enemy_set_color(Enemy *enemy, Color color);

#endif
