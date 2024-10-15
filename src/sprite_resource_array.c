#include "sprite_resource_array.h"

#include <stdio.h>
#include <stdlib.h>

struct sprite_resource_array_impl
{
    size_t count;
    size_t capacity;
    SpriteResource **data;
};

SpriteResourceArray *sprite_resource_array_create(void)
{
    SpriteResourceArray *sprite_resource_array = malloc(sizeof *sprite_resource_array);

    if (sprite_resource_array == NULL)
    {
        fprintf(stderr, "Error creating sprite resource array\n");
        exit(1);
    }

    sprite_resource_array->count = 0;
    sprite_resource_array->capacity = 1;
    sprite_resource_array->data = malloc(sizeof sprite_resource_array->data * sprite_resource_array->capacity);

    if (sprite_resource_array->data == NULL)
    {
        fprintf(stderr, "Error creating sprite resource array data\n");
        exit(1);
    }

    for (size_t i = 0; i < sprite_resource_array->capacity; ++i)
    {
        sprite_resource_array->data[i] = NULL;
    }

    return sprite_resource_array;
}

void sprite_resource_array_free(SpriteResourceArray *sprite_resource_array)
{
    free(sprite_resource_array->data);
    free(sprite_resource_array);
    sprite_resource_array = NULL;
}

size_t sprite_resource_array_get_count(SpriteResourceArray *sprite_resource_array) { return sprite_resource_array->count; }

size_t sprite_resource_array_get_capacity(SpriteResourceArray *sprite_resource_array) { return sprite_resource_array->capacity; }

SpriteResource **sprite_resource_array_get_data(SpriteResourceArray *sprite_resource_array) { return sprite_resource_array->data; }

void sprite_resource_array_set_count(SpriteResourceArray *sprite_resource_array, size_t count) { sprite_resource_array->count = count; }

void sprite_resource_array_set_capacity(SpriteResourceArray *sprite_resource_array, size_t capacity) { sprite_resource_array->capacity = capacity; }

void sprite_resource_array_set_data(SpriteResourceArray *sprite_resource_array, SpriteResource **data) { sprite_resource_array->data = data; }

void sprite_resource_array_add(SpriteResourceArray *sprite_resource_array, SpriteResource *sprite_resource)
{
    if (sprite_resource_array->count == sprite_resource_array->capacity)
    {
        SpriteResource **ptr = realloc(sprite_resource_array->data, sizeof *sprite_resource_array->data * sprite_resource_array->capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating sprite resource array data\n");
            exit(1);
        }
        for (size_t i = sprite_resource_array->capacity; i < sprite_resource_array->capacity * 2; ++i)
        {
            ptr[i] = NULL;
        }
        sprite_resource_array->capacity *= 2;
        sprite_resource_array->data = ptr;
    }

    sprite_resource_array->data[sprite_resource_array->count++] = sprite_resource;
}

SpriteResource *sprite_resource_array_get(SpriteResourceArray *sprite_resource_array, size_t index) { return sprite_resource_array->data[index]; }
