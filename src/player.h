#ifndef PLAYER_H
#define PLAYER_H

#include "cardinal_directions.h"

#include "raylib.h"

typedef struct player_impl Player;

Player *player_create(int x, int y, CardinalDirection facing, int health, Color color);

void player_free(Player *player);

int player_get_x(const Player *player);

int player_get_y(const Player *player);

CardinalDirection player_get_facing(const Player *player);

int player_get_health(const Player *player);

Color player_get_color(const Player *player);

void player_set_x(Player *player, int x);

void player_set_y(Player *player, int y);

void player_set_facing(Player *player, CardinalDirection facing);

void player_set_health(Player *player, int health);

void player_set_color(Player *player, Color color);

#endif
