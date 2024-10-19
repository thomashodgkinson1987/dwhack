#ifndef ACTOR_ARRAY_H
#define ACTOR_ARRAY_H

#include "actor.h"

#include <stddef.h>

typedef struct actor_array_impl ActorArray;

ActorArray *actor_array_create(void);

void actor_array_free(ActorArray *actor_array);

// getters

size_t actor_array_get_count(ActorArray *actor_array);

size_t actor_array_get_capacity(ActorArray *actor_array);

Actor **actor_array_get_data(ActorArray *actor_array);

// setters

void actor_array_set_count(ActorArray *actor_array, size_t count);

void actor_array_set_capacity(ActorArray *actor_array, size_t capacity);

void actor_array_set_data(ActorArray *actor_array, Actor **data);

// helpers

void actor_array_add(ActorArray *actor_array, Actor *actor);

Actor *actor_array_get(ActorArray *actor_array, size_t index);

#endif
