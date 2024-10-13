#include "game_scene.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void game_scene_init_coords(struct scene *scene);
static void game_scene_init_textures(struct scene *scene);
static void game_scene_init_sprites(struct scene *scene);
static void game_scene_init_map(struct scene *scene);
static void game_scene_init_player(struct scene *scene);
static void game_scene_init_enemies(struct scene *scene);
static void game_scene_init_dungeon_camera(struct scene *scene);

static void game_scene_free_coords(struct scene *scene);
static void game_scene_free_textures(struct scene *scene);
static void game_scene_free_sprites(struct scene *scene);
static void game_scene_free_map(struct scene *scene);
static void game_scene_free_player(struct scene *scene);
static void game_scene_free_enemies(struct scene *scene);
static void game_scene_free_dungeon_camera(struct scene *scene);

static void game_scene_draw_world(struct scene *scene);
static void game_scene_draw_main(struct scene *scene);
static void game_scene_draw_ui(struct scene *scene);

static void game_scene_update_dungeon_camera(struct scene *scene);
static void game_scene_update_compass(struct scene *scene);
static void game_scene_recalculate_visible_walls(struct scene *scene);
static void game_scene_flip_backdrop(struct scene *scene);

static void game_scene_calculate_target_position(int *target_x, int *target_y, int x, int y, int *front_vec, int front_distance, int *side_vec, int side_distance);
static bool game_scene_is_wall_at(Map *map, int x, int y);

size_t GAME_SCENE_TAG = 0;

struct scene game_scene_create(void)
{
    struct game_scene_data *data = malloc(sizeof *data);

    if (data == NULL)
    {
        fprintf(stderr, "Error creating game_scene_data\n");
        exit(1);
    }

    memset(data, 0, sizeof *data);

    struct scene scene = scene_create(GAME_SCENE_TAG, data);

    game_scene_init_coords(&scene);
    game_scene_init_textures(&scene);
    game_scene_init_sprites(&scene);
    game_scene_init_map(&scene);
    game_scene_init_player(&scene);
    game_scene_init_enemies(&scene);
    game_scene_init_dungeon_camera(&scene);

    return scene;
}
void game_scene_free(struct scene *scene)
{
    game_scene_free_dungeon_camera(scene);
    game_scene_free_enemies(scene);
    game_scene_free_player(scene);
    game_scene_free_map(scene);
    game_scene_free_sprites(scene);
    game_scene_free_textures(scene);
    game_scene_free_coords(scene);
}

void game_scene_enter(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    sprite_set_is_visible(data->sprite_ui_character_sheet, false);
    sprite_set_is_visible(data->sprite_ui_spells, false);

    sprite_set_texture(data->sprite_backdrop, data->array_texture_backdrops[GetRandomValue(0, (sizeof(data->array_texture_backdrops) / sizeof(Texture2D)) - 1)]);

    game_scene_update_dungeon_camera(scene);
    game_scene_update_compass(scene);
    game_scene_recalculate_visible_walls(scene);
}
void game_scene_exit(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    (void)data;
}
void game_scene_tick(struct scene *scene, float delta)
{
    struct game_scene_data *data = scene->data;

    (void)delta;

    if (IsKeyPressed(KEY_Z))
    {
        for (size_t i = 0; i < data->enemy_array.count; ++i)
        {
            Enemy *enemy = data->enemy_array.enemies[i];

            int move_state = GetRandomValue(0, 1);
            int dx = GetRandomValue(-1, 1);
            int dy = GetRandomValue(-1, 1);

            if (move_state == 0)
            {
                dy = 0;
            }
            else if (move_state == 1)
            {
                dx = 0;
            }

            int new_x = enemy_get_x(enemy) + dx;
            int new_y = enemy_get_y(enemy) + dy;

            if (new_x >= 0 && new_x < (int)map_get_width(data->map) && new_y >= 0 && new_y < (int)map_get_height(data->map))
            {
                if (map_data_get_at(data->map, new_x, new_y) == 0)
                {
                    enemy_set_x(enemy, new_x);
                    enemy_set_y(enemy, new_y);
                }
            }
        }
    }

    if (IsKeyPressed(KEY_C))
    {
        sprite_set_is_visible(data->sprite_ui_inventory, !sprite_get_is_visible(data->sprite_ui_inventory));
        sprite_set_is_visible(data->sprite_ui_equipment, !sprite_get_is_visible(data->sprite_ui_equipment));
        sprite_set_is_visible(data->sprite_ui_character_sheet, !sprite_get_is_visible(data->sprite_ui_character_sheet));
        sprite_set_is_visible(data->sprite_ui_minimap, !sprite_get_is_visible(data->sprite_ui_minimap));
    }

    if (IsKeyPressed(KEY_Q) && !IsKeyPressed(KEY_E))
    {
        CardinalDirection new_facing = (CardinalDirection)((player_get_facing(data->player) + 3) % 4);
        player_set_facing(data->player, new_facing);
        game_scene_update_dungeon_camera(scene);
        game_scene_update_compass(scene);
        game_scene_flip_backdrop(scene);
        game_scene_recalculate_visible_walls(scene);
    }
    else if (!IsKeyPressed(KEY_Q) && IsKeyPressed(KEY_E))
    {
        CardinalDirection new_facing = (CardinalDirection)((player_get_facing(data->player) + 1) % 4);
        player_set_facing(data->player, new_facing);
        game_scene_update_dungeon_camera(scene);
        game_scene_update_compass(scene);
        game_scene_flip_backdrop(scene);
        game_scene_recalculate_visible_walls(scene);
    }
    else
    {
        int dir_vecs[4][2] = {
            {0, -1},
            {1, 0},
            {0, 1},
            {-1, 0}};

        int movement_vec[2] = {0, 0};

        if (IsKeyPressed(KEY_W) && !IsKeyPressed(KEY_S) && !IsKeyPressed(KEY_A) && !IsKeyPressed(KEY_D))
        {
            movement_vec[0] += dir_vecs[player_get_facing(data->player)][0];
            movement_vec[1] += dir_vecs[player_get_facing(data->player)][1];
        }
        else if (!IsKeyPressed(KEY_W) && IsKeyPressed(KEY_S) && !IsKeyPressed(KEY_A) && !IsKeyPressed(KEY_D))
        {
            movement_vec[0] -= dir_vecs[player_get_facing(data->player)][0];
            movement_vec[1] -= dir_vecs[player_get_facing(data->player)][1];
        }
        else if (!IsKeyPressed(KEY_W) && !IsKeyPressed(KEY_S) && IsKeyPressed(KEY_A) && !IsKeyPressed(KEY_D))
        {
            int left_f = (player_get_facing(data->player) + 3) % 4;
            movement_vec[0] += dir_vecs[left_f][0];
            movement_vec[1] += dir_vecs[left_f][1];
        }
        if (!IsKeyPressed(KEY_W) && !IsKeyPressed(KEY_S) && !IsKeyPressed(KEY_A) && IsKeyPressed(KEY_D))
        {
            int right_f = (player_get_facing(data->player) + 1) % 4;
            movement_vec[0] += dir_vecs[right_f][0];
            movement_vec[1] += dir_vecs[right_f][1];
        }

        if (movement_vec[0] != 0 || movement_vec[1] != 0)
        {
            int new_x = player_get_x(data->player) + movement_vec[0];
            int new_y = player_get_y(data->player) + movement_vec[1];

            if (new_x >= 0 && new_x < (int)map_get_width(data->map) && new_y >= 0 && new_y < (int)map_get_height(data->map))
            {
                if (map_data_get_at(data->map, new_x, new_y) == 0)
                {
                    player_set_x(data->player, new_x);
                    player_set_y(data->player, new_y);
                    game_scene_update_dungeon_camera(scene);
                    game_scene_flip_backdrop(scene);
                    game_scene_recalculate_visible_walls(scene);
                }
            }
        }
    }
}
void game_scene_draw(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    (void)data;

    game_scene_draw_world(scene);
    game_scene_draw_main(scene);
    game_scene_draw_ui(scene);
}
static void game_scene_draw_world(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    int map_width = (int)map_get_width(data->map);
    int map_height = (int)map_get_height(data->map);

    int dir_vecs[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0}};

    int front_f = dungeon_camera_get_facing(data->dungeon_camera);
    // int left_f = (front_f + 3) % 4;
    int right_f = (front_f + 1) % 4;

    int *front_vec = dir_vecs[front_f];
    // int *left_vec = dir_vecs[left_f];
    int *right_vec = dir_vecs[right_f];

    struct enemy_position_check
    {
        int forward_distance;
        int sizeways_distance;
        int offset_x;
        int offset_y;
        float radius;
    };

    sprite_draw(data->sprite_backdrop);

    sprite_draw(data->sprite_xm2y3r);
    sprite_draw(data->sprite_xm1y3r);
    sprite_draw(data->sprite_x1y3l);
    sprite_draw(data->sprite_x2y3l);

    {
        struct enemy_position_check checks[] = {
            {3, -2, data->coords.xm2y3f.x + 40, data->coords.xm2y3f.y + 12, 4.0f},
            {3, -1, data->coords.xm1y3f.x + 30, data->coords.xm1y3f.y + 12, 4.0f},
            {3, 0, data->coords.x0y3f.x + 24, data->coords.x0y3f.y + 12, 4.0f},
            {3, 1, data->coords.x1y3f.x + data->coords.x1y3f.w - 30, data->coords.x1y3f.y + 12, 4.0f},
            {3, 2, data->coords.x2y3f.x + data->coords.x2y3f.w - 40, data->coords.x2y3f.y + 12, 4.0f},
        };

        for (size_t i = 0; i < sizeof(checks) / sizeof(checks[0]); ++i)
        {
            struct enemy_position_check *check = &checks[i];

            int target_x = dungeon_camera_get_x(data->dungeon_camera) + front_vec[0] * check->forward_distance + right_vec[0] * check->sizeways_distance;
            int target_y = dungeon_camera_get_y(data->dungeon_camera) + front_vec[1] * check->forward_distance + right_vec[1] * check->sizeways_distance;

            if (target_x >= 0 && target_x < map_width && target_y >= 0 && target_y < map_height)
            {
                for (size_t j = 0; j < data->enemy_array.count; ++j)
                {
                    Enemy *enemy = data->enemy_array.enemies[j];
                    if (enemy_get_x(enemy) == target_x && enemy_get_y(enemy) == target_y)
                    {
                        DrawCircle(check->offset_x, check->offset_y, check->radius, enemy_get_color(enemy));
                    }
                }
            }
        }
    }

    sprite_draw(data->sprite_xm2y3f);
    sprite_draw(data->sprite_xm1y3f);
    sprite_draw(data->sprite_x0y3f);
    sprite_draw(data->sprite_x1y3f);
    sprite_draw(data->sprite_x2y3f);

    sprite_draw(data->sprite_xm2y2r);
    sprite_draw(data->sprite_xm1y2r);
    sprite_draw(data->sprite_x1y2l);
    sprite_draw(data->sprite_x2y2l);

    {
        struct enemy_position_check checks[] = {
            {2, -1, data->coords.xm1y3f.x + 24, data->coords.xm1y3f.y + 16, 8.0f},
            {2, 0, data->coords.x0y3f.x + 24, data->coords.x0y3f.y + 16, 8.0f},
            {2, 1, data->coords.x1y3f.x + 24, data->coords.x1y3f.y + 16, 8.0f},
        };

        for (size_t i = 0; i < sizeof(checks) / sizeof(checks[0]); ++i)
        {
            struct enemy_position_check *check = &checks[i];

            int target_x = dungeon_camera_get_x(data->dungeon_camera) + front_vec[0] * check->forward_distance + right_vec[0] * check->sizeways_distance;
            int target_y = dungeon_camera_get_y(data->dungeon_camera) + front_vec[1] * check->forward_distance + right_vec[1] * check->sizeways_distance;

            if (target_x >= 0 && target_x < map_width && target_y >= 0 && target_y < map_height)
            {
                for (size_t j = 0; j < data->enemy_array.count; ++j)
                {
                    Enemy *enemy = data->enemy_array.enemies[j];
                    if (enemy_get_x(enemy) == target_x && enemy_get_y(enemy) == target_y)
                    {
                        DrawCircle(check->offset_x, check->offset_y, check->radius, enemy_get_color(enemy));
                    }
                }
            }
        }
    }

    sprite_draw(data->sprite_xm1y2f);
    sprite_draw(data->sprite_x0y2f);
    sprite_draw(data->sprite_x1y2f);

    sprite_draw(data->sprite_xm1y1r);
    sprite_draw(data->sprite_x1y1l);

    {
        struct enemy_position_check checks[] = {
            {1, -1, data->coords.xm1y2f.x + 40, data->coords.xm1y2f.y + 30, 16.0f},
            {1, 0, data->coords.x0y2f.x + 40, data->coords.x0y2f.y + 30, 16.0f},
            {1, 1, data->coords.x1y2f.x + 40, data->coords.x1y2f.y + 30, 16.0f},
        };

        for (size_t i = 0; i < sizeof(checks) / sizeof(checks[0]); ++i)
        {
            struct enemy_position_check *check = &checks[i];

            int target_x = dungeon_camera_get_x(data->dungeon_camera) + front_vec[0] * check->forward_distance + right_vec[0] * check->sizeways_distance;
            int target_y = dungeon_camera_get_y(data->dungeon_camera) + front_vec[1] * check->forward_distance + right_vec[1] * check->sizeways_distance;

            if (target_x >= 0 && target_x < map_width && target_y >= 0 && target_y < map_height)
            {
                for (size_t j = 0; j < data->enemy_array.count; ++j)
                {
                    Enemy *enemy = data->enemy_array.enemies[j];
                    if (enemy_get_x(enemy) == target_x && enemy_get_y(enemy) == target_y)
                    {
                        DrawCircle(check->offset_x, check->offset_y, check->radius, enemy_get_color(enemy));
                    }
                }
            }
        }
    }

    sprite_draw(data->sprite_xm1y1f);
    sprite_draw(data->sprite_x0y1f);
    sprite_draw(data->sprite_x1y1f);

    sprite_draw(data->sprite_xm1y0r);
    sprite_draw(data->sprite_x1y0l);
}
static void game_scene_draw_main(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    sprite_draw(data->sprite_main);
}
static void game_scene_draw_ui(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    sprite_draw(data->sprite_ui_inventory);
    sprite_draw(data->sprite_ui_button_camp);
    sprite_draw(data->sprite_ui_equipment);
    sprite_draw(data->sprite_ui_character_sheet);
    sprite_draw(data->sprite_ui_minimap);
    sprite_draw(data->sprite_ui_spells);
    sprite_draw(data->sprite_ui_portrait_hands);
    sprite_draw(data->sprite_ui_compass);
    sprite_draw(data->sprite_ui_buttons_direction);
}

static void game_scene_init_coords(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    data->coords = coords_create();

    data->coords.main = (struct rectanglei){0, 0, 320, 200};

    data->coords.ui_inventory = (struct rectanglei){0, 0, 36, 182};
    data->coords.ui_camp_button = (struct rectanglei){0, 181, 37, 19};
    data->coords.ui_equipment = (struct rectanglei){36, 0, 100, 132};
    data->coords.ui_character_sheet = (struct rectanglei){0, 0, 136, 182};
    data->coords.ui_minimap = (struct rectanglei){54, 139, 58, 42};
    data->coords.ui_spells = (struct rectanglei){37, 137, 99, 44};
    data->coords.ui_portrait_hands = (struct rectanglei){139, 136, 66, 44};
    data->coords.ui_compass = (struct rectanglei){210, 134, 45, 44};
    data->coords.ui_movement_buttons = (struct rectanglei){260, 136, 58, 44};

    data->coords.backdrop = (struct rectanglei){138, 13, 176, 120};

    data->coords.xm1y0r = (struct rectanglei){138, 13, 24, 120};
    data->coords.x1y0l = (struct rectanglei){290, 13, 24, 120};

    data->coords.xm1y1f = (struct rectanglei){34, 21, 128, 96};
    data->coords.x0y1f = (struct rectanglei){162, 21, 128, 96};
    data->coords.x1y1f = (struct rectanglei){290, 21, 128, 96};

    data->coords.xm1y1r = (struct rectanglei){162, 21, 24, 95};
    data->coords.x1y1l = (struct rectanglei){266, 21, 24, 95};

    data->coords.xm1y2f = (struct rectanglei){106, 33, 80, 59};
    data->coords.x0y2f = (struct rectanglei){186, 33, 80, 59};
    data->coords.x1y2f = (struct rectanglei){266, 33, 80, 59};

    data->coords.xm2y2r = (struct rectanglei){138, 39, 16, 43};
    data->coords.xm1y2r = (struct rectanglei){186, 33, 16, 59};
    data->coords.x1y2l = (struct rectanglei){250, 33, 16, 59};
    data->coords.x2y2l = (struct rectanglei){298, 39, 16, 43};

    data->coords.xm2y3f = (struct rectanglei){106, 40, 48, 37};
    data->coords.xm1y3f = (struct rectanglei){154, 40, 48, 37};
    data->coords.x0y3f = (struct rectanglei){202, 40, 48, 37};
    data->coords.x1y3f = (struct rectanglei){250, 40, 48, 37};
    data->coords.x2y3f = (struct rectanglei){298, 40, 48, 37};

    data->coords.xm2y3r = (struct rectanglei){154, 41, 24, 35};
    data->coords.xm1y3r = (struct rectanglei){202, 41, 8, 35};
    data->coords.x1y3l = (struct rectanglei){242, 41, 8, 35};
    data->coords.x2y3l = (struct rectanglei){274, 41, 24, 35};
}
static void game_scene_init_textures(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    data->texture_main = LoadTexture("res/main5.png");

    data->texture_ui_inventory = LoadTexture("res/ui_inventory.png");
    data->texture_ui_button_camp = LoadTexture("res/ui_button_camp.png");
    data->texture_ui_equipment = LoadTexture("res/ui_equipment.png");
    data->texture_ui_character_sheet = LoadTexture("res/ui_character_sheet.png");
    data->texture_ui_minimap = LoadTexture("res/ui_minimap.png");
    data->texture_ui_spells = LoadTexture("res/ui_spells.png");
    data->texture_ui_portrait_hands = LoadTexture("res/ui_portrait_hands.png");
    data->texture_ui_compass_north = LoadTexture("res/ui_compass_north.png");
    data->texture_ui_compass_east = LoadTexture("res/ui_compass_east.png");
    data->texture_ui_compass_south = LoadTexture("res/ui_compass_south.png");
    data->texture_ui_compass_west = LoadTexture("res/ui_compass_west.png");
    data->texture_ui_buttons_direction = LoadTexture("res/ui_buttons_direction.png");

    data->array_texture_backdrops[0] = LoadTexture("res/backdrops/backdrop01.png");
    data->array_texture_backdrops[1] = LoadTexture("res/backdrops/backdrop02.png");
    data->array_texture_backdrops[2] = LoadTexture("res/backdrops/backdrop03.png");
    data->array_texture_backdrops[3] = LoadTexture("res/backdrops/backdrop04.png");
    data->array_texture_backdrops[4] = LoadTexture("res/backdrops/backdrop05.png");
    data->array_texture_backdrops[5] = LoadTexture("res/backdrops/backdrop06.png");
    data->array_texture_backdrops[6] = LoadTexture("res/backdrops/backdrop07.png");
    data->array_texture_backdrops[7] = LoadTexture("res/backdrops/backdrop08.png");
    data->array_texture_backdrops[8] = LoadTexture("res/backdrops/backdrop09.png");
    data->array_texture_backdrops[9] = LoadTexture("res/backdrops/backdrop10.png");
    data->array_texture_backdrops[10] = LoadTexture("res/backdrops/backdrop11.png");
    data->array_texture_backdrops[11] = LoadTexture("res/backdrops/backdrop12.png");
    data->array_texture_backdrops[12] = LoadTexture("res/backdrops/backdrop13.png");
    data->array_texture_backdrops[13] = LoadTexture("res/backdrops/backdrop14.png");
    data->array_texture_backdrops[14] = LoadTexture("res/backdrops/backdrop15.png");
    data->array_texture_backdrops[15] = LoadTexture("res/backdrops/backdrop16.png");
    data->array_texture_backdrops[16] = LoadTexture("res/backdrops/backdrop17.png");
    data->array_texture_backdrops[17] = LoadTexture("res/backdrops/backdrop18.png");
    data->array_texture_backdrops[18] = LoadTexture("res/backdrops/backdrop19.png");
    data->array_texture_backdrops[19] = LoadTexture("res/backdrops/backdrop20.png");
    data->array_texture_backdrops[20] = LoadTexture("res/backdrops/backdrop21.png");
    data->array_texture_backdrops[21] = LoadTexture("res/backdrops/backdrop22.png");
    data->array_texture_backdrops[22] = LoadTexture("res/backdrops/backdrop23.png");
    data->array_texture_backdrops[23] = LoadTexture("res/backdrops/backdrop24.png");
    data->array_texture_backdrops[24] = LoadTexture("res/backdrops/backdrop25.png");
    data->array_texture_backdrops[25] = LoadTexture("res/backdrops/backdrop26.png");
    data->array_texture_backdrops[26] = LoadTexture("res/backdrops/backdrop27.png");
    data->array_texture_backdrops[27] = LoadTexture("res/backdrops/backdrop28.png");
    data->array_texture_backdrops[28] = LoadTexture("res/backdrops/backdrop29.png");
    data->array_texture_backdrops[29] = LoadTexture("res/backdrops/backdrop30.png");
    data->array_texture_backdrops[30] = LoadTexture("res/backdrops/backdrop31.png");
    data->array_texture_backdrops[31] = LoadTexture("res/backdrops/backdrop32.png");
    data->array_texture_backdrops[32] = LoadTexture("res/backdrops/backdrop33.png");
    data->array_texture_backdrops[33] = LoadTexture("res/backdrops/backdrop34.png");
    data->array_texture_backdrops[34] = LoadTexture("res/backdrops/backdrop35.png");
    data->array_texture_backdrops[35] = LoadTexture("res/backdrops/backdrop36.png");

    data->texture_xm1y0r = LoadTexture("res/xm1y0r.png");
    data->texture_x1y0l = LoadTexture("res/x1y0l.png");

    data->texture_xm1y1f = LoadTexture("res/xm1y1f.png");
    data->texture_x0y1f = LoadTexture("res/x0y1f.png");
    data->texture_x1y1f = LoadTexture("res/x1y1f.png");

    data->texture_xm1y1r = LoadTexture("res/xm1y1r.png");
    data->texture_x1y1l = LoadTexture("res/x1y1l.png");

    data->texture_xm1y2f = LoadTexture("res/xm1y2f.png");
    data->texture_x0y2f = LoadTexture("res/x0y2f.png");
    data->texture_x1y2f = LoadTexture("res/x1y2f.png");

    data->texture_xm2y2r = LoadTexture("res/xm2y2r.png");
    data->texture_xm1y2r = LoadTexture("res/xm1y2r.png");
    data->texture_x1y2l = LoadTexture("res/x1y2l.png");
    data->texture_x2y2l = LoadTexture("res/x2y2l.png");

    data->texture_xm2y3f = LoadTexture("res/xm2y3f.png");
    data->texture_xm1y3f = LoadTexture("res/xm1y3f.png");
    data->texture_x0y3f = LoadTexture("res/x0y3f.png");
    data->texture_x1y3f = LoadTexture("res/x1y3f.png");
    data->texture_x2y3f = LoadTexture("res/x2y3f.png");

    data->texture_xm2y3r = LoadTexture("res/xm2y3r.png");
    data->texture_xm1y3r = LoadTexture("res/xm1y3r.png");
    data->texture_x1y3l = LoadTexture("res/x1y3l.png");
    data->texture_x2y3l = LoadTexture("res/x2y3l.png");

    //

    data->array_textures_count = 0;
    data->array_textures_capacity = 72;
    data->array_textures = malloc(sizeof *data->array_textures * data->array_textures_capacity);

    if (data->array_textures == NULL)
    {
        fprintf(stderr, "Error creating array_textures\n");
        exit(1);
    }

    memset(data->array_textures, 0, sizeof *data->array_textures * data->array_textures_capacity);

    data->array_textures[data->array_textures_count++] = &data->texture_main;

    data->array_textures[data->array_textures_count++] = &data->texture_ui_inventory;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_button_camp;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_equipment;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_character_sheet;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_minimap;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_spells;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_portrait_hands;

    data->array_textures[data->array_textures_count++] = &data->texture_ui_compass_north;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_compass_east;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_compass_south;
    data->array_textures[data->array_textures_count++] = &data->texture_ui_compass_west;

    data->array_textures[data->array_textures_count++] = &data->texture_ui_buttons_direction;

    for (size_t i = 0; i < sizeof(data->array_texture_backdrops) / sizeof(Texture2D); ++i)
    {
        data->array_textures[data->array_textures_count++] = &data->array_texture_backdrops[i];
    }

    data->array_textures[data->array_textures_count++] = &data->texture_xm1y0r;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y0l;

    data->array_textures[data->array_textures_count++] = &data->texture_xm1y1f;
    data->array_textures[data->array_textures_count++] = &data->texture_x0y1f;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y1f;

    data->array_textures[data->array_textures_count++] = &data->texture_xm1y1r;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y1l;

    data->array_textures[data->array_textures_count++] = &data->texture_xm1y2f;
    data->array_textures[data->array_textures_count++] = &data->texture_x0y2f;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y2f;

    data->array_textures[data->array_textures_count++] = &data->texture_xm2y2r;
    data->array_textures[data->array_textures_count++] = &data->texture_xm1y2r;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y2l;
    data->array_textures[data->array_textures_count++] = &data->texture_x2y2l;

    data->array_textures[data->array_textures_count++] = &data->texture_xm2y3f;
    data->array_textures[data->array_textures_count++] = &data->texture_xm1y3f;
    data->array_textures[data->array_textures_count++] = &data->texture_x0y3f;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y3f;
    data->array_textures[data->array_textures_count++] = &data->texture_x2y3f;

    data->array_textures[data->array_textures_count++] = &data->texture_xm2y3r;
    data->array_textures[data->array_textures_count++] = &data->texture_xm1y3r;
    data->array_textures[data->array_textures_count++] = &data->texture_x1y3l;
    data->array_textures[data->array_textures_count++] = &data->texture_x2y3l;
}
static void game_scene_init_sprites(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    //

    struct coords coords = data->coords;

    //

    data->sprite_main = sprite_create(data->texture_main, (float)coords.main.x, (float)coords.main.y, (float)coords.main.w, (float)coords.main.h);

    data->sprite_ui_inventory = sprite_create(data->texture_ui_inventory, (float)coords.ui_inventory.x, (float)coords.ui_inventory.y, (float)coords.ui_inventory.w, (float)coords.ui_inventory.h);
    data->sprite_ui_button_camp = sprite_create(data->texture_ui_button_camp, (float)coords.ui_camp_button.x, (float)coords.ui_camp_button.y, (float)coords.ui_camp_button.w, (float)coords.ui_camp_button.h);
    data->sprite_ui_equipment = sprite_create(data->texture_ui_equipment, (float)coords.ui_equipment.x, (float)coords.ui_equipment.y, (float)coords.ui_equipment.w, (float)coords.ui_equipment.h);
    data->sprite_ui_character_sheet = sprite_create(data->texture_ui_character_sheet, (float)coords.ui_character_sheet.x, (float)coords.ui_character_sheet.y, (float)coords.ui_character_sheet.w, (float)coords.ui_character_sheet.h);
    data->sprite_ui_minimap = sprite_create(data->texture_ui_minimap, (float)coords.ui_minimap.x, (float)coords.ui_minimap.y, (float)coords.ui_minimap.w, (float)coords.ui_minimap.h);
    data->sprite_ui_spells = sprite_create(data->texture_ui_spells, (float)coords.ui_spells.x, (float)coords.ui_spells.y, (float)coords.ui_spells.w, (float)coords.ui_spells.h);
    data->sprite_ui_portrait_hands = sprite_create(data->texture_ui_portrait_hands, (float)coords.ui_portrait_hands.x, (float)coords.ui_portrait_hands.y, (float)coords.ui_portrait_hands.w, (float)coords.ui_portrait_hands.h);
    data->sprite_ui_compass = sprite_create(data->texture_ui_compass_north, (float)coords.ui_compass.x, (float)coords.ui_compass.y, (float)coords.ui_compass.w, (float)coords.ui_compass.h);
    data->sprite_ui_buttons_direction = sprite_create(data->texture_ui_buttons_direction, (float)coords.ui_movement_buttons.x, (float)coords.ui_movement_buttons.y, (float)coords.ui_movement_buttons.w, (float)coords.ui_movement_buttons.h);

    data->sprite_backdrop = sprite_create(data->array_texture_backdrops[0], (float)coords.backdrop.x, (float)coords.backdrop.y, (float)coords.backdrop.w, (float)coords.backdrop.h);

    data->sprite_xm1y0r = sprite_create(data->texture_xm1y0r, (float)coords.xm1y0r.x, (float)coords.xm1y0r.y, (float)coords.xm1y0r.w, (float)coords.xm1y0r.h);
    data->sprite_x1y0l = sprite_create(data->texture_x1y0l, (float)coords.x1y0l.x, (float)coords.x1y0l.y, (float)coords.x1y0l.w, (float)coords.x1y0l.h);

    data->sprite_xm1y1f = sprite_create(data->texture_xm1y1f, (float)coords.xm1y1f.x, (float)coords.xm1y1f.y, (float)coords.xm1y1f.w, (float)coords.xm1y1f.h);
    data->sprite_x0y1f = sprite_create(data->texture_x0y1f, (float)coords.x0y1f.x, (float)coords.x0y1f.y, (float)coords.x0y1f.w, (float)coords.x0y1f.h);
    data->sprite_x1y1f = sprite_create(data->texture_x1y1f, (float)coords.x1y1f.x, (float)coords.x1y1f.y, (float)coords.x1y1f.w, (float)coords.x1y1f.h);

    data->sprite_xm1y1r = sprite_create(data->texture_xm1y1r, (float)coords.xm1y1r.x, (float)coords.xm1y1r.y, (float)coords.xm1y1r.w, (float)coords.xm1y1r.h);
    data->sprite_x1y1l = sprite_create(data->texture_x1y1l, (float)coords.x1y1l.x, (float)coords.x1y1l.y, (float)coords.x1y1l.w, (float)coords.x1y1l.h);

    data->sprite_xm1y2f = sprite_create(data->texture_xm1y2f, (float)coords.xm1y2f.x, (float)coords.xm1y2f.y, (float)coords.xm1y2f.w, (float)coords.xm1y2f.h);
    data->sprite_x0y2f = sprite_create(data->texture_x0y2f, (float)coords.x0y2f.x, (float)coords.x0y2f.y, (float)coords.x0y2f.w, (float)coords.x0y2f.h);
    data->sprite_x1y2f = sprite_create(data->texture_x1y2f, (float)coords.x1y2f.x, (float)coords.x1y2f.y, (float)coords.x1y2f.w, (float)coords.x1y2f.h);

    data->sprite_xm2y2r = sprite_create(data->texture_xm2y2r, (float)coords.xm2y2r.x, (float)coords.xm2y2r.y, (float)coords.xm2y2r.w, (float)coords.xm2y2r.h);
    data->sprite_xm1y2r = sprite_create(data->texture_xm1y2r, (float)coords.xm1y2r.x, (float)coords.xm1y2r.y, (float)coords.xm1y2r.w, (float)coords.xm1y2r.h);
    data->sprite_x1y2l = sprite_create(data->texture_x1y2l, (float)coords.x1y2l.x, (float)coords.x1y2l.y, (float)coords.x1y2l.w, (float)coords.x1y2l.h);
    data->sprite_x2y2l = sprite_create(data->texture_x2y2l, (float)coords.x2y2l.x, (float)coords.x2y2l.y, (float)coords.x2y2l.w, (float)coords.x2y2l.h);

    data->sprite_xm2y3f = sprite_create(data->texture_xm2y3f, (float)coords.xm2y3f.x, (float)coords.xm2y3f.y, (float)coords.xm2y3f.w, (float)coords.xm2y3f.h);
    data->sprite_xm1y3f = sprite_create(data->texture_xm1y3f, (float)coords.xm1y3f.x, (float)coords.xm1y3f.y, (float)coords.xm1y3f.w, (float)coords.xm1y3f.h);
    data->sprite_x0y3f = sprite_create(data->texture_x0y3f, (float)coords.x0y3f.x, (float)coords.x0y3f.y, (float)coords.x0y3f.w, (float)coords.x0y3f.h);
    data->sprite_x1y3f = sprite_create(data->texture_x1y3f, (float)coords.x1y3f.x, (float)coords.x1y3f.y, (float)coords.x1y3f.w, (float)coords.x1y3f.h);
    data->sprite_x2y3f = sprite_create(data->texture_x2y3f, (float)coords.x2y3f.x, (float)coords.x2y3f.y, (float)coords.x2y3f.w, (float)coords.x2y3f.h);

    data->sprite_xm2y3r = sprite_create(data->texture_xm2y3r, (float)coords.xm2y3r.x, (float)coords.xm2y3r.y, (float)coords.xm2y3r.w, (float)coords.xm2y3r.h);
    data->sprite_xm1y3r = sprite_create(data->texture_xm1y3r, (float)coords.xm1y3r.x, (float)coords.xm1y3r.y, (float)coords.xm1y3r.w, (float)coords.xm1y3r.h);
    data->sprite_x1y3l = sprite_create(data->texture_x1y3l, (float)coords.x1y3l.x, (float)coords.x1y3l.y, (float)coords.x1y3l.w, (float)coords.x1y3l.h);
    data->sprite_x2y3l = sprite_create(data->texture_x2y3l, (float)coords.x2y3l.x, (float)coords.x2y3l.y, (float)coords.x2y3l.w, (float)coords.x2y3l.h);

    //

    data->sprites_count = 0;
    data->sprites_capacity = 37;
    data->sprites = (Sprite **)malloc(sizeof *data->sprites * data->sprites_capacity);

    if (data->sprites == NULL)
    {
        fprintf(stderr, "Cannot malloc sprites array!\n");
        exit(1);
    }

    memset(data->sprites, 0, sizeof *data->sprites * data->sprites_capacity);

    //

    data->sprites[data->sprites_count++] = data->sprite_main;

    data->sprites[data->sprites_count++] = data->sprite_ui_inventory;
    data->sprites[data->sprites_count++] = data->sprite_ui_button_camp;
    data->sprites[data->sprites_count++] = data->sprite_ui_equipment;
    data->sprites[data->sprites_count++] = data->sprite_ui_character_sheet;
    data->sprites[data->sprites_count++] = data->sprite_ui_minimap;
    data->sprites[data->sprites_count++] = data->sprite_ui_spells;
    data->sprites[data->sprites_count++] = data->sprite_ui_portrait_hands;
    data->sprites[data->sprites_count++] = data->sprite_ui_compass;
    data->sprites[data->sprites_count++] = data->sprite_ui_buttons_direction;

    data->sprites[data->sprites_count++] = data->sprite_backdrop;

    data->sprites[data->sprites_count++] = data->sprite_xm1y0r;
    data->sprites[data->sprites_count++] = data->sprite_x1y0l;

    data->sprites[data->sprites_count++] = data->sprite_xm1y1f;
    data->sprites[data->sprites_count++] = data->sprite_x0y1f;
    data->sprites[data->sprites_count++] = data->sprite_x1y1f;

    data->sprites[data->sprites_count++] = data->sprite_xm1y1r;
    data->sprites[data->sprites_count++] = data->sprite_x1y1l;

    data->sprites[data->sprites_count++] = data->sprite_xm1y2f;
    data->sprites[data->sprites_count++] = data->sprite_x0y2f;
    data->sprites[data->sprites_count++] = data->sprite_x1y2f;

    data->sprites[data->sprites_count++] = data->sprite_xm2y2r;
    data->sprites[data->sprites_count++] = data->sprite_xm1y2r;
    data->sprites[data->sprites_count++] = data->sprite_x1y2l;
    data->sprites[data->sprites_count++] = data->sprite_x2y2l;

    data->sprites[data->sprites_count++] = data->sprite_xm2y3f;
    data->sprites[data->sprites_count++] = data->sprite_xm1y3f;
    data->sprites[data->sprites_count++] = data->sprite_x0y3f;
    data->sprites[data->sprites_count++] = data->sprite_x1y3f;
    data->sprites[data->sprites_count++] = data->sprite_x2y3f;

    data->sprites[data->sprites_count++] = data->sprite_xm2y3r;
    data->sprites[data->sprites_count++] = data->sprite_xm1y3r;
    data->sprites[data->sprites_count++] = data->sprite_x1y3l;
    data->sprites[data->sprites_count++] = data->sprite_x2y3l;

    //

    data->wall_sprites_count = 0;
    data->wall_sprites_capacity = 23;
    data->wall_sprites = (Sprite **)malloc(sizeof *data->wall_sprites * data->wall_sprites_capacity);

    if (data->wall_sprites == NULL)
    {
        fprintf(stderr, "Error malloc wall_sprites!\n");
        exit(1);
    }

    memset(data->wall_sprites, 0, sizeof *data->wall_sprites * data->wall_sprites_capacity);

    //

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y0r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y0l;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y1f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x0y1f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y1f;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y1r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y1l;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y2f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x0y2f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y2f;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm2y2r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y2r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y2l;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x2y2l;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm2y3f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y3f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x0y3f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y3f;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x2y3f;

    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm2y3r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_xm1y3r;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x1y3l;
    data->wall_sprites[data->wall_sprites_count++] = data->sprite_x2y3l;
}
static void game_scene_init_map(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    data->map = map_create(16, 16);

    for (size_t y = 0; y < map_get_height(data->map); ++y)
    {
        for (size_t x = 0; x < map_get_width(data->map); ++x)
        {
            if ((y == 0 || y == map_get_height(data->map) - 1) || (x == 0 || x == map_get_width(data->map) - 1))
            {
                map_data_set_at(data->map, x, y, 1);
            }
        }
    }

    for (size_t y = 1; y < map_get_height(data->map) - 1; ++y)
    {
        for (size_t x = 1; x < map_get_width(data->map) - 1; ++x)
        {
            map_data_set_at(data->map, x, y, GetRandomValue(0, 100) > 75 ? 1 : 0);
        }
    }
}
static void game_scene_init_player(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    int x = 1;
    int y = map_get_height(data->map) - 2;
    CardinalDirection facing = CARDINAL_DIRECTION_NORTH;
    int health = 10;
    Color color = (Color){255, 255, 255, 255};

    data->player = player_create(x, y, facing, health, color);
}
static void game_scene_init_enemies(struct scene *scene)
{
    struct game_scene_data *data = (struct game_scene_data *)scene->data;

    data->enemy_array.count = 0;
    data->enemy_array.capacity = 1;
    data->enemy_array.enemies = malloc(sizeof *data->enemy_array.enemies * data->enemy_array.capacity);

    if (data->enemy_array.enemies == NULL)
    {
        fprintf(stderr, "Error creating enemies array\n");
        exit(1);
    }

    memset(data->enemy_array.enemies, 0, sizeof *data->enemy_array.enemies * data->enemy_array.capacity);

    int num_enemies = 16;

    for (int i = 0; i < num_enemies; ++i)
    {
        if (data->enemy_array.count == data->enemy_array.capacity)
        {
            Enemy **ptr = realloc(data->enemy_array.enemies, sizeof *data->enemy_array.enemies * data->enemy_array.capacity * 2);

            if (ptr == NULL)
            {
                fprintf(stderr, "Error reallocating enemies array\n");
                exit(1);
            }

            memset(&ptr[data->enemy_array.capacity], 0, sizeof *data->enemy_array.enemies * data->enemy_array.capacity);
            data->enemy_array.enemies = ptr;
            data->enemy_array.capacity *= 2;
        }

        int x = GetRandomValue(1, map_get_width(data->map) - 2);
        int y = GetRandomValue(1, map_get_height(data->map) - 2);
        CardinalDirection facing = CARDINAL_DIRECTION_NORTH;
        int health = 10;
        unsigned char r = GetRandomValue(0, 255);
        unsigned char g = GetRandomValue(0, 255);
        unsigned char b = GetRandomValue(0, 255);
        Color color = (Color){r, g, b, 255};

        Enemy *enemy = enemy_create(x, y, facing, health, color);

        data->enemy_array.enemies[data->enemy_array.count++] = enemy;
    }
}
static void game_scene_init_dungeon_camera(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    data->dungeon_camera = dungeon_camera_create(0, 0, CARDINAL_DIRECTION_NORTH);
}

static void game_scene_free_coords(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    coords_free(&data->coords);
}
static void game_scene_free_textures(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    for (size_t i = 0; i < data->array_textures_count; ++i)
    {
        Texture2D *texture = data->array_textures[i];
        UnloadTexture(*texture);
    }

    data->array_textures_count = 0;
    data->array_textures_capacity = 0;
    free(data->array_textures);
    data->array_textures = NULL;

    memset(data->array_texture_backdrops, 0, sizeof(data->array_texture_backdrops));
}
static void game_scene_free_sprites(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    //

    for (size_t i = 0; i < data->sprites_count; ++i)
    {
        Sprite *sprite = data->sprites[i];
        sprite_free(sprite);
    }

    //

    data->sprites_count = 0;
    data->sprites_capacity = 0;
    free(data->sprites);
    data->sprites = NULL;

    //

    data->wall_sprites_capacity = 0;
    data->wall_sprites_count = 0;
    free(data->wall_sprites);
    data->wall_sprites = NULL;
}
static void game_scene_free_map(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    map_free(data->map);
}
static void game_scene_free_player(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    player_free(data->player);
}
static void game_scene_free_enemies(struct scene *scene)
{
    struct game_scene_data *data = (struct game_scene_data *)scene->data;

    for (size_t i = 0; i < data->enemy_array.count; ++i)
    {
        Enemy *enemy = data->enemy_array.enemies[i];
        enemy_free(enemy);
    }

    free(data->enemy_array.enemies);
    data->enemy_array = (EnemyArray){0};
}
static void game_scene_free_dungeon_camera(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    dungeon_camera_free(data->dungeon_camera);
}

static void game_scene_update_dungeon_camera(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    int x = player_get_x(data->player);
    int y = player_get_y(data->player);
    CardinalDirection facing = player_get_facing(data->player);

    dungeon_camera_set_x(data->dungeon_camera, x);
    dungeon_camera_set_y(data->dungeon_camera, y);
    dungeon_camera_set_facing(data->dungeon_camera, facing);
}

static void game_scene_update_compass(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    switch (player_get_facing(data->player))
    {
    case 0:
        sprite_set_texture(data->sprite_ui_compass, data->texture_ui_compass_north);
        break;
    case 1:
        sprite_set_texture(data->sprite_ui_compass, data->texture_ui_compass_east);
        break;
    case 2:
        sprite_set_texture(data->sprite_ui_compass, data->texture_ui_compass_south);
        break;
    case 3:
        sprite_set_texture(data->sprite_ui_compass, data->texture_ui_compass_west);
        break;
    default:
        sprite_set_texture(data->sprite_ui_compass, data->texture_ui_compass_north);
        break;
    }
}

static void game_scene_recalculate_visible_walls(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    for (size_t i = 0; i < data->wall_sprites_count; ++i)
    {
        sprite_set_is_visible(data->wall_sprites[i], false);
    }

    int dir_vecs[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0}};

    int front_f = dungeon_camera_get_facing(data->dungeon_camera);
    int left_f = (front_f + 3) % 4;
    int right_f = (front_f + 1) % 4;

    int *front_vec = dir_vecs[front_f];
    int *left_vec = dir_vecs[left_f];
    int *right_vec = dir_vecs[right_f];

    struct position_check
    {
        int forward_distance;
        int sizeways_distance;
        Sprite **sprites;
        size_t sprites_count;
    };

    struct position_check checks[] = {
        {3, -2, (Sprite *[]){data->sprite_xm2y3r, data->sprite_xm2y3f}, 2},
        {3, -1, (Sprite *[]){data->sprite_xm1y3r, data->sprite_xm1y3f}, 2},
        {3, 0, (Sprite *[]){data->sprite_x0y3f}, 1},
        {3, 1, (Sprite *[]){data->sprite_x1y3l, data->sprite_x1y3f}, 2},
        {3, 2, (Sprite *[]){data->sprite_x2y3l, data->sprite_x2y3f}, 2},

        {2, -2, (Sprite *[]){data->sprite_xm2y2r}, 1},
        {2, -1, (Sprite *[]){data->sprite_xm1y2r, data->sprite_xm1y2f}, 2},
        {2, 0, (Sprite *[]){data->sprite_x0y2f}, 1},
        {2, 1, (Sprite *[]){data->sprite_x1y2l, data->sprite_x1y2f}, 2},
        {2, 2, (Sprite *[]){data->sprite_x2y2l}, 1},

        {1, -1, (Sprite *[]){data->sprite_xm1y1r, data->sprite_xm1y1f}, 2},
        {1, 0, (Sprite *[]){data->sprite_x0y1f}, 1},
        {1, 1, (Sprite *[]){data->sprite_x1y1l, data->sprite_x1y1f}, 2},

        {0, -1, (Sprite *[]){data->sprite_xm1y0r}, 1},
        {0, 1, (Sprite *[]){data->sprite_x1y0l}, 1},
    };

    int num_checks = sizeof(checks) / sizeof checks[0];

    for (int i = 0; i < num_checks; ++i)
    {
        struct position_check *check = &checks[i];

        int target_x;
        int target_y;

        int *side_vec = check->sizeways_distance < 0 ? left_vec : right_vec;
        int sideways_distance = abs(check->sizeways_distance);

        game_scene_calculate_target_position(&target_x, &target_y, dungeon_camera_get_x(data->dungeon_camera), dungeon_camera_get_y(data->dungeon_camera), front_vec, check->forward_distance, side_vec, sideways_distance);

        if (sideways_distance == 0)
        {
            target_x = dungeon_camera_get_x(data->dungeon_camera) + front_vec[0] * check->forward_distance;
            target_y = dungeon_camera_get_y(data->dungeon_camera) + front_vec[1] * check->forward_distance;
        }

        if (game_scene_is_wall_at(data->map, target_x, target_y))
        {
            for (size_t j = 0; j < check->sprites_count; ++j)
            {
                sprite_set_is_visible(check->sprites[j], true);
            }
        }
    }
}

static void game_scene_flip_backdrop(struct scene *scene)
{
    struct game_scene_data *data = scene->data;

    Rectangle source = sprite_get_source(data->sprite_backdrop);

    source.width *= -1;

    sprite_set_source(data->sprite_backdrop, source);
}

static void game_scene_calculate_target_position(int *target_x, int *target_y, int x, int y, int *dir_vec, int forward_distance, int *side_vec, int sideways_distance)
{
    *target_x = x + dir_vec[0] * forward_distance + side_vec[0] * sideways_distance;
    *target_y = y + dir_vec[1] * forward_distance + side_vec[1] * sideways_distance;
}

static bool game_scene_is_wall_at(Map *map, int x, int y)
{
    if (x >= 0 && x < (int)map_get_width(map) && y >= 0 && y < (int)map_get_height(map))
    {
        return map_data_get_at(map, x, y) != 0;
    }

    return false;
}
