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

float sprite_x_get(struct sprite *sprite);
float sprite_y_get(struct sprite *sprite);
float sprite_w_get(struct sprite *sprite);
float sprite_h_get(struct sprite *sprite);

void sprite_x_set(struct sprite *sprite, float x);
void sprite_y_set(struct sprite *sprite, float y);
void sprite_w_set(struct sprite *sprite, float w);
void sprite_h_set(struct sprite *sprite, float h);
void sprite_set_position(struct sprite *sprite, float x, float y);
void sprite_set_size(struct sprite *sprite, float w, float h);

void sprite_is_visible_toggle(struct sprite *sprite);

void sprite_draw(struct sprite *sprite);

#endif
