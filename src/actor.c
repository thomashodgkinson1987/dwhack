#include "actor.h"

#include <stdio.h>
#include <stdlib.h>

struct actor_impl
{
    int x;
    int y;
    CardinalDirection facing;
    int health;
    int max_health;
    Color color;
};

// create and free

Actor *actor_create(int x, int y, CardinalDirection facing, int health, Color color)
{
    Actor *actor = malloc(sizeof *actor);

    if (actor == NULL)
    {
        fprintf(stderr, "Error creating actor\n");
        exit(1);
    }

    actor->x = x;
    actor->y = y;
    actor->facing = facing;
    actor->health = health;
    actor->max_health = health;
    actor->color = color;

    return actor;
}

void actor_free(Actor *actor)
{
    free(actor);
    actor = NULL;
}

// getters

int actor_get_x(const Actor *actor) { return actor->x; }

int actor_get_y(const Actor *actor) { return actor->y; }

CardinalDirection actor_get_facing(const Actor *actor) { return actor->facing; }

int actor_get_health(const Actor *actor) { return actor->health; }

int actor_get_max_health(const Actor *actor) { return actor->max_health; }

Color actor_get_color(const Actor *actor) { return actor->color; }

// setters

void actor_set_x(Actor *actor, int x) { actor->x = x; }

void actor_set_y(Actor *actor, int y) { actor->y = y; }

void actor_set_facing(Actor *actor, CardinalDirection facing) { actor->facing = facing; }

void actor_set_health(Actor *actor, int health) { actor->health = health; }

void actor_set_max_health(Actor *actor, int health) { actor->health = health; }

void actor_set_color(Actor *actor, Color color) { actor->color = color; }

// helpers

void actor_set_position(Actor *actor, int x, int y)
{
    actor_set_x(actor, x);
    actor_set_y(actor, y);
}
