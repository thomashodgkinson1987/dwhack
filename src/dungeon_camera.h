#ifndef DUNGEON_CAMERA_H
#define DUNGEON_CAMERA_H

#include "cardinal_directions.h"

typedef struct dungeon_camera_impl DungeonCamera;

DungeonCamera *dungeon_camera_create(int x, int y, CardinalDirection facing);

void dungeon_camera_free(DungeonCamera *dungeon_camera);

int dungeon_camera_get_x(const DungeonCamera *dungeon_camera);

int dungeon_camera_get_y(const DungeonCamera *dungeon_camera);

CardinalDirection dungeon_camera_get_facing(const DungeonCamera *dungeon_camera);

void dungeon_camera_set_x(DungeonCamera *dungeon_camera, int x);

void dungeon_camera_set_y(DungeonCamera *dungeon_camera, int y);

void dungeon_camera_set_facing(DungeonCamera *dungeon_camera, CardinalDirection facing);

#endif
