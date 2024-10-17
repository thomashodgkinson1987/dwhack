#ifndef ACTOR_H
#define ACTOR_H

#include "cardinal_directions.h"

#include "raylib.h"

typedef struct actor_impl Actor;

Actor *actor_create(int x, int y, CardinalDirection facing, int health, Color color);

void actor_free(Actor *actor);

// getters

int actor_get_x(const Actor *actor);

int actor_get_y(const Actor *actor);

CardinalDirection actor_get_facing(const Actor *actor);

int actor_get_health(const Actor *actor);

int actor_get_max_health(const Actor *actor);

Color actor_get_color(const Actor *actor);

// setters

void actor_set_x(Actor *actor, int x);

void actor_set_y(Actor *actor, int y);

void actor_set_facing(Actor *actor, CardinalDirection facing);

void actor_set_health(Actor *actor, int health);

void actor_set_max_health(Actor *actor, int max_health);

void actor_set_color(Actor *actor, Color color);

// helpers

void actor_set_position(Actor *actor, int x, int y);

#endif
