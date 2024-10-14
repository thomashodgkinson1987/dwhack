#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct map_impl
{
    size_t width;
    size_t height;
    int *data;
};

Map *map_create(size_t width, size_t height)
{
    Map *map = (Map *)malloc(sizeof(struct map_impl));
    if (map == NULL)
    {
        fprintf(stderr, "Error creating map: memory allocation failed\n");
        exit(1);
    }
    map->width = width;
    map->height = height;
    map->data = malloc(sizeof *map->data * map->width * map->height);
    if (map->data == NULL)
    {
        fprintf(stderr, "Error creating map  memory allocation failed\n");
        free(map);
        exit(1);
    }
    memset(map->data, 0, sizeof *map->data * map->width * map->height);
    return map;
}

void map_free(Map *map)
{
    free(map->data);
    free(map);
    map = NULL;
}

size_t map_get_width(Map *map) { return map->width; }

size_t map_get_height(Map *map) { return map->height; }

int *map_get_data(Map *map) { return map->data; }

int map_data_get_at(Map *map, size_t x, size_t y) { return map->data[y * map->width + x]; }

void map_data_set_at(Map *map, size_t x, size_t y, int value) { map->data[y * map->width + x] = value; }

void map_data_set_all(Map *map, int value)
{
    for (size_t i = 0; i < map->width * map->height; ++i)
    {
        map->data[i] = value;
    }
}
