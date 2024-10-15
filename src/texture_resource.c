#include "texture_resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct texture_resource_impl
{
    char *name;
    Texture2D texture;
};

TextureResource *texture_resource_create(const char *filename)
{
    TextureResource *texture_resource = malloc(sizeof *texture_resource);

    if (texture_resource == NULL)
    {
        fprintf(stderr, "Error creating texture resource\n");
        exit(1);
    }

    texture_resource->name = malloc(strlen(filename) + 1);

    if (texture_resource->name == NULL)
    {
        fprintf(stderr, "Error creating texture resource name\n");
        exit(1);
    }

    strncpy(texture_resource->name, filename, strlen(filename) + 1);

    texture_resource->texture = LoadTexture(filename);

    return texture_resource;
}

void texture_resource_free(TextureResource *texture_resource)
{
    free(texture_resource->name);
    UnloadTexture(texture_resource->texture);
    free(texture_resource);
    texture_resource = NULL;
}

char *texture_resource_get_name(TextureResource *texture_resource) { return texture_resource->name; }

Texture2D texture_resource_get_texture(TextureResource *texture_resource) { return texture_resource->texture; }

void texture_resource_set_name(TextureResource *texture_resource, char *name) { texture_resource->name = name; }

void texture_resource_set_texture(TextureResource *texture_resource, Texture2D texture) { texture_resource->texture = texture; }
