#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

struct sprite
{
    bool is_visible;
    Texture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
};

struct sprite sprite_create(Texture2D texture, float x, float y, float w, float h);
void sprite_free(struct sprite *sprite);

bool sprite_get_is_visible(struct sprite *sprite);

Texture2D sprite_get_texture(struct sprite *sprite);

float sprite_get_x(struct sprite *sprite);
float sprite_get_y(struct sprite *sprite);
float sprite_get_w(struct sprite *sprite);
float sprite_get_h(struct sprite *sprite);

void sprite_set_is_visible(struct sprite *sprite, bool is_visible);

void sprite_set_texture(struct sprite *sprite, Texture2D texture);

void sprite_set_x(struct sprite *sprite, float x);
void sprite_set_y(struct sprite *sprite, float y);
void sprite_set_w(struct sprite *sprite, float w);
void sprite_set_h(struct sprite *sprite, float h);

void sprite_set_position(struct sprite *sprite, float x, float y);
void sprite_set_size(struct sprite *sprite, float w, float h);

void sprite_toggle_is_visible(struct sprite *sprite);

void sprite_draw(struct sprite *sprite);

#endif
