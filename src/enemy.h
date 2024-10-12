#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

enum enemy_direction
{
    ENEMY_NORTH,
    ENEMY_EAST,
    ENEMY_SOUTH,
    ENEMY_WEST
};

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

int enemy_get_x(const struct enemy *enemy);
int enemy_get_y(const struct enemy *enemy);
enum enemy_direction enemy_get_facing(const struct enemy *enemy);
int enemy_get_health(const struct enemy *enemy);
Color enemy_get_color(const struct enemy *enemy);

void enemy_set_x(struct enemy *enemy, int x);
void enemy_set_y(struct enemy *enemy, int y);
void enemy_set_facing(struct enemy *enemy, enum enemy_direction facing);
void enemy_set_health(struct enemy *enemy, int health);
void enemy_set_color(struct enemy *enemy, Color color);

#endif
