#ifndef RECTANGLEI_H
#define RECTANGLEI_H

struct rectanglei
{
    int x, y, w, h;
};

struct rectanglei rectanglei_create(int x, int y, int w, int h);
void rectanglei_free(struct rectanglei *rectanglei);

#endif
