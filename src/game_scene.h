#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "coords.h"
#include "dungeon_camera.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "sprite.h"

#include "raylib.h"

extern size_t GAME_SCENE_TAG;

typedef struct
{
    size_t count;
    size_t capacity;
    Enemy **enemies;
} EnemyArray;

typedef struct
{
    char *name;
    Texture2D texture;
} TextureResource;

typedef struct
{
    size_t count;
    size_t capacity;
    TextureResource *texture_resources;
} TextureResourceArray;

struct game_scene_data
{
    struct coords coords;

    //

    TextureResourceArray texture_resource_array;

    size_t backdrop_textures_count;
    size_t backdrop_textures_capacity;
    TextureResource **backdrop_textures;

    //

    Sprite *sprite_main;

    Sprite *sprite_ui_inventory;
    Sprite *sprite_ui_button_camp;
    Sprite *sprite_ui_equipment;
    Sprite *sprite_ui_character_sheet;
    Sprite *sprite_ui_minimap;
    Sprite *sprite_ui_spells;
    Sprite *sprite_ui_portrait_hands;
    Sprite *sprite_ui_compass;
    Sprite *sprite_ui_buttons_direction;

    Sprite *sprite_backdrop;

    Sprite *sprite_xm1y0r;
    Sprite *sprite_x1y0l;

    Sprite *sprite_xm1y1f;
    Sprite *sprite_x0y1f;
    Sprite *sprite_x1y1f;

    Sprite *sprite_xm1y1r;
    Sprite *sprite_x1y1l;

    Sprite *sprite_xm1y2f;
    Sprite *sprite_x0y2f;
    Sprite *sprite_x1y2f;

    Sprite *sprite_xm2y2r;
    Sprite *sprite_xm1y2r;
    Sprite *sprite_x1y2l;
    Sprite *sprite_x2y2l;

    Sprite *sprite_xm2y3f;
    Sprite *sprite_xm1y3f;
    Sprite *sprite_x0y3f;
    Sprite *sprite_x1y3f;
    Sprite *sprite_x2y3f;

    Sprite *sprite_xm2y3r;
    Sprite *sprite_xm1y3r;
    Sprite *sprite_x1y3l;
    Sprite *sprite_x2y3l;

    size_t sprites_count;
    size_t sprites_capacity;
    Sprite **sprites;

    //

    size_t wall_sprites_count;
    size_t wall_sprites_capacity;
    Sprite **wall_sprites;

    //

    Map *map;

    Player *player;

    EnemyArray enemy_array;

    DungeonCamera *dungeon_camera;
};

struct scene game_scene_create(void);
void game_scene_free(struct scene *scene);

void game_scene_enter(struct scene *scene);
void game_scene_exit(struct scene *scene);
void game_scene_tick(struct scene *scene, float delta);
void game_scene_draw(struct scene *scene);

#endif
