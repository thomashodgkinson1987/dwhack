#ifndef MAP_H
#define MAP_H

#include <stddef.h>

typedef struct map_impl Map;

Map *map_create(size_t width, size_t height);

void map_free(Map *map);

size_t map_get_width(Map *map);

size_t map_get_height(Map *map);

int *map_get_data(Map *map);

void map_set_width(Map *map, size_t width);

void map_set_height(Map *map, size_t height);

void map_set_data(Map *map, int *data);

int map_data_get_at(Map *map, size_t x, size_t y);

void map_data_set_at(Map *map, size_t x, size_t y, int value);

void map_data_set_all(Map *map, int value);

#endif
