#include "coords.h"

struct coords coords_create(void)
{
    struct coords coords = (struct coords){0};

    return coords;
}
void coords_free(struct coords *coords)
{
    *coords = (struct coords){0};
}
