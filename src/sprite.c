#include "sprite.h"

#include "raylib.h"

struct sprite sprite_create(Texture2D texture, float x, float y, float w, float h)
{
    struct sprite sprite = {0};

    sprite.is_visible = true;
    sprite.texture = texture;
    sprite.source = (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height};
    sprite.dest = (Rectangle){x, y, w, h};
    sprite.origin = (Vector2){0.0f, 0.0f};
    sprite.rotation = 0.0f;
    sprite.tint = WHITE;

    return sprite;
}

void sprite_free(struct sprite *sprite)
{
    sprite->is_visible = 0;
    sprite->texture = (Texture2D){0};
    sprite->source = (Rectangle){0};
    sprite->dest = (Rectangle){0};
    sprite->origin = (Vector2){0};
    sprite->rotation = 0.0f;
    sprite->tint = BLANK;
}

bool sprite_get_is_visible(struct sprite *sprite)
{
    return sprite->is_visible;
}

Texture2D sprite_get_texture(struct sprite *sprite)
{
    return sprite->texture;
}

float sprite_get_x(struct sprite *sprite)
{
    return sprite->dest.x;
}
float sprite_get_y(struct sprite *sprite)
{
    return sprite->dest.y;
}
float sprite_get_w(struct sprite *sprite)
{
    return sprite->dest.width;
}
float sprite_get_h(struct sprite *sprite)
{
    return sprite->dest.height;
}

void sprite_set_is_visible(struct sprite *sprite, bool is_visible)
{
    sprite->is_visible = is_visible;
}

void sprite_set_texture(struct sprite *sprite, Texture2D texture)
{
    sprite->texture = texture;
}

void sprite_set_x(struct sprite *sprite, float x)
{
    sprite->dest.x = x;
}
void sprite_set_y(struct sprite *sprite, float y)
{
    sprite->dest.y = y;
}
void sprite_set_w(struct sprite *sprite, float w)
{
    sprite->dest.width = w;
}
void sprite_set_h(struct sprite *sprite, float h)
{
    sprite->dest.height = h;
}

void sprite_set_position(struct sprite *sprite, float x, float y)
{
    sprite_set_x(sprite, x);
    sprite_set_y(sprite, y);
}
void sprite_set_size(struct sprite *sprite, float w, float h)
{
    sprite_set_w(sprite, w);
    sprite_set_h(sprite, h);
}

void sprite_toggle_is_visible(struct sprite *sprite)
{
    sprite->is_visible = !sprite->is_visible;
}

void sprite_draw(struct sprite *sprite)
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
