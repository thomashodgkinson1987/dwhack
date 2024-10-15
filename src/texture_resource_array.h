#ifndef TEXTURE_RESOURCE_ARRAY
#define TEXTURE_RESOURCE_ARRAY

#include "texture_resource.h"

#include <stddef.h>

typedef struct texture_resource_array_impl TextureResourceArray;

TextureResourceArray *texture_resource_array_create(void);

void texture_resource_array_free(TextureResourceArray *texture_resource_array);

size_t texture_resource_array_get_count(TextureResourceArray *texture_resource_array);

size_t texture_resource_array_get_capacity(TextureResourceArray *texture_resource_array);

TextureResource **texture_resource_array_get_data(TextureResourceArray *texture_resource_array);

void texture_resource_array_set_count(TextureResourceArray *texture_resource_array, size_t count);

void texture_resource_array_set_capacity(TextureResourceArray *texture_resource_array, size_t capacity);

void texture_resource_array_set_data(TextureResourceArray *texture_resource_array, TextureResource **data);

void texture_resource_array_add(TextureResourceArray *texture_resource_array, TextureResource *texture_resource);

TextureResource *texture_resource_array_get(TextureResourceArray *texture_resource_array, size_t index);

#endif
