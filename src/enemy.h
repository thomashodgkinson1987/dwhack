/**
 * @file enemy.h
 * @brief This file declares the Enemy data structure and its associated functions.
 *        It provides an interface for creating, manipulating, and accessing enemy data.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "cardinal_directions.h"

#include "raylib.h"

// Opaque struct definition for Enemy.  Implementation details are hidden.
typedef struct enemy_impl Enemy;

/**
 * @brief Creates a new enemy.
 *
 * @param x The x-coordinate of the enemy.
 * @param y The y-coordinate of the enemy.
 * @param facing The initial direction the enemy is facing.
 * @param health The initial health of the enemy.
 * @param color The color of the enemy.
 * @return A pointer to the newly created enemy, or NULL if memory allocation fails.
 */
Enemy *enemy_create(int x, int y, CardinalDirection facing, int health, Color color);

/**
 * @brief Frees the memory allocated for an enemy.
 *
 * @param enemy A pointer to the enemy to be freed. Sets the pointer to NULL after freeing.
 */
void enemy_free(Enemy *enemy);

/**
 * @brief Gets the x-coordinate of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @return The x-coordinate of the enemy.
 */
int enemy_get_x(const Enemy *enemy);

/**
 * @brief Gets the y-coordinate of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @return The y-coordinate of the enemy.
 */
int enemy_get_y(const Enemy *enemy);

/**
 * @brief Gets the direction the enemy is facing.
 *
 * @param enemy A pointer to the enemy.
 * @return The direction the enemy is facing.
 */
CardinalDirection enemy_get_facing(const Enemy *enemy);

/**
 * @brief Gets the health of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @return The health of the enemy.
 */
int enemy_get_health(const Enemy *enemy);

/**
 * @brief Gets the color of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @return The color of the enemy.
 */
Color enemy_get_color(const Enemy *enemy);

/**
 * @brief Sets the x-coordinate of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @param x The new x-coordinate.
 */
void enemy_set_x(Enemy *enemy, int x);

/**
 * @brief Sets the y-coordinate of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @param y The new y-coordinate.
 */
void enemy_set_y(Enemy *enemy, int y);

/**
 * @brief Sets the direction the enemy is facing.
 *
 * @param enemy A pointer to the enemy.
 * @param facing The new direction.
 */
void enemy_set_facing(Enemy *enemy, CardinalDirection facing);

/**
 * @brief Sets the health of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @param health The new health.
 */
void enemy_set_health(Enemy *enemy, int health);

/**
 * @brief Sets the color of the enemy.
 *
 * @param enemy A pointer to the enemy.
 * @param color The new color.
 */
void enemy_set_color(Enemy *enemy, Color color);

#endif
