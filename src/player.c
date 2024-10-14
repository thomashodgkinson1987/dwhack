#include "player.h"

#include <stdio.h>
#include <stdlib.h>

struct player_impl
{
    int x;
    int y;
    CardinalDirection facing;
    int health;
    Color color;
};

Player *player_create(int x, int y, CardinalDirection facing, int health, Color color)
{
    Player *player = (Player *)malloc(sizeof(struct player_impl));

    if (player == NULL)
    {
        fprintf(stderr, "Error creating player\n");
        exit(1);
    }

    player->x = x;
    player->y = y;
    player->facing = facing;
    player->health = health;
    player->color = color;

    return player;
}

void player_free(Player *player)
{
    free(player);
    player = NULL;
}

int player_get_x(const Player *player) { return player->x; }

int player_get_y(const Player *player) { return player->y; }

CardinalDirection player_get_facing(const Player *player) { return player->facing; }

int player_get_health(const Player *player) { return player->health; }

Color player_get_color(const Player *player) { return player->color; }

void player_set_x(Player *player, int x) { player->x = x; }

void player_set_y(Player *player, int y) { player->y = y; }

void player_set_facing(Player *player, CardinalDirection facing) { player->facing = facing; }

void player_set_health(Player *player, int health) { player->health = health; }

void player_set_color(Player *player, Color color) { player->color = color; }
