#include "scene.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t vtable_count = 0;
static size_t vtable_capacity = 0;
static struct scene_funcs *vtable = NULL;

void scene_vtable_init(void)
{
    vtable_count = 0;
    vtable_capacity = 1;
    vtable = malloc(sizeof *vtable * vtable_capacity);
    assert(vtable != NULL);
    memset(vtable, 0, sizeof *vtable * vtable_capacity);

    SCENE_1_TAG = scene_vtable_register((struct scene_funcs){
        .on_enter = scene_1_on_enter,
        .on_exit = scene_1_on_exit,
        .on_tick = scene_1_on_tick,
        .on_draw = scene_1_on_draw,
        .on_free = scene_1_on_free});
}
void scene_vtable_free(void)
{
    vtable_count = 0;
    vtable_capacity = 0;
    free(vtable);
    vtable = NULL;

    SCENE_1_TAG = 0;
}
size_t scene_vtable_register(struct scene_funcs scene_funcs)
{
    if (vtable_count == vtable_capacity)
    {
        struct scene_funcs *ptr = realloc(vtable, sizeof *vtable * vtable_capacity * 2);
        assert(ptr != NULL);
        vtable = ptr;
        memset(&vtable[vtable_capacity], 0, sizeof *vtable * vtable_capacity);
        vtable_capacity *= 2;
    }

    vtable[vtable_count++] = scene_funcs;

    return vtable_count - 1;
}

struct scene scene_create(size_t tag, void *data)
{
    struct scene scene =
        {
            .tag = tag,
            .data = data};

    return scene;
}
void scene_free(struct scene *scene)
{
    if (vtable[scene->tag].on_free != NULL)
    {
        vtable[scene->tag].on_free(scene);
    }

    scene->tag = 0;

    if (scene->data != NULL)
    {
        free(scene->data);
        scene->data = NULL;
    }
}
void scene_enter(struct scene *scene)
{
    if (vtable[scene->tag].on_enter != NULL)
    {
        vtable[scene->tag].on_enter(scene);
    }
}
void scene_exit(struct scene *scene)
{
    if (vtable[scene->tag].on_exit != NULL)
    {
        vtable[scene->tag].on_exit(scene);
    }
}
void scene_tick(struct scene *scene, float delta)
{
    if (vtable[scene->tag].on_tick != NULL)
    {
        vtable[scene->tag].on_tick(scene, delta);
    }
}
void scene_draw(struct scene *scene)
{
    if (vtable[scene->tag].on_draw != NULL)
    {
        vtable[scene->tag].on_draw(scene);
    }
}

// SCENE 1

size_t SCENE_1_TAG = 0;

struct scene scene_1_create(int x, int y)
{
    struct scene_data_1 *data = malloc(sizeof *data);
    assert(data != NULL);
    memset(data, 0, sizeof *data);

    data->x = x;
    data->y = y;

    struct scene scene = scene_create(SCENE_1_TAG, data);

    return scene;
}
void scene_1_on_free(struct scene *scene)
{
    struct scene_data_1 *data = scene->data;
}
void scene_1_on_enter(struct scene *scene)
{
    struct scene_data_1 *data = scene->data;
}
void scene_1_on_exit(struct scene *scene)
{
    struct scene_data_1 *data = scene->data;
}
void scene_1_on_tick(struct scene *scene, float delta)
{
    struct scene_data_1 *data = scene->data;
}
void scene_1_on_draw(struct scene *scene)
{
    struct scene_data_1 *data = scene->data;
}
