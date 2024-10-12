/**
 * @file enemy.c
 * @brief This file implements the functions declared in enemy.h.
 *        It provides the functionality for creating, manipulating, and freeing enemy data.
 */
#include "enemy.h"

#include <stdlib.h>

// Structure implementation for Enemy.
struct enemy_impl
{
    int x;          // x-coordinate
    int y;          // y-coordinate
    enum enemy_direction facing; // Direction the enemy is facing
    int health;     // Enemy's health
    Color color;    // Enemy's color
};

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
Enemy *enemy_create(int x, int y, enum enemy_direction facing, int health, Color color)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(struct enemy_impl));

    if (enemy != NULL)
    {
        enemy->x = x;
        enemy->y = y;
        enemy->facing = facing;
        enemy->health = health;
        enemy->color = color;
    }

    return enemy;
}

/**
 * @brief Frees the memory allocated for an enemy.
 * 
 * @param enemy A pointer to the enemy to be freed. It's safe to pass NULL.
 */
void enemy_free(Enemy *enemy)
{
    if (enemy != NULL)
    {
        free(enemy);
    }
}

/**
 * @brief Gets the x-coordinate of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @return The x-coordinate of the enemy.
 */
int enemy_get_x(const Enemy *enemy) { return enemy->x; }

/**
 * @brief Gets the y-coordinate of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @return The y-coordinate of the enemy.
 */
int enemy_get_y(const Enemy *enemy) { return enemy->y; }

/**
 * @brief Gets the direction the enemy is facing.
 * 
 * @param enemy A pointer to the enemy.
 * @return The direction the enemy is facing.
 */
enum enemy_direction enemy_get_facing(const Enemy *enemy) { return enemy->facing; }

/**
 * @brief Gets the health of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @return The health of the enemy.
 */
int enemy_get_health(const Enemy *enemy) { return enemy->health; }

/**
 * @brief Gets the color of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @return The color of the enemy.
 */
Color enemy_get_color(const Enemy *enemy) { return enemy->color; }

/**
 * @brief Sets the x-coordinate of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @param x The new x-coordinate.
 */
void enemy_set_x(Enemy *enemy, int x) { enemy->x = x; }

/**
 * @brief Sets the y-coordinate of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @param y The new y-coordinate.
 */
void enemy_set_y(Enemy *enemy, int y) { enemy->y = y; }

/**
 * @brief Sets the direction the enemy is facing.
 * 
 * @param enemy A pointer to the enemy.
 * @param facing The new direction.
 */
void enemy_set_facing(Enemy *enemy, enum enemy_direction facing) { enemy->facing = facing; }

/**
 * @brief Sets the health of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @param health The new health.
 */
void enemy_set_health(Enemy *enemy, int health) { enemy->health = health; }

/**
 * @brief Sets the color of the enemy.
 * 
 * @param enemy A pointer to the enemy.
 * @param color The new color.
 */
void enemy_set_color(Enemy *enemy, Color color) { enemy->color = color; }
