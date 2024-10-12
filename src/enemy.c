#include "enemy.h"

struct enemy enemy_create(int x, int y, int f, Color color)
{
    struct enemy enemy = (struct enemy){
        .x = x,
        .y = y,
        .f = f,
        .color = color};

    return enemy;
}

void enemy_free(struct enemy *enemy)
{
    *enemy = (struct enemy){0};
}
