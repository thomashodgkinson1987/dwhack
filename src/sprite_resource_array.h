#ifndef SPRITE_RESOURCE_ARRAY_H
#define SPRITE_RESOURCE_ARRAY_H

#include "sprite_resource.h"

#include <stddef.h>

typedef struct sprite_resource_array_impl SpriteResourceArray;

SpriteResourceArray *sprite_resource_array_create(void);

void sprite_resource_array_free(SpriteResourceArray *sprite_resource_array);

size_t sprite_resource_array_get_count(SpriteResourceArray *sprite_resource_array);

size_t sprite_resource_array_get_capacity(SpriteResourceArray *sprite_resource_array);

SpriteResource **sprite_resource_array_get_data(SpriteResourceArray *sprite_resource_array);

void sprite_resource_array_set_count(SpriteResourceArray *sprite_resource_array, size_t count);

void sprite_resource_array_set_capacity(SpriteResourceArray *sprite_resource_array, size_t capacity);

void sprite_resource_array_set_data(SpriteResourceArray *sprite_resource_array, SpriteResource **data);

void sprite_resource_array_add(SpriteResourceArray *sprite_resource_array, SpriteResource *sprite_resource);

SpriteResource *sprite_resource_array_get(SpriteResourceArray *sprite_resource_array, size_t index);

#endif
