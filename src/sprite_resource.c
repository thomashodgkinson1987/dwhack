#include "sprite_resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sprite_resource_impl
{
    char *name;
    Sprite *sprite;
};

SpriteResource *sprite_resource_create(char *name, Sprite *sprite)
{
    SpriteResource *sprite_resource = malloc(sizeof *sprite_resource);

    if (sprite_resource == NULL)
    {
        fprintf(stderr, "Error creating sprite resource\n");
        exit(1);
    }

    sprite_resource->name = malloc(strlen(name) + 1);

    if (sprite_resource->name == NULL)
    {
        fprintf(stderr, "Error creating sprite resource name\n");
        exit(1);
    }

    strncpy(sprite_resource->name, name, strlen(name) + 1);

    sprite_resource->sprite = sprite;

    return sprite_resource;
}

void sprite_resource_free(SpriteResource *sprite_resource)
{
    free(sprite_resource->name);
    free(sprite_resource);
    sprite_resource = NULL;
}

char *sprite_resource_get_name(SpriteResource *sprite_resource) { return sprite_resource->name; }

Sprite *sprite_resource_get_sprite(SpriteResource *sprite_resource) { return sprite_resource->sprite; }

void sprite_resource_set_name(SpriteResource *sprite_resource, char *name) { sprite_resource->name = name; }

void sprite_resource_set_sprite(SpriteResource *sprite_resource, Sprite *sprite) { sprite_resource->sprite = sprite; }
