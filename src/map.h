#ifndef MAP_H
#define MAP_H

#include <stddef.h>

struct map
{
    size_t width;
    size_t height;
    int *data;
};

struct map map_create(size_t width, size_t height);
void map_free(struct map *map);

size_t map_get_width(struct map *map);
size_t map_get_height(struct map *map);
int *map_get_data(struct map *map);

int map_data_get_at(struct map *map, size_t x, size_t y);
void map_data_set_at(struct map *map, size_t x, size_t y, int value);
void map_data_set_all(struct map *map, int value);

#endif
