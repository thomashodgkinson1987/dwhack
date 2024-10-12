#include "rectanglei.h"
#include <string.h>

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
 * @brief Frees the memory allocated for a rectanglei. Sets all members to zero.
 *
 * @param rectanglei A pointer to the rectanglei to clear.
 */
void rectanglei_free(struct rectanglei *rectanglei)
{
    memset(rectanglei, 0, sizeof(struct rectanglei));
}
