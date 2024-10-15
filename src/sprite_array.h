#ifndef SPRITE_ARRAY_H
#define SPRITE_ARRAY_H

#include "sprite.h"

#include <stddef.h>

typedef struct sprite_array_impl SpriteArray;

SpriteArray *sprite_array_create(void);

void sprite_array_free(SpriteArray *sprite_array);

size_t sprite_array_get_count(SpriteArray *sprite_array);

size_t sprite_array_get_capacity(SpriteArray *sprite_array);

Sprite **sprite_array_get_data(SpriteArray *sprite_array);

void sprite_array_set_count(SpriteArray *sprite_array, size_t count);

void sprite_array_set_capacity(SpriteArray *sprite_array, size_t capacity);

void sprite_array_set_data(SpriteArray *sprite_array, Sprite **data);

void sprite_array_add(SpriteArray *sprite_array, Sprite *sprite);

Sprite *sprite_array_get(SpriteArray *sprite_array, size_t index);

#endif
