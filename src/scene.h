#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>

typedef struct scene_impl Scene;

struct scene_funcs
{
    void (*free)(const Scene *scene);
    void (*enter)(const Scene *scene);
    void (*exit)(const Scene *scene);
    void (*tick)(const Scene *scene, float delta);
    void (*draw)(const Scene *scene);
};

void scene_vtable_init(void);

void scene_vtable_free(void);

size_t scene_vtable_register(struct scene_funcs scene_funcs);

Scene *scene_create(size_t tag, void *data);

void scene_free(Scene *scene);

size_t scene_get_tag(const Scene *scene);

void *scene_get_data(const Scene *scene);

void scene_set_tag(Scene *scene, size_t tag);

void scene_set_data(Scene *scene, void *data);

void scene_enter(const Scene *scene);

void scene_exit(const Scene *scene);

void scene_tick(const Scene *scene, float delta);

void scene_draw(const Scene *scene);

#endif
