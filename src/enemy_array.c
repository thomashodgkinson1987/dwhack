#include "enemy_array.h"

#include <stdio.h>
#include <stdlib.h>

struct enemy_array_impl
{
    size_t count;
    size_t capacity;
    Enemy **data;
};

EnemyArray *enemy_array_create(void)
{
    EnemyArray *enemy_array = calloc(1, sizeof *enemy_array);

    if (enemy_array == NULL)
    {
        fprintf(stderr, "Error creating enemy array\n");
        exit(1);
    }

    *enemy_array = (EnemyArray){0};

    enemy_array->count = 0;
    enemy_array->capacity = 1;
    enemy_array->data = calloc(enemy_array->capacity, sizeof *enemy_array->data);

    if (enemy_array->data == NULL)
    {
        fprintf(stderr, "Error creating enemy array data\n");
        exit(1);
    }

    for (size_t i = 0; i < enemy_array->capacity; ++i)
    {
        enemy_array->data[i] = NULL;
    }

    return enemy_array;
}

void enemy_array_free(EnemyArray *enemy_array)
{
    free(enemy_array->data);
    free(enemy_array);
    enemy_array = NULL;
}

size_t enemy_array_get_count(EnemyArray *enemy_array) { return enemy_array->count; }

size_t enemy_array_get_capacity(EnemyArray *enemy_array) { return enemy_array->capacity; }

Enemy **enemy_array_get_data(EnemyArray *enemy_array) { return enemy_array->data; }

void enemy_array_set_count(EnemyArray *enemy_array, size_t count) { enemy_array->count = count; }

void enemy_array_set_capacity(EnemyArray *enemy_array, size_t capacity) { enemy_array->capacity = capacity; }

void enemy_array_set_data(EnemyArray *enemy_array, Enemy **data) { enemy_array->data = data; }

void enemy_array_add(EnemyArray *enemy_array, Enemy *enemy)
{
    if (enemy_array->count == enemy_array->capacity)
    {
        Enemy **ptr = realloc(enemy_array->data, sizeof *enemy_array->data * enemy_array->capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating enemy array data\n");
            exit(1);
        }
        for (size_t i = enemy_array->capacity; i < enemy_array->capacity * 2; ++i)
        {
            ptr[i] = NULL;
        }
        enemy_array->capacity *= 2;
        enemy_array->data = ptr;
    }

    enemy_array->data[enemy_array->count++] = enemy;
}

Enemy *enemy_array_get(EnemyArray *enemy_array, size_t index)
{
    return enemy_array->data[index];
}
