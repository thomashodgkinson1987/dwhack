#include "rectanglei.h"

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
void rectanglei_free(struct rectanglei *rectanglei)
{
    rectanglei->x = 0;
    rectanglei->y = 0;
    rectanglei->w = 0;
    rectanglei->h = 0;
}
