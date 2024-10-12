#include "player.h"

#include <stdlib.h>

// Structure implementation for the Player type.
struct player_impl
{
    int x;                        // The player's x-coordinate.
    int y;                        // The player's y-coordinate.
    enum player_direction facing; // The player's facing direction.
    int health;                   // The player's health.
    Color color;                  // The player's color.
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
Player *player_create(int x, int y, enum player_direction facing, int health, Color color)
{
    Player *player = (Player *)malloc(sizeof(struct player_impl));

    if (player != NULL)
    {
        player->x = x;
        player->y = y;
        player->facing = facing;
        player->health = health;
        player->color = color;
    }

    return player;
}

/**
 * @brief Frees the memory allocated for a player.
 *
 * @param player A pointer to the player to be freed.
 */
void player_free(Player *player)
{
    if (player != NULL)
    {
        free(player);
        // Setting player to NULL is good practice but not strictly necessary as the pointer is no longer valid after free().
        player = NULL;
    }
}

/**
 * @brief Gets the player's x-coordinate.
 *
 * @param player A pointer to the player.
 * @return The player's x-coordinate.
 */
int player_get_x(const Player *player) { return player->x; }

/**
 * @brief Gets the player's y-coordinate.
 *
 * @param player A pointer to the player.
 * @return The player's y-coordinate.
 */
int player_get_y(const Player *player) { return player->y; }

/**
 * @brief Gets the player's facing direction.
 *
 * @param player A pointer to the player.
 * @return The player's facing direction.
 */
enum player_direction player_get_facing(const Player *player) { return player->facing; }

/**
 * @brief Gets the player's health.
 *
 * @param player A pointer to the player.
 * @return The player's health.
 */
int player_get_health(const Player *player) { return player->health; }

/**
 * @brief Gets the player's color.
 *
 * @param player A pointer to the player.
 * @return The player's color.
 */
Color player_get_color(const Player *player) { return player->color; }

/**
 * @brief Sets the player's x-coordinate.
 *
 * @param player A pointer to the player.
 * @param x The new x-coordinate.
 */
void player_set_x(Player *player, int x) { player->x = x; }

/**
 * @brief Sets the player's y-coordinate.
 *
 * @param player A pointer to the player.
 * @param y The new y-coordinate.
 */
void player_set_y(Player *player, int y) { player->y = y; }

/**
 * @brief Sets the player's facing direction.
 *
 * @param player A pointer to the player.
 * @param facing The new facing direction.
 */
void player_set_facing(Player *player, enum player_direction facing) { player->facing = facing; }

/**
 * @brief Sets the player's health.
 *
 * @param player A pointer to the player.
 * @param health The new health.
 */
void player_set_health(Player *player, int health) { player->health = health; }

/**
 * @brief Sets the player's color.
 *
 * @param player A pointer to the player.
 * @param color The new color.
 */
void player_set_color(Player *player, Color color) { player->color = color; }
