#include "enemy.h"

struct enemy enemy_create(int x, int y, EnemyDirection facing, int health, Color color)
{
    struct enemy enemy = (struct enemy){
        .x = x,
        .y = y,
        .facing = facing,
        .health = health,
        .color = color};

    return enemy;
}

void enemy_free(struct enemy *enemy)
{
    *enemy = (struct enemy){0};
}
