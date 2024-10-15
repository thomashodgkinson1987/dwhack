#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "coords.h"
#include "dungeon_camera.h"
#include "enemy_array.h"
#include "map.h"
#include "player.h"
#include "sprite_resource_array.h"
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

    SpriteResourceArray *sprite_resources;

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
