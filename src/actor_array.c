#include "actor_array.h"

#include <stdio.h>
#include <stdlib.h>

struct actor_array_impl
{
    size_t count;
    size_t capacity;
    Actor **data;
};

ActorArray *actor_array_create(void)
{
    ActorArray *actor_array = malloc(sizeof *actor_array);

    if (actor_array == NULL)
    {
        fprintf(stderr, "Error creating actor array\n");
        exit(1);
    }

    *actor_array = (ActorArray){0};

    actor_array->count = 0;
    actor_array->capacity = 1;
    actor_array->data = malloc(sizeof *actor_array->data * actor_array->capacity);

    if (actor_array->data == NULL)
    {
        fprintf(stderr, "Error creating actor array data\n");
        exit(1);
    }

    for (size_t i = 0; i < actor_array->capacity; ++i)
    {
        actor_array->data[i] = NULL;
    }

    return actor_array;
}

void actor_array_free(ActorArray *actor_array)
{
    free(actor_array->data);
    free(actor_array);
    actor_array = NULL;
}

// getters

size_t actor_array_get_count(ActorArray *actor_array) { return actor_array->count; }

size_t actor_array_get_capacity(ActorArray *actor_array) { return actor_array->capacity; }

Actor **actor_array_get_data(ActorArray *actor_array) { return actor_array->data; }

// setters

void actor_array_set_count(ActorArray *actor_array, size_t count) { actor_array->count = count; }

void actor_array_set_capacity(ActorArray *actor_array, size_t capacity) { actor_array->capacity = capacity; }

void actor_array_set_data(ActorArray *actor_array, Actor **data) { actor_array->data = data; }

// helpers

void actor_array_add(ActorArray *actor_array, Actor *actor)
{
    if (actor_array->count == actor_array->capacity)
    {
        Actor **ptr = realloc(actor_array->data, sizeof *actor_array->data * actor_array->capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating actor array data\n");
            exit(1);
        }
        for (size_t i = actor_array->capacity; i < actor_array->capacity * 2; ++i)
        {
            ptr[i] = NULL;
        }
        actor_array->capacity *= 2;
        actor_array->data = ptr;
    }

    actor_array->data[actor_array->count++] = actor;
}

Actor *actor_array_get(ActorArray *actor_array, size_t index) { return actor_array->data[index]; }
