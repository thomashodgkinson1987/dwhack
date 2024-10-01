#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>

struct scene
{
    size_t tag;
    void *data;
};

struct scene_funcs
{
    void(*on_enter)(struct scene *scene);
    void(*on_exit)(struct scene *scene);
    void(*on_tick)(struct scene *scene, float delta);
    void(*on_draw)(struct scene *scene);
    void(*on_free)(struct scene *scene);
};

void scene_vtable_init(void);
void scene_vtable_free(void);

size_t scene_register_type(struct scene_funcs scene_funcs);

void scene_on_enter(struct scene *scene);
void scene_on_exit(struct scene *scene);
void scene_on_tick(struct scene *scene, float delta);
void scene_on_draw(struct scene *scene);
void scene_on_free(struct scene *scene);

// SCENE 1

struct scene_data_1
{
    int x;
    int y;
};

struct scene scene_1_create(int x, int y);
void scene_1_on_enter(struct scene *scene);
void scene_1_on_exit(struct scene *scene);
void scene_1_on_tick(struct scene *scene, float delta);
void scene_1_on_draw(struct scene *scene);
void scene_1_on_free(struct scene *scene);

#endif
