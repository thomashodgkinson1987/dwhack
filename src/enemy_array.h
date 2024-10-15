#ifndef ENEMY_ARRAY_H
#define ENEMY_ARRAY_H

#include "enemy.h"

#include <stddef.h>

typedef struct enemy_array_impl EnemyArray;

EnemyArray *enemy_array_create(void);

void enemy_array_free(EnemyArray *enemy_array);

size_t enemy_array_get_count(EnemyArray *enemy_array);

size_t enemy_array_get_capacity(EnemyArray *enemy_array);

Enemy **enemy_array_get_data(EnemyArray *enemy_array);

void enemy_array_set_count(EnemyArray *enemy_array, size_t count);

void enemy_array_set_capacity(EnemyArray *enemy_array, size_t capacity);

void enemy_array_set_data(EnemyArray *enemy_array, Enemy **data);

void enemy_array_add(EnemyArray *enemy_array, Enemy *enemy);

Enemy *enemy_array_get(EnemyArray *enemy_array, size_t index);

#endif
