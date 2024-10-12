#include "scene.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Global variables for managing the scene virtual function table.
static size_t vtable_count = 0;
static size_t vtable_capacity = 0;
static struct scene_funcs *vtable = NULL;

/**
 * @brief Initializes the scene virtual function table.
 * Should be called once before using any other scene functions.
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
 * @brief Frees the resources used by the scene virtual function table.
 */
void scene_vtable_free(void)
{
    vtable_count = 0;
    vtable_capacity = 0;
    free(vtable);
    vtable = NULL;
}

/**
 * @brief Registers a set of scene functions into the virtual function table.
 *
 * @param scene_funcs The function pointers to register.
 * @return A unique identifier for the registered scene functions.
 */
size_t scene_vtable_register(struct scene_funcs scene_funcs)
{
    // Double the capacity if the table is full.
    if (vtable_count == vtable_capacity)
    {
        struct scene_funcs *ptr = realloc(vtable, sizeof *vtable * vtable_capacity * 2);
        assert(ptr != NULL);
        vtable = ptr;
        memset(&vtable[vtable_capacity], 0, sizeof *vtable * vtable_capacity);
        vtable_capacity *= 2;
    }

    // Add the new functions to the table.
    vtable[vtable_count++] = scene_funcs;

    // Return the index of the newly registered functions.
    return vtable_count - 1;
}

/**
 * @brief Creates a new scene.
 *
 * @param tag Unique identifier for the scene.
 * @param data Pointer to scene-specific data.
 * @return A scene struct.  The data pointer is copied, not the data itself.
 */
struct scene scene_create(size_t tag, void *data)
{
    // Create and return a new scene struct.
    struct scene scene = {
        .tag = tag,
        .data = data,
    };

    return scene;
}

/**
 * @brief Frees the resources associated with the scene.
 */
void scene_free(struct scene *scene)
{
    // Free scene-specific resources if a free function is registered.
    if (vtable[scene->tag].free != NULL)
    {
        vtable[scene->tag].free(scene);
    }

    // Reset the scene tag.
    scene->tag = 0;

    // Free scene-specific data if it exists.
    if (scene->data != NULL)
    {
        free(scene->data);
        scene->data = NULL;
    }
}

/**
 * @brief Called when the scene is entered.
 */
void scene_enter(struct scene *scene)
{
    // Call the scene's enter function if it exists.
    if (vtable[scene->tag].enter != NULL)
    {
        vtable[scene->tag].enter(scene);
    }
}

/**
 * @brief Called when the scene is exited.
 */
void scene_exit(struct scene *scene)
{
    // Call the scene's exit function if it exists.
    if (vtable[scene->tag].exit != NULL)
    {
        vtable[scene->tag].exit(scene);
    }
}

/**
 * @brief Updates the scene's state.
 *
 * @param scene The scene to update.
 * @param delta The time delta.
 */
void scene_tick(struct scene *scene, float delta)
{
    // Call the scene's tick function if it exists.
    if (vtable[scene->tag].tick != NULL)
    {
        vtable[scene->tag].tick(scene, delta);
    }
}

/**
 * @brief Renders the scene.
 */
void scene_draw(struct scene *scene)
{
    // Call the scene's draw function if it exists.
    if (vtable[scene->tag].draw != NULL)
    {
        vtable[scene->tag].draw(scene);
    }
}
