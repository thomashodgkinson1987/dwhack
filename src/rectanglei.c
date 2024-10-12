#include "rectanglei.h"

/**
 * @brief Creates a new rectanglei.
 *
 * @param x The x-coordinate of the top-left corner.
 * @param y The y-coordinate of the top-left corner.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 * @return struct rectanglei The created rectangle.
 */
struct rectanglei rectanglei_create(int x, int y, int w, int h)
{
    struct rectanglei rectanglei =
    {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };

    return rectanglei;
}

/**
 * @brief Frees the memory allocated for a rectanglei (does nothing in this case, as it's a simple struct).
 *
 * @param rectanglei A pointer to the rectanglei to free.
 */
void rectanglei_free(struct rectanglei *rectanglei)
{
    //In this simple case, there is no dynamic memory allocation, so nothing needs to be freed.
    rectanglei->x = 0;
    rectanglei->y = 0;
    rectanglei->w = 0;
    rectanglei->h = 0;
}
