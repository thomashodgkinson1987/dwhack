#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Opaque struct definition for Player.  Implementation details are hidden.
typedef struct player_impl Player;

// Enum defining the possible directions a player can face.
enum player_direction
{
    PLAYER_NORTH = 0,
    PLAYER_EAST = 1,
    PLAYER_SOUTH = 2,
    PLAYER_WEST = 3
};

/**
 * @brief Creates a new player.
 * 
 * @param x The player's initial x-coordinate.
 * @param y The player's initial y-coordinate.
 * @param facing The player's initial facing direction.
 * @param health The player's initial health.
 * @param color The player's color.
 * @return A pointer to the newly created player, or NULL if memory allocation fails.
 */
Player *player_create(int x, int y, enum player_direction facing, int health, Color color);

/**
 * @brief Frees the memory allocated for a player.
 * 
 * @param player A pointer to the player to be freed.  Sets the pointer to NULL after freeing.
 */
void player_free(Player *player);

/**
 * @brief Gets the player's x-coordinate.
 * 
 * @param player A pointer to the player.
 * @return The player's x-coordinate.
 */
int player_get_x(const Player *player);

/**
 * @brief Gets the player's y-coordinate.
 * 
 * @param player A pointer to the player.
 * @return The player's y-coordinate.
 */
int player_get_y(const Player *player);

/**
 * @brief Gets the player's facing direction.
 * 
 * @param player A pointer to the player.
 * @return The player's facing direction.
 */
enum player_direction player_get_facing(const Player *player);

/**
 * @brief Gets the player's health.
 * 
 * @param player A pointer to the player.
 * @return The player's health.
 */
int player_get_health(const Player *player);

/**
 * @brief Gets the player's color.
 * 
 * @param player A pointer to the player.
 * @return The player's color.
 */
Color player_get_color(const Player *player);

/**
 * @brief Sets the player's x-coordinate.
 * 
 * @param player A pointer to the player.
 * @param x The new x-coordinate.
 */
void player_set_x(Player *player, int x);

/**
 * @brief Sets the player's y-coordinate.
 * 
 * @param player A pointer to the player.
 * @param y The new y-coordinate.
 */
void player_set_y(Player *player, int y);

/**
 * @brief Sets the player's facing direction.
 * 
 * @param player A pointer to the player.
 * @param facing The new facing direction.
 */
void player_set_facing(Player *player, enum player_direction facing);

/**
 * @brief Sets the player's health.
 * 
 * @param player A pointer to the player.
 * @param health The new health.
 */
void player_set_health(Player *player, int health);

/**
 * @brief Sets the player's color.
 * 
 * @param player A pointer to the player.
 * @param color The new color.
 */
void player_set_color(Player *player, Color color);

#endif
