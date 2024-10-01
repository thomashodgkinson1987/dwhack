#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include <stddef.h>

extern size_t GAME_SCENE_TAG;

struct game_scene_data
{

};

struct scene game_scene_create(void);
void game_scene_free(struct scene *scene);

void game_scene_on_enter(struct scene *scene);
void game_scene_on_exit(struct scene *scene);
void game_scene_on_tick(struct scene *scene, float delta);
void game_scene_on_draw(struct scene *scene);

#endif
