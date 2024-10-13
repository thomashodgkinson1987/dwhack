#include "dungeon_camera.h"

#include <stdio.h>
#include <stdlib.h>

struct dungeon_camera_impl
{
    int x;
    int y;
    CardinalDirection facing;
};

DungeonCamera *dungeon_camera_create(int x, int y, CardinalDirection facing)
{
    DungeonCamera *dungeon_camera = (DungeonCamera *)malloc(sizeof(struct dungeon_camera_impl));

    if (dungeon_camera == NULL)
    {
        fprintf(stderr, "Error creating dungeon camera\n");
        exit(1);
    }

    dungeon_camera->x = x;
    dungeon_camera->y = y;
    dungeon_camera->facing = facing;

    return dungeon_camera;
}

void dungeon_camera_free(DungeonCamera *dungeon_camera)
{
    free(dungeon_camera);
    dungeon_camera = NULL;
}

int dungeon_camera_get_x(const DungeonCamera *dungeon_camera) { return dungeon_camera->x; }

int dungeon_camera_get_y(const DungeonCamera *dungeon_camera) { return dungeon_camera->y; }

CardinalDirection dungeon_camera_get_facing(const DungeonCamera *dungeon_camera) { return dungeon_camera->facing; }

void dungeon_camera_set_x(DungeonCamera *dungeon_camera, int x) { dungeon_camera->x = x; }

void dungeon_camera_set_y(DungeonCamera *dungeon_camera, int y) { dungeon_camera->y = y; }

void dungeon_camera_set_facing(DungeonCamera *dungeon_camera, CardinalDirection facing) { dungeon_camera->facing = facing; }
