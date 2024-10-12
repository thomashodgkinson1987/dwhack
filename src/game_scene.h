#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "coords.h"
#include "enemy.h"
#include "map.h"
#include "sprite.h"

#include "raylib.h"

extern size_t GAME_SCENE_TAG;

struct game_scene_data
{
    struct coords coords;

    //

    Texture2D texture_main;

    Texture2D texture_ui_inventory;
    Texture2D texture_ui_button_camp;
    Texture2D texture_ui_equipment;
    Texture2D texture_ui_character_sheet;
    Texture2D texture_ui_minimap;
    Texture2D texture_ui_spells;
    Texture2D texture_ui_portrait_hands;
    Texture2D texture_ui_compass_north;
    Texture2D texture_ui_compass_east;
    Texture2D texture_ui_compass_south;
    Texture2D texture_ui_compass_west;
    Texture2D texture_ui_buttons_direction;

    Texture2D array_texture_backdrops[36];

    Texture2D texture_xm1y0r;
    Texture2D texture_x1y0l;

    Texture2D texture_xm1y1f;
    Texture2D texture_x0y1f;
    Texture2D texture_x1y1f;

    Texture2D texture_xm1y1r;
    Texture2D texture_x1y1l;

    Texture2D texture_xm1y2f;
    Texture2D texture_x0y2f;
    Texture2D texture_x1y2f;

    Texture2D texture_xm2y2r;
    Texture2D texture_xm1y2r;
    Texture2D texture_x1y2l;
    Texture2D texture_x2y2l;

    Texture2D texture_xm2y3f;
    Texture2D texture_xm1y3f;
    Texture2D texture_x0y3f;
    Texture2D texture_x1y3f;
    Texture2D texture_x2y3f;

    Texture2D texture_xm2y3r;
    Texture2D texture_xm1y3r;
    Texture2D texture_x1y3l;
    Texture2D texture_x2y3l;

    size_t array_textures_count;
    size_t array_textures_capacity;
    Texture2D **array_textures;

    //

    struct sprite sprite_main;

    struct sprite sprite_ui_inventory;
    struct sprite sprite_ui_button_camp;
    struct sprite sprite_ui_equipment;
    struct sprite sprite_ui_character_sheet;
    struct sprite sprite_ui_minimap;
    struct sprite sprite_ui_spells;
    struct sprite sprite_ui_portrait_hands;
    struct sprite sprite_ui_compass;
    struct sprite sprite_ui_buttons_direction;

    struct sprite sprite_backdrop;

    struct sprite sprite_xm1y0r;
    struct sprite sprite_x1y0l;

    struct sprite sprite_xm1y1f;
    struct sprite sprite_x0y1f;
    struct sprite sprite_x1y1f;

    struct sprite sprite_xm1y1r;
    struct sprite sprite_x1y1l;

    struct sprite sprite_xm1y2f;
    struct sprite sprite_x0y2f;
    struct sprite sprite_x1y2f;

    struct sprite sprite_xm2y2r;
    struct sprite sprite_xm1y2r;
    struct sprite sprite_x1y2l;
    struct sprite sprite_x2y2l;

    struct sprite sprite_xm2y3f;
    struct sprite sprite_xm1y3f;
    struct sprite sprite_x0y3f;
    struct sprite sprite_x1y3f;
    struct sprite sprite_x2y3f;

    struct sprite sprite_xm2y3r;
    struct sprite sprite_xm1y3r;
    struct sprite sprite_x1y3l;
    struct sprite sprite_x2y3l;

    size_t array_sprites_count;
    size_t array_sprites_capacity;
    struct sprite **array_sprites;

    size_t array_wall_sprites_count;
    size_t array_wall_sprites_capacity;
    struct sprite **array_wall_sprites;

    //

    struct map map;

    //

    int player_x;
    int player_y;
    int player_f;

    //

    size_t enemies_count;
    size_t enemies_capacity;
    Enemy **enemies;
};

struct scene game_scene_create(void);
void game_scene_free(struct scene *scene);

void game_scene_enter(struct scene *scene);
void game_scene_exit(struct scene *scene);
void game_scene_tick(struct scene *scene, float delta);
void game_scene_draw(struct scene *scene);

#endif
