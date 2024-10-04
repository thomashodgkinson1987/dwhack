#include "scene.h"

#include <assert.h>
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
}
void scene_vtable_free(void)
{
    vtable_count = 0;
    vtable_capacity = 0;
    free(vtable);
    vtable = NULL;
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
    struct scene scene = {
        .tag = tag,
        .data = data,
    };

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
