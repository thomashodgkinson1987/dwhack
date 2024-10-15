#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H

#include "sprite.h"

typedef struct sprite_resource_impl SpriteResource;

SpriteResource *sprite_resource_create(char *name, Sprite *sprite);

void sprite_resource_free(SpriteResource *sprite_resource);

char *sprite_resource_get_name(SpriteResource *sprite_resource);

Sprite *sprite_resource_get_sprite(SpriteResource *sprite_resource);

void sprite_resource_set_name(SpriteResource *sprite_resource, char *name);

void sprite_resource_set_sprite(SpriteResource *sprite_resource, Sprite *sprite);

#endif
