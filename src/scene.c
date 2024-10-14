#include "scene.h"

#include <stdio.h>
#include <stdlib.h>

struct scene_impl
{
    size_t tag;
    void *data;
};

struct scene_funcs_impl
{
    void (*free)(const Scene *scene);
    void (*enter)(const Scene *scene);
    void (*exit)(const Scene *scene);
    void (*tick)(const Scene *scene, float delta);
    void (*draw)(const Scene *scene);
};

typedef struct
{
    size_t count;
    size_t capacity;
    struct scene_funcs *data;
} SceneFuncsArray;

static SceneFuncsArray scene_funcs_array;

void scene_vtable_init(void)
{
    size_t count = 0;
    size_t capacity = 1;
    struct scene_funcs *data = malloc(sizeof *data * capacity);

    if (data == NULL)
    {
        fprintf(stderr, "Error creating scene funcs array\n");
        exit(1);
    }

    scene_funcs_array = (SceneFuncsArray){
        .count = count,
        .capacity = capacity,
        .data = data};
}

void scene_vtable_free(void)
{
    free(scene_funcs_array.data);
    scene_funcs_array = (SceneFuncsArray){0};
}

size_t scene_vtable_register(struct scene_funcs scene_funcs)
{
    if (scene_funcs_array.count == scene_funcs_array.capacity)
    {
        struct scene_funcs *ptr = realloc(scene_funcs_array.data, sizeof *scene_funcs_array.data * scene_funcs_array.capacity * 2);
        if (ptr == NULL)
        {
            fprintf(stderr, "Error reallocating scene funcs array\n");
            exit(1);
        }
        for (size_t i = scene_funcs_array.capacity; i < scene_funcs_array.capacity * 2; ++i)
        {
            ptr[i] = (struct scene_funcs){0};
        }
        scene_funcs_array.capacity *= 2;
        scene_funcs_array.data = ptr;
    }

    scene_funcs_array.data[scene_funcs_array.count++] = scene_funcs;

    return scene_funcs_array.count - 1;
}

Scene *scene_create(size_t tag, void *data)
{
    Scene *scene = malloc(sizeof *scene);

    if (scene == NULL)
    {
        fprintf(stderr, "Error creating scene\n");
        exit(1);
    }

    scene->tag = tag;
    scene->data = data;

    return scene;
}

void scene_free(Scene *scene)
{
    if (scene_funcs_array.data[scene->tag].free != NULL)
    {
        scene_funcs_array.data[scene->tag].free(scene);
    }

    if (scene->data != NULL)
    {
        free(scene->data);
    }

    free(scene);
    scene = NULL;
}

size_t scene_get_tag(const Scene *scene) { return scene->tag; }

void *scene_get_data(const Scene *scene) { return scene->data; }

void scene_set_tag(Scene *scene, size_t tag) { scene->tag = tag; }

void scene_set_data(Scene *scene, void *data) { scene->data = data; }

void scene_enter(const Scene *scene)
{
    if (scene_funcs_array.data[scene->tag].enter != NULL)
    {
        scene_funcs_array.data[scene->tag].enter(scene);
    }
}

void scene_exit(const Scene *scene)
{
    if (scene_funcs_array.data[scene->tag].exit != NULL)
    {
        scene_funcs_array.data[scene->tag].exit(scene);
    }
}

void scene_tick(const Scene *scene, float delta)
{
    if (scene_funcs_array.data[scene->tag].tick != NULL)
    {
        scene_funcs_array.data[scene->tag].tick(scene, delta);
    }
}

void scene_draw(const Scene *scene)
{
    if (scene_funcs_array.data[scene->tag].draw != NULL)
    {
        scene_funcs_array.data[scene->tag].draw(scene);
    }
}
