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
    enemy->x = 0;
    enemy->y = 0;
    enemy->f = 0;
    enemy->color = BLANK;
}
