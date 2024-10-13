/**
 * @file dungeon_camera.h
 * @brief This file declares the DungeonCamera structure and its associated functions for managing a camera in a dungeon-like environment.
 */
#ifndef DUNGEON_CAMERA_H
#define DUNGEON_CAMERA_H

#include "cardinal_directions.h"

/**
 * @brief Opaque structure representing a dungeon camera.  Implementation details are hidden.
 */
typedef struct dungeon_camera_impl DungeonCamera;

/**
 * @brief Creates a new dungeon camera object.
 * 
 * @param x The initial x-coordinate of the camera.
 * @param y The initial y-coordinate of the camera.
 * @param facing The initial facing direction of the camera.
 * @return A pointer to the newly created DungeonCamera object, or NULL if memory allocation fails.
 */
DungeonCamera *dungeon_camera_create(int x, int y, CardinalDirection facing);

/**
 * @brief Frees the memory allocated for a dungeon camera object.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object to be freed.  Sets the pointer to NULL after freeing.
 */
void dungeon_camera_free(DungeonCamera *dungeon_camera);

/**
 * @brief Gets the x-coordinate of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @return The x-coordinate of the camera.
 */
int dungeon_camera_get_x(const DungeonCamera *dungeon_camera);

/**
 * @brief Gets the y-coordinate of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @return The y-coordinate of the camera.
 */
int dungeon_camera_get_y(const DungeonCamera *dungeon_camera);

/**
 * @brief Gets the facing direction of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @return The facing direction of the camera.
 */
CardinalDirection dungeon_camera_get_facing(const DungeonCamera *dungeon_camera);

/**
 * @brief Sets the x-coordinate of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @param x The new x-coordinate of the camera.
 */
void dungeon_camera_set_x(DungeonCamera *dungeon_camera, int x);

/**
 * @brief Sets the y-coordinate of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @param y The new y-coordinate of the camera.
 */
void dungeon_camera_set_y(DungeonCamera *dungeon_camera, int y);

/**
 * @brief Sets the facing direction of the dungeon camera.
 * 
 * @param dungeon_camera A pointer to the DungeonCamera object.
 * @param facing The new facing direction of the camera.
 */
void dungeon_camera_set_facing(DungeonCamera *dungeon_camera, CardinalDirection facing);

#endif
