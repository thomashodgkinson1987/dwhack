/**
 * @file map.c
 * @brief Implementation of map functions.
 */

#include "map.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a new map with the given width and height.
 *
 * @param width The width of the map.
 * @param height The height of the map.
 * @return A new map struct.
 */
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

/**
 * @brief Frees the memory allocated for the map.
 *
 * @param map The map to free.
 */
void map_free(struct map *map)
{
    map->width = 0;
    map->height = 0;
    free(map->data);
    map->data = NULL;
}

/**
 * @brief Gets the width of the map.
 *
 * @param map The map.
 * @return The width of the map.
 */
size_t map_get_width(struct map *map)
{
    return map->width;
}

/**
 * @brief Gets the height of the map.
 *
 * @param map The map.
 * @return The height of the map.
 */
size_t map_get_height(struct map *map)
{
    return map->height;
}

/**
 * @brief Gets the data of the map.
 *
 * @param map The map.
 * @return A pointer to the map data.
 */
int *map_get_data(struct map *map)
{
    return map->data;
}

/**
 * @brief Gets the value at the given coordinates.
 *
 * @param map The map.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @return The value at the given coordinates.
 */
int map_data_get_at(struct map *map, size_t x, size_t y)
{
    assert(x < map->width);
    assert(y < map->height);

    return map->data[y * map->width + x];
}

/**
 * @brief Sets the value at the given coordinates.
 *
 * @param map The map.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param value The value to set.
 */
void map_data_set_at(struct map *map, size_t x, size_t y, int value)
{
    assert(x < map->width);
    assert(y < map->height);

    map->data[y * map->width + x] = value;
}

/**
 * @brief Sets all values in the map to the given value.
 *
 * @param map The map.
 * @param value The value to set.
 */
void map_data_set_all(struct map *map, int value)
{
    for (size_t i = 0; i < map->width * map->height; ++i)
    {
        map->data[i] = value;
    }
}
