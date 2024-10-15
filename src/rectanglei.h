#ifndef RECTANGLEI_H
#define RECTANGLEI_H

struct rectanglei
{
    int x;
    int y;
    int width;
    int height;
};

struct rectanglei rectanglei_create(int x, int y, int width, int height);

void rectanglei_free(struct rectanglei *rectanglei);

#endif
