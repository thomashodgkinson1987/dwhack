/**
 * @file sprite.c
 * @brief This file implements the functions declared in sprite.h.
 */
#include "sprite.h"

#include "raylib.h"

#include <stdlib.h>

/**
 * @brief  Implementation struct for a sprite.
 */
struct sprite_impl
{
    bool is_visible;   // Whether the sprite is visible.
    Texture2D texture; // The texture of the sprite.
    Rectangle source;  // The source rectangle of the sprite within the texture.
    Rectangle dest;    // The destination rectangle of the sprite on the screen.
    Vector2 origin;    // The origin of the sprite (rotation point).
    float rotation;    // The rotation of the sprite in degrees.
    Color tint;        // The tint color of the sprite.
};

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
Sprite *sprite_create(Texture2D texture, float x, float y, float w, float h)
{
    // Allocate memory for the sprite.
    Sprite *sprite = (Sprite *)malloc(sizeof(struct sprite_impl));

    // Check if memory allocation was successful.
    if (sprite != NULL)
    {
        // Initialize sprite properties.
        sprite->is_visible = true;
        sprite->texture = texture;
        sprite->source = (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height};
        sprite->dest = (Rectangle){x, y, w, h};
        sprite->origin = (Vector2){0.0f, 0.0f};
        sprite->rotation = 0.0f;
        sprite->tint = (Color){255, 255, 255, 255};
    }

    // Return the pointer to the newly created sprite.
    return sprite;
}

/**
 * @brief Frees the memory allocated for a sprite.
 *
 * @param sprite A pointer to the sprite to free.
 */
void sprite_free(Sprite *sprite)
{
    // Check if the sprite pointer is valid.
    if (sprite != NULL)
    {
        // Free the memory allocated for the sprite.
        free(sprite);
        // Set the sprite pointer to NULL to prevent dangling pointers.
        sprite = NULL;
    }
}

/**
 * @brief Gets the visibility status of the sprite.
 * @param sprite The sprite to query.
 * @return True if the sprite is visible, false otherwise.
 */
bool sprite_get_is_visible(const Sprite *sprite) { return sprite->is_visible; }

/**
 * @brief Gets the texture of the sprite.
 * @param sprite The sprite to query.
 * @return The texture of the sprite.
 */
Texture2D sprite_get_texture(const Sprite *sprite) { return sprite->texture; }

/**
 * @brief Gets the source rectangle of the sprite.
 * @param sprite The sprite to query.
 * @return The source rectangle of the sprite.
 */
Rectangle sprite_get_source(const Sprite *sprite) { return sprite->source; }

/**
 * @brief Gets the destination rectangle of the sprite.
 * @param sprite The sprite to query.
 * @return The destination rectangle of the sprite.
 */
Rectangle sprite_get_dest(const Sprite *sprite) { return sprite->dest; }

/**
 * @brief Gets the origin of the sprite.
 * @param sprite The sprite to query.
 * @return The origin of the sprite.
 */
Vector2 sprite_get_origin(const Sprite *sprite) { return sprite->origin; }

/**
 * @brief Gets the rotation of the sprite in degrees.
 * @param sprite The sprite to query.
 * @return The rotation of the sprite in degrees.
 */
float sprite_get_rotation(const Sprite *sprite) { return sprite->rotation; }

/**
 * @brief Gets the tint color of the sprite.
 * @param sprite The sprite to query.
 * @return The tint color of the sprite.
 */
Color sprite_get_tint(const Sprite *sprite) { return sprite->tint; }

/**
 * @brief Sets the visibility status of the sprite.
 * @param sprite The sprite to modify.
 * @param is_visible The new visibility status of the sprite.
 */
void sprite_set_is_visible(Sprite *sprite, bool is_visible) { sprite->is_visible = is_visible; }

/**
 * @brief Sets the texture of the sprite.
 * @param sprite The sprite to modify.
 * @param texture The new texture of the sprite.
 */
void sprite_set_texture(Sprite *sprite, Texture2D texture) { sprite->texture = texture; }

/**
 * @brief Sets the source rectangle of the sprite.
 * @param sprite The sprite to modify.
 * @param source The new source rectangle of the sprite.
 */
void sprite_set_source(Sprite *sprite, Rectangle source) { sprite->source = source; }

/**
 * @brief Sets the destination rectangle of the sprite.
 * @param sprite The sprite to modify.
 * @param dest The new destination rectangle of the sprite.
 */
void sprite_set_dest(Sprite *sprite, Rectangle dest) { sprite->dest = dest; }

/**
 * @brief Sets the origin of the sprite.
 * @param sprite The sprite to modify.
 * @param origin The new origin of the sprite.
 */
void sprite_set_origin(Sprite *sprite, Vector2 origin) { sprite->origin = origin; }

/**
 * @brief Sets the rotation of the sprite in degrees.
 * @param sprite The sprite to modify.
 * @param rotation The new rotation of the sprite in degrees.
 */
void sprite_set_rotation(Sprite *sprite, float rotation) { sprite->rotation = rotation; }

/**
 * @brief Sets the tint color of the sprite.
 * @param sprite The sprite to modify.
 * @param tint The new tint color of the sprite.
 */
void sprite_set_tint(Sprite *sprite, Color tint) { sprite->tint = tint; }

/**
 * @brief Gets the x-coordinate of the sprite.
 * @param sprite The sprite to query.
 * @return The x-coordinate of the sprite.
 */
float sprite_get_x(const Sprite *sprite) { return sprite->dest.x; }

/**
 * @brief Gets the y-coordinate of the sprite.
 * @param sprite The sprite to query.
 * @return The y-coordinate of the sprite.
 */
float sprite_get_y(const Sprite *sprite) { return sprite->dest.y; }

/**
 * @brief Gets the width of the sprite.
 * @param sprite The sprite to query.
 * @return The width of the sprite.
 */
float sprite_get_w(const Sprite *sprite) { return sprite->dest.width; }

/**
 * @brief Gets the height of the sprite.
 * @param sprite The sprite to query.
 * @return The height of the sprite.
 */
float sprite_get_h(const Sprite *sprite) { return sprite->dest.height; }

/**
 * @brief Sets the x-coordinate of the sprite.
 * @param sprite The sprite to modify.
 * @param x The new x-coordinate of the sprite.
 */
void sprite_set_x(Sprite *sprite, float x) { sprite->dest.x = x; }

/**
 * @brief Sets the y-coordinate of the sprite.
 * @param sprite The sprite to modify.
 * @param y The new y-coordinate of the sprite.
 */
void sprite_set_y(Sprite *sprite, float y) { sprite->dest.y = y; }

/**
 * @brief Sets the width of the sprite.
 * @param sprite The sprite to modify.
 * @param w The new width of the sprite.
 */
void sprite_set_w(Sprite *sprite, float w) { sprite->dest.width = w; }

/**
 * @brief Sets the height of the sprite.
 * @param sprite The sprite to modify.
 * @param h The new height of the sprite.
 */
void sprite_set_h(Sprite *sprite, float h) { sprite->dest.height = h; }

/**
 * @brief Draws the sprite using raylib's DrawTexturePro function.
 *
 * @param sprite A pointer to the sprite to draw.
 */
void sprite_draw(const Sprite *sprite)
{
    // Check if the sprite is visible.
    if (!sprite->is_visible)
    {
        // If not visible, return without drawing.
        return;
    }

    // Extract sprite properties for clarity.
    Texture2D texture = sprite->texture;
    Rectangle source = sprite->source;
    Rectangle dest = sprite->dest;
    Vector2 origin = sprite->origin;
    float rotation = sprite->rotation;
    Color tint = sprite->tint;

    // Draw the sprite using raylib's DrawTexturePro function.
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
