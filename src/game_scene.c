#include "game_scene.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

size_t GAME_SCENE_TAG = 0;

struct scene game_scene_create(void)
{
    struct game_scene_data *data = malloc(sizeof *data);
    assert(data != NULL);
    memset(data, 0, sizeof *data);

    struct scene scene = scene_create(GAME_SCENE_TAG, data);

    return scene;
}
void game_scene_free(struct scene *scene)
{
    struct game_scene_data *data = scene->data;
}

void game_scene_on_enter(struct scene *scene)
{
    struct game_scene_data *data = scene->data;
}
void game_scene_on_exit(struct scene *scene)
{
    struct game_scene_data *data = scene->data;
}
void game_scene_on_tick(struct scene *scene, float delta)
{
    struct game_scene_data *data = scene->data;
}
void game_scene_on_exit(struct scene *scene)
{
    struct game_scene_data *data = scene->data;
}
