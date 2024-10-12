#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct player_impl Player;

enum player_direction
{
    PLAYER_NORTH = 0,
    PLAYER_EAST = 1,
    PLAYER_SOUTH = 2,
    PLAYER_WEST = 3
};

Player *player_create(int x, int y, enum player_direction facing, int health, Color color);

void player_free(Player *player);

int player_get_x(const Player *player);

int player_get_y(const Player *player);

enum player_direction player_get_facing(const Player *player);

int player_get_health(const Player *player);

Color player_get_color(const Player *player);

void player_set_x(Player *player, int x);

void player_set_y(Player *player, int y);

void player_set_facing(Player *player, enum player_direction facing);

void player_set_health(Player *player, int health);

void player_set_color(Player *player, Color color);

#endif
