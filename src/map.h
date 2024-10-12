/**
 * @file map.h
 * @brief Header file for map functions.
 */

#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Structure representing a map.
 */
struct map {
    size_t width;  /**< Width of the map. */
    size_t height; /**< Height of the map. */
    int *data;     /**< Pointer to the map data. */
};

/**
 * @brief Creates a new map with the given width and height.
 *
 * @param width The width of the map.
 * @param height The height of the map.
 * @return A new map struct.
 */
struct map map_create(size_t width, size_t height);

/**
 * @brief Frees the memory allocated for the map.
 *
 * @param map The map to free.
 */
void map_free(struct map *map);

/**
 * @brief Gets the width of the map.
 *
 * @param map The map.
 * @return The width of the map.
 */
size_t map_get_width(struct map *map);

/**
 * @brief Gets the height of the map.
 *
 * @param map The map.
 * @return The height of the map.
 */
size_t map_get_height(struct map *map);

/**
 * @brief Gets the data of the map.
 *
 * @param map The map.
 * @return A pointer to the map data.
 */
int *map_get_data(struct map *map);

/**
 * @brief Gets the value at the given coordinates.
 *
 * @param map The map.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @return The value at the given coordinates.
 */
int map_data_get_at(struct map *map, size_t x, size_t y);

/**
 * @brief Sets the value at the given coordinates.
 *
 * @param map The map.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param value The value to set.
 */
void map_data_set_at(struct map *map, size_t x, size_t y, int value);

/**
 * @brief Sets all values in the map to the given value.
 *
 * @param map The map.
 * @param value The value to set.
 */
void map_data_set_all(struct map *map, int value);

#endif
