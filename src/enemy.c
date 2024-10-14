#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>

struct enemy_impl
{
    int x;
    int y;
    CardinalDirection facing;
    int health;
    Color color;
};

Enemy *enemy_create(int x, int y, CardinalDirection facing, int health, Color color)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(struct enemy_impl));

    if (enemy == NULL)
    {
        fprintf(stderr, "Error creating enemy\n");
        exit(1);
    }

    enemy->x = x;
    enemy->y = y;
    enemy->facing = facing;
    enemy->health = health;
    enemy->color = color;

    return enemy;
}

void enemy_free(Enemy *enemy)
{
    free(enemy);
    enemy = NULL;
}

int enemy_get_x(const Enemy *enemy) { return enemy->x; }

int enemy_get_y(const Enemy *enemy) { return enemy->y; }

CardinalDirection enemy_get_facing(const Enemy *enemy) { return enemy->facing; }

int enemy_get_health(const Enemy *enemy) { return enemy->health; }

Color enemy_get_color(const Enemy *enemy) { return enemy->color; }

void enemy_set_x(Enemy *enemy, int x) { enemy->x = x; }

void enemy_set_y(Enemy *enemy, int y) { enemy->y = y; }

void enemy_set_facing(Enemy *enemy, CardinalDirection facing) { enemy->facing = facing; }

void enemy_set_health(Enemy *enemy, int health) { enemy->health = health; }

void enemy_set_color(Enemy *enemy, Color color) { enemy->color = color; }
