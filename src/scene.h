#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>

/**
 * @brief Represents a scene in the game or application.
 * 
 * This structure holds a tag for identification and a pointer to arbitrary data.
 */
struct scene
{
    /** @brief Unique identifier for the scene. */
    size_t tag;
    /** @brief Pointer to scene-specific data. */
    void *data;
};

/**
 * @brief Function pointers for scene management.
 * 
 * This structure defines a set of function pointers for managing the lifecycle of a scene.
 */
struct scene_funcs
{
    /** @brief Frees the resources associated with the scene. */
    void(*free)(struct scene *scene);
    /** @brief Called when the scene is entered. */
    void(*enter)(struct scene *scene);
    /** @brief Called when the scene is exited. */
    void(*exit)(struct scene *scene);
    /** @brief Updates the scene's state. */
    void(*tick)(struct scene *scene, float delta);  /* delta: time since last tick */
    /** @brief Renders the scene. */
    void(*draw)(struct scene *scene);
};

/** @brief Initializes the scene virtual function table.  Should be called once before using any other scene functions. */
void scene_vtable_init(void);
/** @brief Frees the resources used by the scene virtual function table. */
void scene_vtable_free(void);
/**
 * @brief Registers a set of scene functions into the virtual function table.
 * 
 * @param scene_funcs The function pointers to register.
 * @return A unique identifier for the registered scene functions.  Returns 0 on failure.
 */
size_t scene_vtable_register(struct scene_funcs scene_funcs);

/**
 * @brief Creates a new scene.
 * 
 * @param tag Unique identifier for the scene.
 * @param data Pointer to scene-specific data.
 * @return A scene struct.  The data pointer is copied, not the data itself.
 */
struct scene scene_create(size_t tag, void *data);
/** @brief Frees the resources associated with the scene. */
void scene_free(struct scene *scene);
/** @brief Called when the scene is entered. */
void scene_enter(struct scene *scene);
/** @brief Called when the scene is exited. */
void scene_exit(struct scene *scene);
/** @brief Updates the scene's state. */
void scene_tick(struct scene *scene, float delta);
/** @brief Renders the scene. */
void scene_draw(struct scene *scene);

#endif
