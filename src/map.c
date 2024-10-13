/**
 * @file map.c
 * @brief This file implements the functions for managing game maps.
 *
 *  This module provides the implementation details for creating, manipulating, and accessing data within a 2D map.
 *  Error handling is minimal; memory allocation failures will result in program termination.
 *
 * @version 1.0
 * @author Bard
 * @date 2023-10-27
 */
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Internal structure representing a map.
 */
struct map_impl
{
    size_t width;  /**< The width of the map (number of columns). */
    size_t height; /**< The height of the map (number of rows). */
    int *data;     /**< A 1D array storing the map data. */
};

/**
 * @brief Creates a new map with the specified width and height.
 *
 * @param width The width of the map (number of columns). Must be greater than 0.
 * @param height The height of the map (number of rows). Must be greater than 0.
 * @return A pointer to the newly created Map, or NULL if memory allocation fails.
 */
Map *map_create(size_t width, size_t height)
{
    // Allocate memory for the map structure
    Map *map = (Map *)malloc(sizeof(struct map_impl));

    // Check for memory allocation errors
    if (map == NULL)
    {
        fprintf(stderr, "Error creating map: memory allocation failed\n");
        exit(1); // Exit the program if memory allocation fails
    }

    // Set the map dimensions
    map->width = width;
    map->height = height;

    // Allocate memory for the map data
    map->data = malloc(sizeof *map->data * map->width * map->height);

    // Check for memory allocation errors
    if (map->data == NULL)
    {
        fprintf(stderr, "Error creating map  memory allocation failed\n");
        free(map); // Free the map structure if data allocation fails
        exit(1);   // Exit the program
    }

    // Initialize the map data to 0
    memset(map->data, 0, sizeof *map->data * map->width * map->height);

    return map;
}

/**
 * @brief Frees the memory allocated for the given map.
 *
 * @param map A pointer to the Map to be freed.  The pointer will be set to NULL after freeing the memory.
 */
void map_free(Map *map)
{
    free(map->data); // Free the map data
    free(map);       // Free the map structure
    map = NULL;      // Set the pointer to NULL to prevent dangling pointers
}

/**
 * @brief Returns the width of the map.
 *
 * @param map A pointer to the Map.
 * @return The width of the map.
 */
size_t map_get_width(Map *map)
{
    return map->width;
}

/**
 * @brief Returns the height of the map.
 *
 * @param map A pointer to the Map.
 * @return The height of the map.
 */
size_t map_get_height(Map *map)
{
    return map->height;
}

/**
 * @brief Returns a pointer to the internal 1D array representing the map data.
 *
 * @param map A pointer to the Map.
 * @return A pointer to the map's data array.  Modifying this array directly is discouraged; use map_data_set_at() and map_data_get_at() instead.
 */
int *map_get_data(Map *map)
{
    return map->data;
}

/**
 * @brief Gets the value at the specified coordinates in the map.
 *
 * @param map A pointer to the Map.
 * @param x The x-coordinate (column index). Must be less than map_get_width(map).
 * @param y The y-coordinate (row index). Must be less than map_get_height(map).
 * @return The integer value at the specified coordinates.
 */
int map_data_get_at(Map *map, size_t x, size_t y)
{
    return map->data[y * map->width + x];
}

/**
 * @brief Sets the value at the specified coordinates in the map.
 *
 * @param map A pointer to the Map.
 * @param x The x-coordinate (column index). Must be less than map_get_width(map).
 * @param y The y-coordinate (row index). Must be less than map_get_height(map).
 * @param value The integer value to set at the specified coordinates.
 */
void map_data_set_at(Map *map, size_t x, size_t y, int value)
{
    map->data[y * map->width + x] = value;
}

/**
 * @brief Sets all values in the map to the specified value.
 *
 * @param map A pointer to the Map.
 * @param value The integer value to set all map cells to.
 */
void map_data_set_all(Map *map, int value)
{
    for (size_t i = 0; i < map->width * map->height; ++i)
    {
        map->data[i] = value;
    }
}
