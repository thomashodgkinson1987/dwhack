#include "enemy.h"

#include <stdlib.h>

struct enemy_impl
{
    int x;
    int y;
    enum enemy_direction facing;
    int health;
    Color color;
};

Enemy *enemy_create(int x, int y, enum enemy_direction facing, int health, Color color)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(struct enemy_impl));

    if (enemy != NULL)
    {
        enemy->x = x;
        enemy->y = y;
        enemy->facing = facing;
        enemy->health = health;
        enemy->color = color;
    }

    return enemy;
}

void enemy_free(Enemy *enemy)
{
    if (enemy != NULL)
    {
        free(enemy);
    }
}

int enemy_get_x(const Enemy *enemy) { return enemy->x; }
int enemy_get_y(const Enemy *enemy) { return enemy->y; }
enum enemy_direction enemy_get_facing(const Enemy *enemy) { return enemy->facing; }
int enemy_get_health(const Enemy *enemy) { return enemy->health; }
Color enemy_get_color(const Enemy *enemy) { return enemy->color; }

void enemy_set_x(Enemy *enemy, int x) { enemy->x = x; }
void enemy_set_y(Enemy *enemy, int y) { enemy->y = y; }
void enemy_set_facing(Enemy *enemy, enum enemy_direction facing) { enemy->facing = facing; }
void enemy_set_health(Enemy *enemy, int health) { enemy->health = health; }
void enemy_set_color(Enemy *enemy, Color color) { enemy->color = color; }
