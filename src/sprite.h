#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct sprite_impl Sprite;

Sprite *sprite_create(Texture2D texture, float x, float y, float w, float h);

void sprite_free(Sprite *sprite);

bool sprite_get_is_visible(const Sprite *sprite);

Texture2D sprite_get_texture(const Sprite *sprite);

Rectangle sprite_get_source(const Sprite *sprite);

Rectangle sprite_get_dest(const Sprite *sprite);

Vector2 sprite_get_origin(const Sprite *sprite);

float sprite_get_rotation(const Sprite *sprite);

Color sprite_get_tint(const Sprite *sprite);

void sprite_set_is_visible(Sprite *sprite, bool is_visible);

void sprite_set_texture(Sprite *sprite, Texture2D texture);

void sprite_set_source(Sprite *sprite, Rectangle source);

void sprite_set_dest(Sprite *sprite, Rectangle dest);

void sprite_set_origin(Sprite *sprite, Vector2 origin);

void sprite_set_rotation(Sprite *sprite, float rotation);

void sprite_set_tint(Sprite *sprite, Color tint);

float sprite_get_x(const Sprite *sprite);

float sprite_get_y(const Sprite *sprite);

float sprite_get_w(const Sprite *sprite);

float sprite_get_h(const Sprite *sprite);

void sprite_set_x(Sprite *sprite, float x);

void sprite_set_y(Sprite *sprite, float y);

void sprite_set_w(Sprite *sprite, float w);

void sprite_set_h(Sprite *sprite, float h);

void sprite_draw(const Sprite *sprite);

#endif
