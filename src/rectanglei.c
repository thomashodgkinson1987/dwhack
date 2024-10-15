#include "rectanglei.h"

struct rectanglei rectanglei_create(int x, int y, int width, int height)
{
    struct rectanglei rectanglei = {
        .x = x,
        .y = y,
        .width = width,
        .height = height,
    };

    return rectanglei;
}

void rectanglei_free(struct rectanglei *rectanglei)
{
    *rectanglei = (struct rectanglei){0};
}
