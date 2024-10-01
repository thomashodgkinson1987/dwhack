#include "map.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct map map_create(size_t width, size_t height)
{
    assert(width > 0);
    assert(height > 0);

    struct map map = (struct map){0};

    map.width = width;
    map.height = height;
    map.data = malloc(sizeof *map.data * map.width * map.height);
    assert(map.data != NULL);
    memset(map.data, 0, sizeof *map.data * map.width * map.height);

    return map;
}

void map_free(struct map *map)
{
    map->width = 0;
    map->height = 0;
    free(map->data);
    map->data = NULL;
}

size_t map_get_width(struct map *map)
{
    return map->width;
}

size_t map_get_height(struct map *map)
{
    return map->height;
}

int *map_get_data(struct map *map)
{
    return map->data;
}

int map_data_get_at(struct map *map, size_t x, size_t y)
{
    assert(x < map->width);
    assert(y < map->height);

    return map->data[y * map->width + x];
}

void map_data_set_at(struct map *map, size_t x, size_t y, int value)
{
    assert(x < map->width);
    assert(y < map->height);

    map->data[y * map->width + x] = value;
}

void map_data_set_all(struct map *map, int value)
{
    for (size_t i = 0; i < map->width * map->height; ++i)
    {
        map->data[i] = value;
    }
}
