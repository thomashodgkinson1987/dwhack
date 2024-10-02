#ifndef COORDS_H
#define COORDS_H

#include "rectanglei.h"

struct coords
{
    struct rectanglei main;

    struct rectanglei ui_inventory;
    struct rectanglei ui_camp_button;
    struct rectanglei ui_equipment;
    struct rectanglei ui_character_sheet;
    struct rectanglei ui_minimap;
    struct rectanglei ui_spells;
    struct rectanglei ui_portrait_hands;
    struct rectanglei ui_compass;
    struct rectanglei ui_movement_buttons;

    struct rectanglei backdrop;

    struct rectanglei xm1y0r;
    struct rectanglei x1y0l;

    struct rectanglei xm1y1f;
    struct rectanglei x0y1f;
    struct rectanglei x1y1f;

    struct rectanglei xm1y1r;
    struct rectanglei x1y1l;

    struct rectanglei xm1y2f;
    struct rectanglei x0y2f;
    struct rectanglei x1y2f;

    struct rectanglei xm2y2r;
    struct rectanglei xm1y2r;
    struct rectanglei x1y2l;
    struct rectanglei x2y2l;

    struct rectanglei xm2y3f;
    struct rectanglei xm1y3f;
    struct rectanglei x0y3f;
    struct rectanglei x1y3f;
    struct rectanglei x2y3f;

    struct rectanglei xm2y3r;
    struct rectanglei xm1y3r;
    struct rectanglei x1y3l;
    struct rectanglei x2y3l;
};

struct coords coords_create(void);
void coords_free(struct coords *coords);

#endif
