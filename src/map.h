/**
 * @file map.h
 * @brief This header file defines the Map data structure and associated functions for managing game maps.
 *
 *  This module provides functions for creating, manipulating, and accessing data within a 2D map represented
 *  as a 1D array.  Error handling is minimal, relying on the caller to handle potential memory allocation failures.
 */
#ifndef MAP_H
#define MAP_H

#include <stddef.h>

/**
 * @brief Represents a 2D game map.  The map data is stored internally as a 1D array.
 */
typedef struct map_impl Map;

/**
 * @brief Creates a new map with the specified width and height.
 *
 * @param width The width of the map (number of columns). Must be greater than 0.
 * @param height The height of the map (number of rows). Must be greater than 0.
 * @return A pointer to the newly created Map.  The caller is responsible for freeing the allocated memory using map_free().
 */
Map *map_create(size_t width, size_t height);

/**
 * @brief Frees the memory allocated for the given map.
 *
 * @param map A pointer to the Map to be freed.  The pointer will be set to NULL after freeing the memory.
 */
void map_free(Map *map);

/**
 * @brief Returns the width of the map.
 *
 * @param map A pointer to the Map.
 * @return The width of the map.
 */
size_t map_get_width(Map *map);

/**
 * @brief Returns the height of the map.
 *
 * @param map A pointer to the Map.
 * @return The height of the map.
 */
size_t map_get_height(Map *map);

/**
 * @brief Returns a pointer to the internal 1D array representing the map data.
 *
 * @param map A pointer to the Map.
 * @return A pointer to the map's data array.  Modifying this array directly is discouraged; use map_data_set_at() and map_data_get_at() instead.
 */
int *map_get_data(Map *map);

/**
 * @brief Gets the value at the specified coordinates in the map.
 *
 * @param map A pointer to the Map.
 * @param x The x-coordinate (column index). Must be less than map_get_width(map).
 * @param y The y-coordinate (row index). Must be less than map_get_height(map).
 * @return The integer value at the specified coordinates.
 */
int map_data_get_at(Map *map, size_t x, size_t y);

/**
 * @brief Sets the value at the specified coordinates in the map.
 *
 * @param map A pointer to the Map.
 * @param x The x-coordinate (column index). Must be less than map_get_width(map).
 * @param y The y-coordinate (row index). Must be less than map_get_height(map).
 * @param value The integer value to set at the specified coordinates.
 */
void map_data_set_at(Map *map, size_t x, size_t y, int value);

/**
 * @brief Sets all values in the map to the specified value.
 *
 * @param map A pointer to the Map.
 * @param value The integer value to set all map cells to.
 */
void map_data_set_all(Map *map, int value);

#endif
