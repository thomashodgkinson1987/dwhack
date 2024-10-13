/**
 * @file sprite.h
 * @brief This file defines the interface for the Sprite data structure and its associated functions.
 *        Sprites are used to represent images in the game.
 */
#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

/**
 * @brief Opaque struct representing a sprite.  Users should interact with it only through the provided functions.
 */
typedef struct sprite_impl Sprite;

/**
 * @brief Creates a new sprite.
 *
 * @param texture The texture to use for the sprite.
 * @param x The x-coordinate of the sprite's top-left corner.
 * @param y The y-coordinate of the sprite's top-left corner.
 * @param w The width of the sprite.
 * @param h The height of the sprite.
 * @return A pointer to the newly created sprite, or NULL if memory allocation fails.
 */
Sprite *sprite_create(Texture2D texture, float x, float y, float w, float h);

/**
 * @brief Frees the memory allocated for a sprite.
 *
 * @param sprite A pointer to the sprite to free. Pointer is set to NULL.
 */
void sprite_free(Sprite *sprite);

/**
 * @brief Gets the visibility state of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return True if the sprite is visible, false otherwise.
 */
bool sprite_get_is_visible(const Sprite *sprite);

/**
 * @brief Gets the texture of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The texture of the sprite.
 */
Texture2D sprite_get_texture(const Sprite *sprite);

/**
 * @brief Gets the source rectangle of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The source rectangle of the sprite.
 */
Rectangle sprite_get_source(const Sprite *sprite);

/**
 * @brief Gets the destination rectangle of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The destination rectangle of the sprite.
 */
Rectangle sprite_get_dest(const Sprite *sprite);

/**
 * @brief Gets the origin of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The origin of the sprite.
 */
Vector2 sprite_get_origin(const Sprite *sprite);

/**
 * @brief Gets the rotation of the sprite in degrees.
 *
 * @param sprite A pointer to the sprite.
 * @return The rotation of the sprite.
 */
float sprite_get_rotation(const Sprite *sprite);

/**
 * @brief Gets the tint color of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The tint color of the sprite.
 */
Color sprite_get_tint(const Sprite *sprite);

/**
 * @brief Sets the visibility state of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param is_visible True to make the sprite visible, false to hide it.
 */
void sprite_set_is_visible(Sprite *sprite, bool is_visible);

/**
 * @brief Sets the texture of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param texture The new texture for the sprite.
 */
void sprite_set_texture(Sprite *sprite, Texture2D texture);

/**
 * @brief Sets the source rectangle of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param source The new source rectangle for the sprite.
 */
void sprite_set_source(Sprite *sprite, Rectangle source);

/**
 * @brief Sets the destination rectangle of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param dest The new destination rectangle for the sprite.
 */
void sprite_set_dest(Sprite *sprite, Rectangle dest);

/**
 * @brief Sets the origin of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param origin The new origin for the sprite.
 */
void sprite_set_origin(Sprite *sprite, Vector2 origin);

/**
 * @brief Sets the rotation of the sprite in degrees.
 *
 * @param sprite A pointer to the sprite.
 * @param rotation The new rotation for the sprite.
 */
void sprite_set_rotation(Sprite *sprite, float rotation);

/**
 * @brief Sets the tint color of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param tint The new tint color for the sprite.
 */
void sprite_set_tint(Sprite *sprite, Color tint);

/**
 * @brief Gets the x-coordinate of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The x-coordinate of the sprite.
 */
float sprite_get_x(const Sprite *sprite);

/**
 * @brief Gets the y-coordinate of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The y-coordinate of the sprite.
 */
float sprite_get_y(const Sprite *sprite);

/**
 * @brief Gets the width of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The width of the sprite.
 */
float sprite_get_w(const Sprite *sprite);

/**
 * @brief Gets the height of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @return The height of the sprite.
 */
float sprite_get_h(const Sprite *sprite);

/**
 * @brief Sets the x-coordinate of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param x The new x-coordinate for the sprite.
 */
void sprite_set_x(Sprite *sprite, float x);

/**
 * @brief Sets the y-coordinate of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param y The new y-coordinate for the sprite.
 */
void sprite_set_y(Sprite *sprite, float y);

/**
 * @brief Sets the width of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param w The new width for the sprite.
 */
void sprite_set_w(Sprite *sprite, float w);

/**
 * @brief Sets the height of the sprite.
 *
 * @param sprite A pointer to the sprite.
 * @param h The new height for the sprite.
 */
void sprite_set_h(Sprite *sprite, float h);

/**
 * @brief Draws the sprite.
 *
 * @param sprite A pointer to the sprite to draw.
 */
void sprite_draw(const Sprite *sprite);

#endif
