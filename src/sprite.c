#include "sprite.h"

#include "raylib.h"

#include <stdlib.h>

struct sprite_impl
{
    bool is_visible;
    Texture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
};

Sprite *sprite_create(Texture2D texture, float x, float y, float width, float height)
{
    Sprite *sprite = (Sprite *)malloc(sizeof(struct sprite_impl));
    if (sprite != NULL)
    {
        sprite->is_visible = true;
        sprite->texture = texture;
        sprite->source = (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height};
        sprite->dest = (Rectangle){x, y, width, height};
        sprite->origin = (Vector2){0.0f, 0.0f};
        sprite->rotation = 0.0f;
        sprite->tint = (Color){255, 255, 255, 255};
    }
    return sprite;
}

void sprite_free(Sprite *sprite)
{
    if (sprite != NULL)
    {
        free(sprite);
        sprite = NULL;
    }
}

bool sprite_get_is_visible(const Sprite *sprite) { return sprite->is_visible; }

Texture2D sprite_get_texture(const Sprite *sprite) { return sprite->texture; }

Rectangle sprite_get_source(const Sprite *sprite) { return sprite->source; }

Rectangle sprite_get_dest(const Sprite *sprite) { return sprite->dest; }

Vector2 sprite_get_origin(const Sprite *sprite) { return sprite->origin; }

float sprite_get_rotation(const Sprite *sprite) { return sprite->rotation; }

Color sprite_get_tint(const Sprite *sprite) { return sprite->tint; }

void sprite_set_is_visible(Sprite *sprite, bool is_visible) { sprite->is_visible = is_visible; }

void sprite_set_texture(Sprite *sprite, Texture2D texture) { sprite->texture = texture; }

void sprite_set_source(Sprite *sprite, Rectangle source) { sprite->source = source; }

void sprite_set_dest(Sprite *sprite, Rectangle dest) { sprite->dest = dest; }

void sprite_set_origin(Sprite *sprite, Vector2 origin) { sprite->origin = origin; }

void sprite_set_rotation(Sprite *sprite, float rotation) { sprite->rotation = rotation; }

void sprite_set_tint(Sprite *sprite, Color tint) { sprite->tint = tint; }

float sprite_get_x(const Sprite *sprite) { return sprite->dest.x; }

float sprite_get_y(const Sprite *sprite) { return sprite->dest.y; }

float sprite_get_width(const Sprite *sprite) { return sprite->dest.width; }

float sprite_get_height(const Sprite *sprite) { return sprite->dest.height; }

void sprite_set_x(Sprite *sprite, float x) { sprite->dest.x = x; }

void sprite_set_y(Sprite *sprite, float y) { sprite->dest.y = y; }

void sprite_set_width(Sprite *sprite, float width) { sprite->dest.width = width; }

void sprite_set_height(Sprite *sprite, float height) { sprite->dest.height = height; }

void sprite_draw(const Sprite *sprite)
{
    if (!sprite->is_visible)
    {
        return;
    }
    Texture2D texture = sprite->texture;
    Rectangle source = sprite->source;
    Rectangle dest = sprite->dest;
    Vector2 origin = sprite->origin;
    float rotation = sprite->rotation;
    Color tint = sprite->tint;
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
