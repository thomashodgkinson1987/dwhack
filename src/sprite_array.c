#include "sprite_array.h"

#include <stdio.h>
#include <stdlib.h>

struct sprite_array_impl
{
    size_t count;
    size_t capacity;
    Sprite **data;
};

SpriteArray *sprite_array_create(void)
{
    SpriteArray *sprite_array = malloc(sizeof *sprite_array);

    if (sprite_array == NULL)
    {
        fprintf(stderr, "Error creating sprite array\n");
        exit(1);
    }

    sprite_array->count = 0;
    sprite_array->capacity = 1;
    sprite_array->data = malloc(sizeof sprite_array->data * sprite_array->capacity);

    if (sprite_array->data == NULL)
    {
        fprintf(stderr, "Error creating sprite array data\n");
        exit(1);
    }

    for (size_t i = 0; i < sprite_array->capacity; ++i)
    {
        sprite_array->data[i] = NULL;
    }

    return sprite_array;
}

void sprite_array_free(SpriteArray *sprite_array)
{
    free(sprite_array->data);
    free(sprite_array);
    sprite_array = NULL;
}

size_t sprite_array_get_count(SpriteArray *sprite_array) { return sprite_array->count; }

size_t sprite_array_get_capacity(SpriteArray *sprite_array) { return sprite_array->capacity; }

Sprite **sprite_array_get_data(SpriteArray *sprite_array) { return sprite_array->data; }

void sprite_array_set_count(SpriteArray *sprite_array, size_t count) { sprite_array->count = count; }

void sprite_array_set_capacity(SpriteArray *sprite_array, size_t capacity) { sprite_array->capacity = capacity; }

void sprite_array_set_data(SpriteArray *sprite_array, Sprite **data) { sprite_array->data = data; }

void sprite_array_add(SpriteArray *sprite_array, Sprite *sprite)
{
    if (sprite_array->count == sprite_array->capacity)
    {
        Sprite **ptr = realloc(sprite_array->data, sizeof *sprite_array->data * sprite_array->capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating sprite array data\n");
            exit(1);
        }
        for (size_t i = sprite_array->capacity; i < sprite_array->capacity * 2; ++i)
        {
            ptr[i] = NULL;
        }
        sprite_array->capacity *= 2;
        sprite_array->data = ptr;
    }

    sprite_array->data[sprite_array->count++] = sprite;
}

Sprite *sprite_array_get(SpriteArray *sprite_array, size_t index) { return sprite_array->data[index]; }
