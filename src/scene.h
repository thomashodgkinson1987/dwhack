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
    void(*on_free)(struct scene *scene);
    void(*on_enter)(struct scene *scene);
    void(*on_exit)(struct scene *scene);
    void(*on_tick)(struct scene *scene, float delta);
    void(*on_draw)(struct scene *scene);
};

void scene_vtable_init(void);
void scene_vtable_free(void);
size_t scene_vtable_register(struct scene_funcs scene_funcs);

struct scene scene_create(size_t tag, void *data);
void scene_free(struct scene *scene);
void scene_enter(struct scene *scene);
void scene_exit(struct scene *scene);
void scene_tick(struct scene *scene, float delta);
void scene_draw(struct scene *scene);

// SCENE 1

extern size_t SCENE_1_TAG;

struct scene_data_1
{
    int x;
    int y;
};

struct scene scene_1_create(int x, int y);
void scene_1_on_free(struct scene *scene);
void scene_1_on_enter(struct scene *scene);
void scene_1_on_exit(struct scene *scene);
void scene_1_on_tick(struct scene *scene, float delta);
void scene_1_on_draw(struct scene *scene);

#endif
