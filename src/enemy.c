#include "enemy.h"

struct enemy enemy_create(int x, int y, enum enemy_direction facing, int health, Color color)
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

int enemy_get_x(const struct enemy *enemy) { return enemy->x; }
int enemy_get_y(const struct enemy *enemy) { return enemy->y; }
enum enemy_direction enemy_get_facing(const struct enemy *enemy) { return enemy->facing; }
int enemy_get_health(const struct enemy *enemy) { return enemy->health; }
Color enemy_get_color(const struct enemy *enemy) { return enemy->color; }

void enemy_set_x(struct enemy *enemy, int x) { enemy->x = x; }
void enemy_set_y(struct enemy *enemy, int y) { enemy->y = y; }
void enemy_set_facing(struct enemy *enemy, enum enemy_direction facing) { enemy->facing = facing; }
void enemy_set_health(struct enemy *enemy, int health) { enemy->health = health; }
void enemy_set_color(struct enemy *enemy, Color color) { enemy->color = color; }
