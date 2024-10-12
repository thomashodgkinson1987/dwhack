#include "scene.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Count of registered scene function tables.
 */
static size_t vtable_count = 0;
/**
 * @brief Capacity of the scene function table array.
 */
static size_t vtable_capacity = 0;
/**
 * @brief Array of scene function tables.
 */
static struct scene_funcs *vtable = NULL;

/**
 * @brief Initialize the scene virtual function table.
 */
void scene_vtable_init(void)
{
    vtable_count = 0;
    vtable_capacity = 1;
    vtable = malloc(sizeof *vtable * vtable_capacity);
    assert(vtable != NULL);
    memset(vtable, 0, sizeof *vtable * vtable_capacity);
}

/**
 * @brief Free the scene virtual function table.
 */
void scene_vtable_free(void)
{
    vtable_count = 0;
    vtable_capacity = 0;
    free(vtable);
    vtable = NULL;
}

/**
 * @brief Register a scene function table.
 *
 * @param scene_funcs The scene function table to register.
 * @return size_t The index of the registered scene function table.
 */
size_t scene_vtable_register(struct scene_funcs scene_funcs)
{
    // Resize the vtable if necessary
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

/**
 * @brief Create a new scene.
 *
 * @param tag The tag of the scene.
 * @param data The data associated with the scene.
 * @return struct scene The newly created scene.
 */
struct scene scene_create(size_t tag, void *data)
{
    struct scene scene = {
        .tag = tag,
        .data = data,
    };

    return scene;
}

/**
 * @brief Free a scene.
 *
 * @param scene The scene to free.
 */
void scene_free(struct scene *scene)
{
    // Call the scene's free function if it exists
    if (vtable[scene->tag].free != NULL)
    {
        vtable[scene->tag].free(scene);
    }

    scene->tag = 0;

    if (scene->data != NULL)
    {
        free(scene->data);
        scene->data = NULL;
    }
}

/**
 * @brief Enter a scene.
 *
 * @param scene The scene to enter.
 */
void scene_enter(struct scene *scene)
{
    // Call the scene's enter function if it exists
    if (vtable[scene->tag].enter != NULL)
    {
        vtable[scene->tag].enter(scene);
    }
}

/**
 * @brief Exit a scene.
 *
 * @param scene The scene to exit.
 */
void scene_exit(struct scene *scene)
{
    // Call the scene's exit function if it exists
    if (vtable[scene->tag].exit != NULL)
    {
        vtable[scene->tag].exit(scene);
    }
}

/**
 * @brief Update a scene.
 *
 * @param scene The scene to update.
 * @param delta The time delta.
 */
void scene_tick(struct scene *scene, float delta)
{
    // Call the scene's tick function if it exists
    if (vtable[scene->tag].tick != NULL)
    {
        vtable[scene->tag].tick(scene, delta);
    }
}

/**
 * @brief Draw a scene.
 *
 * @param scene The scene to draw.
 */
void scene_draw(struct scene *scene)
{
    // Call the scene's draw function if it exists
    if (vtable[scene->tag].draw != NULL)
    {
        vtable[scene->tag].draw(scene);
    }
}
