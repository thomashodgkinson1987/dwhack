#include "texture_resource_array.h"

#include "texture_resource.h"

#include <stdio.h>
#include <stdlib.h>

struct texture_resource_array_impl
{
    size_t count;
    size_t capacity;
    TextureResource **data;
};

TextureResourceArray *texture_resource_array_create(void)
{
    TextureResourceArray *texture_resource_array = malloc(sizeof *texture_resource_array);

    if (texture_resource_array == NULL)
    {
        fprintf(stderr, "Error creating texture resource array\n");
        exit(1);
    }

    texture_resource_array->count = 0;
    texture_resource_array->capacity = 1;
    texture_resource_array->data = malloc(sizeof *texture_resource_array->data * texture_resource_array->capacity);

    if (texture_resource_array->data == NULL)
    {
        fprintf(stderr, "Error creating texture resource array data\n");
        exit(1);
    }

    for (size_t i = 0; i < texture_resource_array->capacity; ++i)
    {
        texture_resource_array->data[i] = NULL;
    }

    return texture_resource_array;
}

void texture_resource_array_free(TextureResourceArray *texture_resource_array)
{
    free(texture_resource_array->data);
    free(texture_resource_array);
    texture_resource_array = NULL;
}

size_t texture_resource_array_get_count(TextureResourceArray *texture_resource_array) { return texture_resource_array->count; }

size_t texture_resource_array_get_capacity(TextureResourceArray *texture_resource_array) { return texture_resource_array->capacity; }

TextureResource **texture_resource_array_get_data(TextureResourceArray *texture_resource_array) { return texture_resource_array->data; }

void texture_resource_array_set_count(TextureResourceArray *texture_resource_array, size_t count) { texture_resource_array->count = count; }

void texture_resource_array_set_capacity(TextureResourceArray *texture_resource_array, size_t capacity) { texture_resource_array->capacity = capacity; }

void texture_resource_array_set_data(TextureResourceArray *texture_resource_array, TextureResource **data) { texture_resource_array->data = data; }

void texture_resource_array_add(TextureResourceArray *texture_resource_array, TextureResource *texture_resource)
{
    if (texture_resource_array->count == texture_resource_array->capacity)
    {
        TextureResource **ptr = realloc(texture_resource_array->data, sizeof *texture_resource_array->data * texture_resource_array->capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating texture resource array data\n");
            exit(1);
        }
        for (size_t i = texture_resource_array->capacity; i < texture_resource_array->capacity * 2; ++i)
        {
            ptr[i] = NULL;
        }
        texture_resource_array->capacity *= 2;
        texture_resource_array->data = ptr;
    }

    texture_resource_array->data[texture_resource_array->count++] = texture_resource;
}

TextureResource *texture_resource_array_get(TextureResourceArray *texture_resource_array, size_t index) { return texture_resource_array->data[index]; }
