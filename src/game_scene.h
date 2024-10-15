#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "coords.h"
#include "dungeon_camera.h"
#include "enemy_array.h"
#include "map.h"
#include "player.h"
#include "sprite.h"
#include "texture_resource_array.h"

#include "raylib.h"

extern size_t GAME_SCENE_TAG;

struct game_scene_data
{
    struct coords coords;

    //

    TextureResourceArray *texture_resources;

    TextureResourceArray *backdrop_texture_resources;

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

    EnemyArray *enemy_array;

    DungeonCamera *dungeon_camera;
};

Scene *game_scene_create(void);
void game_scene_free(const Scene *scene);

void game_scene_enter(const Scene *scene);
void game_scene_exit(const Scene *scene);
void game_scene_tick(const Scene *scene, float delta);
void game_scene_draw(const Scene *scene);

#endif
