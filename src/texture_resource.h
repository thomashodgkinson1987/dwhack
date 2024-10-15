#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "raylib.h"

typedef struct texture_resource_impl TextureResource;

TextureResource *texture_resource_create(const char *name, Texture2D texture);

void texture_resource_free(TextureResource *texture_resource);

char *texture_resource_get_name(TextureResource *texture_resource);

Texture2D texture_resource_get_texture(TextureResource *texture_resource);

void texture_resource_set_name(TextureResource *texture_resource, char *name);

void texture_resource_set_texture(TextureResource *texture_resource, Texture2D texture);

#endif
