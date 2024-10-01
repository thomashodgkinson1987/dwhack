#include "map.h"
#include "sprite.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int virtual_screen_width = 320;
static const int virtual_screen_height = 200;

static const int screen_size_multiplier = 4;

static const int screen_width = virtual_screen_width * screen_size_multiplier;
static const int screen_height = virtual_screen_height * screen_size_multiplier;

struct rectanglei
{
    int x, y, w, h;
};

struct coors
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

struct coors coors;

static bool render_texture_virtual_screen_is_dirty;
static RenderTexture2D render_texture_virtual_screen;
static Rectangle render_texture_virtual_screen_source;
static Rectangle render_texture_virtual_screen_dest;
static Vector2 render_texture_virtual_screen_origin;
static float render_texture_virtual_screen_rotation;
static Color render_texture_virtual_screen_tint;

static Texture2D texture_main;

static Texture2D texture_ui_inventory;
static Texture2D texture_ui_button_camp;
static Texture2D texture_ui_equipment;
static Texture2D texture_ui_character_sheet;
static Texture2D texture_ui_minimap;
static Texture2D texture_ui_spells;
static Texture2D texture_ui_portrait_hands;
static Texture2D texture_ui_compass_north;
static Texture2D texture_ui_compass_east;
static Texture2D texture_ui_compass_south;
static Texture2D texture_ui_compass_west;
static Texture2D texture_ui_buttons_direction;

static const size_t array_backdrop_textures_length = 36;
static Texture2D array_backdrop_textures[36];

static Texture2D texture_xm1y0r;
static Texture2D texture_x1y0l;

static Texture2D texture_xm1y1f;
static Texture2D texture_x0y1f;
static Texture2D texture_x1y1f;

static Texture2D texture_xm1y1r;
static Texture2D texture_x1y1l;

static Texture2D texture_xm1y2f;
static Texture2D texture_x0y2f;
static Texture2D texture_x1y2f;

static Texture2D texture_xm2y2r;
static Texture2D texture_xm1y2r;
static Texture2D texture_x1y2l;
static Texture2D texture_x2y2l;

static Texture2D texture_xm2y3f;
static Texture2D texture_xm1y3f;
static Texture2D texture_x0y3f;
static Texture2D texture_x1y3f;
static Texture2D texture_x2y3f;

static Texture2D texture_xm2y3r;
static Texture2D texture_xm1y3r;
static Texture2D texture_x1y3l;
static Texture2D texture_x2y3l;

static struct sprite sprite_main;

static struct sprite sprite_ui_inventory;
static struct sprite sprite_ui_button_camp;
static struct sprite sprite_ui_equipment;
static struct sprite sprite_ui_character_sheet;
static struct sprite sprite_ui_minimap;
static struct sprite sprite_ui_spells;
static struct sprite sprite_ui_portrait_hands;
static struct sprite sprite_ui_compass;
static struct sprite sprite_ui_buttons_direction;

static struct sprite sprite_backdrop;

static struct sprite sprite_xm1y0r;
static struct sprite sprite_x1y0l;

static struct sprite sprite_xm1y1f;
static struct sprite sprite_x0y1f;
static struct sprite sprite_x1y1f;

static struct sprite sprite_xm1y1r;
static struct sprite sprite_x1y1l;

static struct sprite sprite_xm1y2f;
static struct sprite sprite_x0y2f;
static struct sprite sprite_x1y2f;

static struct sprite sprite_xm2y2r;
static struct sprite sprite_xm1y2r;
static struct sprite sprite_x1y2l;
static struct sprite sprite_x2y2l;

static struct sprite sprite_xm2y3f;
static struct sprite sprite_xm1y3f;
static struct sprite sprite_x0y3f;
static struct sprite sprite_x1y3f;
static struct sprite sprite_x2y3f;

static struct sprite sprite_xm2y3r;
static struct sprite sprite_xm1y3r;
static struct sprite sprite_x1y3l;
static struct sprite sprite_x2y3l;

static size_t array_textures_count;
static size_t array_textures_capacity;
static Texture2D **array_textures;

static size_t array_sprites_count;
static size_t array_sprites_capacity;
static struct sprite **array_sprites;

static size_t array_wall_sprites_count;
static size_t array_wall_sprites_capacity;
static struct sprite **array_wall_sprites;

static int player_x;
static int player_y;
static int player_f;

static struct map map;

static void game_init(void);
static void game_init_coors(void);
static void game_init_textures(void);
static void game_init_sprites(void);
static void game_init_map(void);

static void game_free(void);
static void game_free_coors(void);
static void game_free_textures(void);
static void game_free_sprites(void);
static void game_free_map(void);

static void game_tick(float delta);
static void game_draw(void);

static void flip_backdrop(void);
static void update_compass(void);
static void recalculate_visible_walls(void);

int main(void)
{
    InitWindow(screen_width, screen_height, "Dungeon Whack");
    SetTargetFPS(60);

    game_init();

    float delta = 0.0f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R))
        {
            game_free();
            game_init();
        }

        delta = GetFrameTime();
        game_tick(delta);
        game_draw();
    }

    game_free();

    CloseWindow();

    return 0;
}

static void game_init(void)
{
    game_init_coors();
    game_init_textures();
    game_init_sprites();
    game_init_map();

    sprite_ui_character_sheet.is_visible = false;
    sprite_ui_spells.is_visible = false;

    sprite_backdrop.texture = array_backdrop_textures[GetRandomValue(0, array_backdrop_textures_length - 1)];

    player_x = 1;
    player_y = map_get_height(&map) - 2;
    player_f = 0;

    update_compass();
    recalculate_visible_walls();
}

static void game_init_coors(void)
{
    coors = (struct coors){0};

    coors.main = (struct rectanglei){0, 0, 320, 200};

    coors.ui_inventory = (struct rectanglei){0, 0, 36, 182};
    coors.ui_camp_button = (struct rectanglei){0, 181, 37, 19};
    coors.ui_equipment = (struct rectanglei){36, 0, 100, 132};
    coors.ui_character_sheet = (struct rectanglei){0, 0, 136, 182};
    coors.ui_minimap = (struct rectanglei){54, 139, 58, 42};
    coors.ui_spells = (struct rectanglei){37, 137, 99, 44};
    coors.ui_portrait_hands = (struct rectanglei){139, 136, 66, 44};
    coors.ui_compass = (struct rectanglei){210, 134, 45, 44};
    coors.ui_movement_buttons = (struct rectanglei){260, 136, 58, 44};

    coors.backdrop = (struct rectanglei){138, 13, 176, 120};

    coors.xm1y0r = (struct rectanglei){138, 13, 24, 120};
    coors.x1y0l = (struct rectanglei){290, 13, 24, 120};

    coors.xm1y1f = (struct rectanglei){34, 21, 128, 96};
    coors.x0y1f = (struct rectanglei){162, 21, 128, 96};
    coors.x1y1f = (struct rectanglei){290, 21, 128, 96};

    coors.xm1y1r = (struct rectanglei){162, 21, 24, 95};
    coors.x1y1l = (struct rectanglei){266, 21, 24, 95};

    coors.xm1y2f = (struct rectanglei){106, 33, 80, 59};
    coors.x0y2f = (struct rectanglei){186, 33, 80, 59};
    coors.x1y2f = (struct rectanglei){266, 33, 80, 59};

    coors.xm2y2r = (struct rectanglei){138, 39, 16, 43};
    coors.xm1y2r = (struct rectanglei){186, 33, 16, 59};
    coors.x1y2l = (struct rectanglei){250, 33, 16, 59};
    coors.x2y2l = (struct rectanglei){298, 39, 16, 43};

    coors.xm2y3f = (struct rectanglei){106, 40, 48, 37};
    coors.xm1y3f = (struct rectanglei){154, 40, 48, 37};
    coors.x0y3f = (struct rectanglei){202, 40, 48, 37};
    coors.x1y3f = (struct rectanglei){250, 40, 48, 37};
    coors.x2y3f = (struct rectanglei){298, 40, 48, 37};

    coors.xm2y3r = (struct rectanglei){154, 41, 24, 35};
    coors.xm1y3r = (struct rectanglei){202, 41, 8, 35};
    coors.x1y3l = (struct rectanglei){242, 41, 8, 35};
    coors.x2y3l = (struct rectanglei){274, 41, 24, 35};
}

static void game_init_textures(void)
{
    render_texture_virtual_screen_is_dirty = true;
    render_texture_virtual_screen = LoadRenderTexture(virtual_screen_width, virtual_screen_height);
    render_texture_virtual_screen_source = (Rectangle){0.0f, 0.0f, (float)render_texture_virtual_screen.texture.width, -(float)render_texture_virtual_screen.texture.height};
    render_texture_virtual_screen_dest = (Rectangle){0.0f, 0.0f, (float)screen_width, (float)screen_height};
    render_texture_virtual_screen_origin = (Vector2){0.0f, 0.0f};
    render_texture_virtual_screen_rotation = 0.0f;
    render_texture_virtual_screen_tint = WHITE;

    texture_main = LoadTexture("res/main5.png");

    texture_ui_inventory = LoadTexture("res/ui_inventory.png");
    texture_ui_button_camp = LoadTexture("res/ui_button_camp.png");
    texture_ui_equipment = LoadTexture("res/ui_equipment.png");
    texture_ui_character_sheet = LoadTexture("res/ui_character_sheet.png");
    texture_ui_minimap = LoadTexture("res/ui_minimap.png");
    texture_ui_spells = LoadTexture("res/ui_spells.png");
    texture_ui_portrait_hands = LoadTexture("res/ui_portrait_hands.png");
    texture_ui_compass_north = LoadTexture("res/ui_compass_north.png");
    texture_ui_compass_east = LoadTexture("res/ui_compass_east.png");
    texture_ui_compass_south = LoadTexture("res/ui_compass_south.png");
    texture_ui_compass_west = LoadTexture("res/ui_compass_west.png");
    texture_ui_buttons_direction = LoadTexture("res/ui_buttons_direction.png");

    {
        array_backdrop_textures[0] = LoadTexture("res/backdrops/backdrop01.png");
        array_backdrop_textures[1] = LoadTexture("res/backdrops/backdrop02.png");
        array_backdrop_textures[2] = LoadTexture("res/backdrops/backdrop03.png");
        array_backdrop_textures[3] = LoadTexture("res/backdrops/backdrop04.png");
        array_backdrop_textures[4] = LoadTexture("res/backdrops/backdrop05.png");
        array_backdrop_textures[5] = LoadTexture("res/backdrops/backdrop06.png");
        array_backdrop_textures[6] = LoadTexture("res/backdrops/backdrop07.png");
        array_backdrop_textures[7] = LoadTexture("res/backdrops/backdrop08.png");
        array_backdrop_textures[8] = LoadTexture("res/backdrops/backdrop09.png");
        array_backdrop_textures[9] = LoadTexture("res/backdrops/backdrop10.png");
        array_backdrop_textures[10] = LoadTexture("res/backdrops/backdrop11.png");
        array_backdrop_textures[11] = LoadTexture("res/backdrops/backdrop12.png");
        array_backdrop_textures[12] = LoadTexture("res/backdrops/backdrop13.png");
        array_backdrop_textures[13] = LoadTexture("res/backdrops/backdrop14.png");
        array_backdrop_textures[14] = LoadTexture("res/backdrops/backdrop15.png");
        array_backdrop_textures[15] = LoadTexture("res/backdrops/backdrop16.png");
        array_backdrop_textures[16] = LoadTexture("res/backdrops/backdrop17.png");
        array_backdrop_textures[17] = LoadTexture("res/backdrops/backdrop18.png");
        array_backdrop_textures[18] = LoadTexture("res/backdrops/backdrop19.png");
        array_backdrop_textures[19] = LoadTexture("res/backdrops/backdrop20.png");
        array_backdrop_textures[20] = LoadTexture("res/backdrops/backdrop21.png");
        array_backdrop_textures[21] = LoadTexture("res/backdrops/backdrop22.png");
        array_backdrop_textures[22] = LoadTexture("res/backdrops/backdrop23.png");
        array_backdrop_textures[23] = LoadTexture("res/backdrops/backdrop24.png");
        array_backdrop_textures[24] = LoadTexture("res/backdrops/backdrop25.png");
        array_backdrop_textures[25] = LoadTexture("res/backdrops/backdrop26.png");
        array_backdrop_textures[26] = LoadTexture("res/backdrops/backdrop27.png");
        array_backdrop_textures[27] = LoadTexture("res/backdrops/backdrop28.png");
        array_backdrop_textures[28] = LoadTexture("res/backdrops/backdrop29.png");
        array_backdrop_textures[29] = LoadTexture("res/backdrops/backdrop30.png");
        array_backdrop_textures[30] = LoadTexture("res/backdrops/backdrop31.png");
        array_backdrop_textures[31] = LoadTexture("res/backdrops/backdrop32.png");
        array_backdrop_textures[32] = LoadTexture("res/backdrops/backdrop33.png");
        array_backdrop_textures[33] = LoadTexture("res/backdrops/backdrop34.png");
        array_backdrop_textures[34] = LoadTexture("res/backdrops/backdrop35.png");
        array_backdrop_textures[35] = LoadTexture("res/backdrops/backdrop36.png");
    }

    texture_xm1y0r = LoadTexture("res/xm1y0r.png");
    texture_x1y0l = LoadTexture("res/x1y0l.png");

    texture_xm1y1f = LoadTexture("res/xm1y1f.png");
    texture_x0y1f = LoadTexture("res/x0y1f.png");
    texture_x1y1f = LoadTexture("res/x1y1f.png");

    texture_xm1y1r = LoadTexture("res/xm1y1r.png");
    texture_x1y1l = LoadTexture("res/x1y1l.png");

    texture_xm1y2f = LoadTexture("res/xm1y2f.png");
    texture_x0y2f = LoadTexture("res/x0y2f.png");
    texture_x1y2f = LoadTexture("res/x1y2f.png");

    texture_xm2y2r = LoadTexture("res/xm2y2r.png");
    texture_xm1y2r = LoadTexture("res/xm1y2r.png");
    texture_x1y2l = LoadTexture("res/x1y2l.png");
    texture_x2y2l = LoadTexture("res/x2y2l.png");

    texture_xm2y3f = LoadTexture("res/xm2y3f.png");
    texture_xm1y3f = LoadTexture("res/xm1y3f.png");
    texture_x0y3f = LoadTexture("res/x0y3f.png");
    texture_x1y3f = LoadTexture("res/x1y3f.png");
    texture_x2y3f = LoadTexture("res/x2y3f.png");

    texture_xm2y3r = LoadTexture("res/xm2y3r.png");
    texture_xm1y3r = LoadTexture("res/xm1y3r.png");
    texture_x1y3l = LoadTexture("res/x1y3l.png");
    texture_x2y3l = LoadTexture("res/x2y3l.png");

    array_textures_count = 0;
    array_textures_capacity = 72;
    array_textures = malloc(sizeof *array_textures * array_textures_capacity);
    assert(array_textures != NULL);
    memset(array_textures, 0, sizeof *array_textures * array_textures_capacity);

    array_textures[array_textures_count++] = &texture_main;

    array_textures[array_textures_count++] = &texture_ui_inventory;
    array_textures[array_textures_count++] = &texture_ui_button_camp;
    array_textures[array_textures_count++] = &texture_ui_equipment;
    array_textures[array_textures_count++] = &texture_ui_character_sheet;
    array_textures[array_textures_count++] = &texture_ui_minimap;
    array_textures[array_textures_count++] = &texture_ui_spells;
    array_textures[array_textures_count++] = &texture_ui_portrait_hands;

    array_textures[array_textures_count++] = &texture_ui_compass_north;
    array_textures[array_textures_count++] = &texture_ui_compass_east;
    array_textures[array_textures_count++] = &texture_ui_compass_south;
    array_textures[array_textures_count++] = &texture_ui_compass_west;

    array_textures[array_textures_count++] = &texture_ui_buttons_direction;

    for (size_t i = 0; i < array_backdrop_textures_length; ++i)
    {
        array_textures[array_textures_count++] = &array_backdrop_textures[i];
    }

    array_textures[array_textures_count++] = &texture_xm1y0r;
    array_textures[array_textures_count++] = &texture_x1y0l;

    array_textures[array_textures_count++] = &texture_xm1y1f;
    array_textures[array_textures_count++] = &texture_x0y1f;
    array_textures[array_textures_count++] = &texture_x1y1f;

    array_textures[array_textures_count++] = &texture_xm1y1r;
    array_textures[array_textures_count++] = &texture_x1y1l;

    array_textures[array_textures_count++] = &texture_xm1y2f;
    array_textures[array_textures_count++] = &texture_x0y2f;
    array_textures[array_textures_count++] = &texture_x1y2f;

    array_textures[array_textures_count++] = &texture_xm2y2r;
    array_textures[array_textures_count++] = &texture_xm1y2r;
    array_textures[array_textures_count++] = &texture_x1y2l;
    array_textures[array_textures_count++] = &texture_x2y2l;

    array_textures[array_textures_count++] = &texture_xm2y3f;
    array_textures[array_textures_count++] = &texture_xm1y3f;
    array_textures[array_textures_count++] = &texture_x0y3f;
    array_textures[array_textures_count++] = &texture_x1y3f;
    array_textures[array_textures_count++] = &texture_x2y3f;

    array_textures[array_textures_count++] = &texture_xm2y3r;
    array_textures[array_textures_count++] = &texture_xm1y3r;
    array_textures[array_textures_count++] = &texture_x1y3l;
    array_textures[array_textures_count++] = &texture_x2y3l;
}

static void game_init_sprites(void)
{
    sprite_main = sprite_create(texture_main, (float)coors.main.x, (float)coors.main.y, (float)coors.main.w, (float)coors.main.h);

    sprite_ui_inventory = sprite_create(texture_ui_inventory, (float)coors.ui_inventory.x, (float)coors.ui_inventory.y, (float)coors.ui_inventory.w, (float)coors.ui_inventory.h);
    sprite_ui_button_camp = sprite_create(texture_ui_button_camp, (float)coors.ui_camp_button.x, (float)coors.ui_camp_button.y, (float)coors.ui_camp_button.w, (float)coors.ui_camp_button.h);
    sprite_ui_equipment = sprite_create(texture_ui_equipment, (float)coors.ui_equipment.x, (float)coors.ui_equipment.y, (float)coors.ui_equipment.w, (float)coors.ui_equipment.h);
    sprite_ui_character_sheet = sprite_create(texture_ui_character_sheet, (float)coors.ui_character_sheet.x, (float)coors.ui_character_sheet.y, (float)coors.ui_character_sheet.w, (float)coors.ui_character_sheet.h);
    sprite_ui_minimap = sprite_create(texture_ui_minimap, (float)coors.ui_minimap.x, (float)coors.ui_minimap.y, (float)coors.ui_minimap.w, (float)coors.ui_minimap.h);
    sprite_ui_spells = sprite_create(texture_ui_spells, (float)coors.ui_spells.x, (float)coors.ui_spells.y, (float)coors.ui_spells.w, (float)coors.ui_spells.h);
    sprite_ui_portrait_hands = sprite_create(texture_ui_portrait_hands, (float)coors.ui_portrait_hands.x, (float)coors.ui_portrait_hands.y, (float)coors.ui_portrait_hands.w, (float)coors.ui_portrait_hands.h);
    sprite_ui_compass = sprite_create(texture_ui_compass_north, (float)coors.ui_compass.x, (float)coors.ui_compass.y, (float)coors.ui_compass.w, (float)coors.ui_compass.h);
    sprite_ui_buttons_direction = sprite_create(texture_ui_buttons_direction, (float)coors.ui_movement_buttons.x, (float)coors.ui_movement_buttons.y, (float)coors.ui_movement_buttons.w, (float)coors.ui_movement_buttons.h);

    sprite_backdrop = sprite_create(array_backdrop_textures[0], (float)coors.backdrop.x, (float)coors.backdrop.y, (float)coors.backdrop.w, (float)coors.backdrop.h);

    sprite_xm1y0r = sprite_create(texture_xm1y0r, (float)coors.xm1y0r.x, (float)coors.xm1y0r.y, (float)coors.xm1y0r.w, (float)coors.xm1y0r.h);
    sprite_x1y0l = sprite_create(texture_x1y0l, (float)coors.x1y0l.x, (float)coors.x1y0l.y, (float)coors.x1y0l.w, (float)coors.x1y0l.h);

    sprite_xm1y1f = sprite_create(texture_xm1y1f, (float)coors.xm1y1f.x, (float)coors.xm1y1f.y, (float)coors.xm1y1f.w, (float)coors.xm1y1f.h);
    sprite_x0y1f = sprite_create(texture_x0y1f, (float)coors.x0y1f.x, (float)coors.x0y1f.y, (float)coors.x0y1f.w, (float)coors.x0y1f.h);
    sprite_x1y1f = sprite_create(texture_x1y1f, (float)coors.x1y1f.x, (float)coors.x1y1f.y, (float)coors.x1y1f.w, (float)coors.x1y1f.h);

    sprite_xm1y1r = sprite_create(texture_xm1y1r, (float)coors.xm1y1r.x, (float)coors.xm1y1r.y, (float)coors.xm1y1r.w, (float)coors.xm1y1r.h);
    sprite_x1y1l = sprite_create(texture_x1y1l, (float)coors.x1y1l.x, (float)coors.x1y1l.y, (float)coors.x1y1l.w, (float)coors.x1y1l.h);

    sprite_xm1y2f = sprite_create(texture_xm1y2f, (float)coors.xm1y2f.x, (float)coors.xm1y2f.y, (float)coors.xm1y2f.w, (float)coors.xm1y2f.h);
    sprite_x0y2f = sprite_create(texture_x0y2f, (float)coors.x0y2f.x, (float)coors.x0y2f.y, (float)coors.x0y2f.w, (float)coors.x0y2f.h);
    sprite_x1y2f = sprite_create(texture_x1y2f, (float)coors.x1y2f.x, (float)coors.x1y2f.y, (float)coors.x1y2f.w, (float)coors.x1y2f.h);

    sprite_xm2y2r = sprite_create(texture_xm2y2r, (float)coors.xm2y2r.x, (float)coors.xm2y2r.y, (float)coors.xm2y2r.w, (float)coors.xm2y2r.h);
    sprite_xm1y2r = sprite_create(texture_xm1y2r, (float)coors.xm1y2r.x, (float)coors.xm1y2r.y, (float)coors.xm1y2r.w, (float)coors.xm1y2r.h);
    sprite_x1y2l = sprite_create(texture_x1y2l, (float)coors.x1y2l.x, (float)coors.x1y2l.y, (float)coors.x1y2l.w, (float)coors.x1y2l.h);
    sprite_x2y2l = sprite_create(texture_x2y2l, (float)coors.x2y2l.x, (float)coors.x2y2l.y, (float)coors.x2y2l.w, (float)coors.x2y2l.h);

    sprite_xm2y3f = sprite_create(texture_xm2y3f, (float)coors.xm2y3f.x, (float)coors.xm2y3f.y, (float)coors.xm2y3f.w, (float)coors.xm2y3f.h);
    sprite_xm1y3f = sprite_create(texture_xm1y3f, (float)coors.xm1y3f.x, (float)coors.xm1y3f.y, (float)coors.xm1y3f.w, (float)coors.xm1y3f.h);
    sprite_x0y3f = sprite_create(texture_x0y3f, (float)coors.x0y3f.x, (float)coors.x0y3f.y, (float)coors.x0y3f.w, (float)coors.x0y3f.h);
    sprite_x1y3f = sprite_create(texture_x1y3f, (float)coors.x1y3f.x, (float)coors.x1y3f.y, (float)coors.x1y3f.w, (float)coors.x1y3f.h);
    sprite_x2y3f = sprite_create(texture_x2y3f, (float)coors.x2y3f.x, (float)coors.x2y3f.y, (float)coors.x2y3f.w, (float)coors.x2y3f.h);

    sprite_xm2y3r = sprite_create(texture_xm2y3r, (float)coors.xm2y3r.x, (float)coors.xm2y3r.y, (float)coors.xm2y3r.w, (float)coors.xm2y3r.h);
    sprite_xm1y3r = sprite_create(texture_xm1y3r, (float)coors.xm1y3r.x, (float)coors.xm1y3r.y, (float)coors.xm1y3r.w, (float)coors.xm1y3r.h);
    sprite_x1y3l = sprite_create(texture_x1y3l, (float)coors.x1y3l.x, (float)coors.x1y3l.y, (float)coors.x1y3l.w, (float)coors.x1y3l.h);
    sprite_x2y3l = sprite_create(texture_x2y3l, (float)coors.x2y3l.x, (float)coors.x2y3l.y, (float)coors.x2y3l.w, (float)coors.x2y3l.h);

    array_sprites_count = 0;
    array_sprites_capacity = 37;
    array_sprites = malloc(sizeof *array_sprites * array_sprites_capacity);
    assert(array_sprites != NULL);
    memset(array_sprites, 0, sizeof *array_sprites * array_sprites_capacity);

    array_sprites[array_sprites_count++] = &sprite_main;

    array_sprites[array_sprites_count++] = &sprite_ui_inventory;
    array_sprites[array_sprites_count++] = &sprite_ui_button_camp;
    array_sprites[array_sprites_count++] = &sprite_ui_equipment;
    array_sprites[array_sprites_count++] = &sprite_ui_character_sheet;
    array_sprites[array_sprites_count++] = &sprite_ui_minimap;
    array_sprites[array_sprites_count++] = &sprite_ui_spells;
    array_sprites[array_sprites_count++] = &sprite_ui_portrait_hands;
    array_sprites[array_sprites_count++] = &sprite_ui_compass;
    array_sprites[array_sprites_count++] = &sprite_ui_buttons_direction;

    array_sprites[array_sprites_count++] = &sprite_backdrop;

    array_sprites[array_sprites_count++] = &sprite_xm1y0r;
    array_sprites[array_sprites_count++] = &sprite_x1y0l;

    array_sprites[array_sprites_count++] = &sprite_xm1y1f;
    array_sprites[array_sprites_count++] = &sprite_x0y1f;
    array_sprites[array_sprites_count++] = &sprite_x1y1f;

    array_sprites[array_sprites_count++] = &sprite_xm1y1r;
    array_sprites[array_sprites_count++] = &sprite_x1y1l;

    array_sprites[array_sprites_count++] = &sprite_xm1y2f;
    array_sprites[array_sprites_count++] = &sprite_x0y2f;
    array_sprites[array_sprites_count++] = &sprite_x1y2f;

    array_sprites[array_sprites_count++] = &sprite_xm2y2r;
    array_sprites[array_sprites_count++] = &sprite_xm1y2r;
    array_sprites[array_sprites_count++] = &sprite_x1y2l;
    array_sprites[array_sprites_count++] = &sprite_x2y2l;

    array_sprites[array_sprites_count++] = &sprite_xm2y3f;
    array_sprites[array_sprites_count++] = &sprite_xm1y3f;
    array_sprites[array_sprites_count++] = &sprite_x0y3f;
    array_sprites[array_sprites_count++] = &sprite_x1y3f;
    array_sprites[array_sprites_count++] = &sprite_x2y3f;

    array_sprites[array_sprites_count++] = &sprite_xm2y3r;
    array_sprites[array_sprites_count++] = &sprite_xm1y3r;
    array_sprites[array_sprites_count++] = &sprite_x1y3l;
    array_sprites[array_sprites_count++] = &sprite_x2y3l;

    array_wall_sprites_count = 0;
    array_wall_sprites_capacity = 23;
    array_wall_sprites = malloc(sizeof *array_wall_sprites * array_wall_sprites_capacity);
    assert(array_wall_sprites != NULL);
    memset(array_wall_sprites, 0, sizeof *array_wall_sprites * array_wall_sprites_capacity);

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y0r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y0l;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y1f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x0y1f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y1f;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y1r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y1l;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y2f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x0y2f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y2f;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm2y2r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y2r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y2l;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x2y2l;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm2y3f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y3f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x0y3f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y3f;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x2y3f;

    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm2y3r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_xm1y3r;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x1y3l;
    array_wall_sprites[array_wall_sprites_count++] = &sprite_x2y3l;
}

static void game_init_map(void)
{
    map = map_create(16, 16);

    for (size_t y = 0; y < map_get_height(&map); ++y)
    {
        for (size_t x = 0; x < map_get_width(&map); ++x)
        {
            if ((y == 0 || y == map_get_height(&map) - 1) || (x == 0 || x == map_get_width(&map) - 1))
            {
                map_data_set_at(&map, x, y, 1);
            }
        }
    }

    for (size_t y = 1; y < map_get_height(&map) - 1; ++y)
    {
        for (size_t x = 1; x < map_get_width(&map) - 1; ++x)
        {
            map_data_set_at(&map, x, y, GetRandomValue(0, 100) > 60 ? 1 : 0);
        }
    }

    for (size_t y = 0; y < map_get_height(&map); ++y)
    {
        for (size_t x = 0; x < map_get_width(&map); ++x)
        {
            printf("%i", map_data_get_at(&map, x, y));
        }
        printf("\n");
    }
}

static void game_free(void)
{
    game_free_map();
    game_free_sprites();
    game_free_textures();
    game_free_coors();

    player_x = 0;
    player_y = 0;
    player_f = 0;
}

static void game_free_coors(void)
{
    coors = (struct coors){0};
}

static void game_free_textures(void)
{
    memset(array_backdrop_textures, 0, sizeof(Texture2D) * array_backdrop_textures_length);

    for (size_t i = 0; i < array_textures_count; ++i)
    {
        Texture2D *texture = array_textures[i];
        UnloadTexture(*texture);
    }

    array_textures_count = 0;
    array_textures_capacity = 0;
    free(array_textures);
    array_textures = NULL;

    render_texture_virtual_screen_is_dirty = false;
    UnloadRenderTexture(render_texture_virtual_screen);
    render_texture_virtual_screen_source = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    render_texture_virtual_screen_dest = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    render_texture_virtual_screen_origin = (Vector2){0.0f, 0.0f};
    render_texture_virtual_screen_rotation = 0.0f;
    render_texture_virtual_screen_tint = BLANK;
}

static void game_free_sprites(void)
{
    array_wall_sprites_capacity = 0;
    array_wall_sprites_count = 0;
    free(array_wall_sprites);
    array_wall_sprites = NULL;

    for (size_t i = 0; i < array_sprites_count; ++i)
    {
        struct sprite *sprite = array_sprites[i];
        sprite_free(sprite);
    }

    array_sprites_count = 0;
    array_sprites_capacity = 0;
    free(array_sprites);
    array_sprites = NULL;
}

static void game_free_map(void)
{
    map_free(&map);
}

static void game_tick(float delta)
{
    if (IsKeyPressed(KEY_C))
    {
        sprite_ui_inventory.is_visible = !sprite_ui_inventory.is_visible;
        sprite_ui_equipment.is_visible = !sprite_ui_equipment.is_visible;
        sprite_ui_character_sheet.is_visible = !sprite_ui_character_sheet.is_visible;
        sprite_ui_minimap.is_visible = !sprite_ui_minimap.is_visible;

        render_texture_virtual_screen_is_dirty = true;
    }

    int old_player_x = player_x;
    int old_player_y = player_y;
    int old_player_f = player_f;
    int map_width = (int)map_get_width(&map);
    int map_height = (int)map_get_height(&map);

    if (IsKeyPressed(KEY_A))
    {
        int dx = player_f == 0 ? -1 : player_f == 2 ? 1
                                                    : 0;
        int dy = player_f == 1 ? -1 : player_f == 3 ? 1
                                                    : 0;
        if (dx != 0 || dy != 0)
        {
            int new_x = player_x + dx;
            int new_y = player_y + dy;
            if (new_x >= 0 && new_x < map_width && new_y >= 0 && new_y < map_height)
            {
                if (map_data_get_at(&map, new_x, new_y) == 0)
                {
                    player_x = new_x;
                    player_y = new_y;
                }
            }
        }
    }
    if (IsKeyPressed(KEY_D))
    {
        int dx = player_f == 0 ? 1 : player_f == 2 ? -1
                                                   : 0;
        int dy = player_f == 1 ? 1 : player_f == 3 ? -1
                                                   : 0;
        if (dx != 0 || dy != 0)
        {
            int new_x = player_x + dx;
            int new_y = player_y + dy;
            if (new_x >= 0 && new_x < map_width && new_y >= 0 && new_y < map_height)
            {
                if (map_data_get_at(&map, new_x, new_y) == 0)
                {
                    player_x = new_x;
                    player_y = new_y;
                }
            }
        }
    }
    if (IsKeyPressed(KEY_W))
    {
        int dx = player_f == 3 ? -1 : player_f == 1 ? 1
                                                    : 0;
        int dy = player_f == 0 ? -1 : player_f == 2 ? 1
                                                    : 0;
        if (dx != 0 || dy != 0)
        {
            int new_x = player_x + dx;
            int new_y = player_y + dy;
            if (new_x >= 0 && new_x < map_width && new_y >= 0 && new_y < map_height)
            {
                if (map_data_get_at(&map, new_x, new_y) == 0)
                {
                    player_x = new_x;
                    player_y = new_y;
                }
            }
        }
    }
    if (IsKeyPressed(KEY_S))
    {
        int dx = player_f == 3 ? 1 : player_f == 1 ? -1
                                                   : 0;
        int dy = player_f == 0 ? 1 : player_f == 2 ? -1
                                                   : 0;
        if (dx != 0 || dy != 0)
        {
            int new_x = player_x + dx;
            int new_y = player_y + dy;
            if (new_x >= 0 && new_x < map_width && new_y >= 0 && new_y < map_height)
            {
                if (map_data_get_at(&map, new_x, new_y) == 0)
                {
                    player_x = new_x;
                    player_y = new_y;
                }
            }
        }
    }
    if (IsKeyPressed(KEY_Q))
    {
        player_f = player_f == 0 ? 3 : player_f - 1;
    }
    if (IsKeyPressed(KEY_E))
    {
        player_f = player_f == 3 ? 0 : player_f + 1;
    }

    if (player_x != old_player_x || player_y != old_player_y || player_f != old_player_f)
    {
        flip_backdrop();
        update_compass();
        recalculate_visible_walls();

        render_texture_virtual_screen_is_dirty = true;
    }
}

static void game_draw(void)
{
    if (render_texture_virtual_screen_is_dirty)
    {
        BeginTextureMode(render_texture_virtual_screen);

        ClearBackground(BLANK);

        sprite_draw(&sprite_backdrop);

        sprite_draw(&sprite_xm2y3r);
        sprite_draw(&sprite_xm1y3r);
        sprite_draw(&sprite_x1y3l);
        sprite_draw(&sprite_x2y3l);

        sprite_draw(&sprite_xm2y3f);
        sprite_draw(&sprite_xm1y3f);
        sprite_draw(&sprite_x0y3f);
        sprite_draw(&sprite_x1y3f);
        sprite_draw(&sprite_x2y3f);

        sprite_draw(&sprite_xm2y2r);
        sprite_draw(&sprite_xm1y2r);
        sprite_draw(&sprite_x1y2l);
        sprite_draw(&sprite_x2y2l);

        sprite_draw(&sprite_xm1y2f);
        sprite_draw(&sprite_x0y2f);
        sprite_draw(&sprite_x1y2f);

        sprite_draw(&sprite_xm1y1r);
        sprite_draw(&sprite_x1y1l);

        sprite_draw(&sprite_xm1y1f);
        sprite_draw(&sprite_x0y1f);
        sprite_draw(&sprite_x1y1f);

        sprite_draw(&sprite_xm1y0r);
        sprite_draw(&sprite_x1y0l);

        sprite_draw(&sprite_main);

        sprite_draw(&sprite_ui_inventory);
        sprite_draw(&sprite_ui_button_camp);
        sprite_draw(&sprite_ui_equipment);
        sprite_draw(&sprite_ui_character_sheet);
        sprite_draw(&sprite_ui_minimap);
        sprite_draw(&sprite_ui_spells);
        sprite_draw(&sprite_ui_portrait_hands);

        sprite_draw(&sprite_ui_compass);

        sprite_draw(&sprite_ui_buttons_direction);

        EndTextureMode();

        render_texture_virtual_screen_is_dirty = false;
    }

    BeginDrawing();

    ClearBackground(WHITE);

    DrawTexturePro(render_texture_virtual_screen.texture,
                   render_texture_virtual_screen_source,
                   render_texture_virtual_screen_dest,
                   render_texture_virtual_screen_origin,
                   render_texture_virtual_screen_rotation,
                   render_texture_virtual_screen_tint);

    EndDrawing();
}

static void recalculate_visible_walls(void)
{
    for (size_t i = 0; i < array_wall_sprites_count; ++i)
    {
        array_wall_sprites[i]->is_visible = false;
    }

    //

    int map_width = (int)map_get_width(&map);
    int map_height = (int)map_get_height(&map);

    if (player_f == 0)
    {
        {
            int y = player_y - 3;
            if (y >= 0)
            {
                {
                    int x = player_x - 2;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y3r.is_visible = true;
                            sprite_xm2y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y3r.is_visible = true;
                            sprite_xm1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y3f.is_visible = true;
                    }
                }
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y3l.is_visible = true;
                            sprite_x1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x + 2;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y3l.is_visible = true;
                            sprite_x2y3f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y - 2;
            if (y >= 0)
            {
                {
                    int x = player_x - 2;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y2r.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y2r.is_visible = true;
                            sprite_xm1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y2f.is_visible = true;
                    }
                }
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y2l.is_visible = true;
                            sprite_x1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x + 2;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y2l.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y - 1;
            if (y >= 0)
            {
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y1r.is_visible = true;
                            sprite_xm1y1f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y1f.is_visible = true;
                    }
                }
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y1l.is_visible = true;
                            sprite_x1y1f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y;
            {
                int x = player_x - 1;
                if (x >= 0)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_xm1y0r.is_visible = true;
                    }
                }
            }
            {
                int x = player_x + 1;
                if (x < map_width)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x1y0l.is_visible = true;
                    }
                }
            }
        }
    }

    //

    if (player_f == 1)
    {
        {
            int x = player_x + 3;
            if (x < map_width)
            {
                {
                    int y = player_y - 2;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y3r.is_visible = true;
                            sprite_xm2y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y3r.is_visible = true;
                            sprite_xm1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y3f.is_visible = true;
                    }
                }
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y3l.is_visible = true;
                            sprite_x1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y + 2;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y3l.is_visible = true;
                            sprite_x2y3f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x + 2;
            if (x < map_width)
            {
                {
                    int y = player_y - 2;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y2r.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y2r.is_visible = true;
                            sprite_xm1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y2f.is_visible = true;
                    }
                }
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y2l.is_visible = true;
                            sprite_x1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y + 2;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y2l.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x + 1;
            if (x < map_width)
            {
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y1r.is_visible = true;
                            sprite_xm1y1f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y1f.is_visible = true;
                    }
                }
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y1l.is_visible = true;
                            sprite_x1y1f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x;
            {
                int y = player_y - 1;
                if (y >= 0)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_xm1y0r.is_visible = true;
                    }
                }
            }
            {
                int y = player_y + 1;
                if (y < map_height)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x1y0l.is_visible = true;
                    }
                }
            }
        }
    }

    //

    if (player_f == 2)
    {
        {
            int y = player_y + 3;
            if (y < map_height)
            {
                {
                    int x = player_x + 2;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y3r.is_visible = true;
                            sprite_xm2y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y3r.is_visible = true;
                            sprite_xm1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y3f.is_visible = true;
                    }
                }
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y3l.is_visible = true;
                            sprite_x1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x - 2;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y3l.is_visible = true;
                            sprite_x2y3f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y + 2;
            if (y < map_height)
            {
                {
                    int x = player_x + 2;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y2r.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y2r.is_visible = true;
                            sprite_xm1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y2f.is_visible = true;
                    }
                }
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y2l.is_visible = true;
                            sprite_x1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x - 2;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y2l.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y + 1;
            if (y < map_height)
            {
                {
                    int x = player_x + 1;
                    if (x < map_width)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y1r.is_visible = true;
                            sprite_xm1y1f.is_visible = true;
                        }
                    }
                }
                {
                    int x = player_x;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y1f.is_visible = true;
                    }
                }
                {
                    int x = player_x - 1;
                    if (x >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y1l.is_visible = true;
                            sprite_x1y1f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int y = player_y;
            {
                int x = player_x + 1;
                if (x < map_width)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_xm1y0r.is_visible = true;
                    }
                }
            }
            {
                int x = player_x - 1;
                if (x >= 0)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x1y0l.is_visible = true;
                    }
                }
            }
        }
    }

    //

    if (player_f == 3)
    {
        {
            int x = player_x - 3;
            if (x >= 0)
            {
                {
                    int y = player_y + 2;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y3r.is_visible = true;
                            sprite_xm2y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y3r.is_visible = true;
                            sprite_xm1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y3f.is_visible = true;
                    }
                }
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y3l.is_visible = true;
                            sprite_x1y3f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y - 2;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y3l.is_visible = true;
                            sprite_x2y3f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x - 2;
            if (x >= 0)
            {
                {
                    int y = player_y + 2;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm2y2r.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y2r.is_visible = true;
                            sprite_xm1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y2f.is_visible = true;
                    }
                }
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y2l.is_visible = true;
                            sprite_x1y2f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y - 2;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x2y2l.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x - 1;
            if (x >= 0)
            {
                {
                    int y = player_y + 1;
                    if (y < map_height)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_xm1y1r.is_visible = true;
                            sprite_xm1y1f.is_visible = true;
                        }
                    }
                }
                {
                    int y = player_y;
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x0y1f.is_visible = true;
                    }
                }
                {
                    int y = player_y - 1;
                    if (y >= 0)
                    {
                        if (map_data_get_at(&map, x, y) != 0)
                        {
                            sprite_x1y1l.is_visible = true;
                            sprite_x1y1f.is_visible = true;
                        }
                    }
                }
            }
        }
        {
            int x = player_x;
            {
                int y = player_y + 1;
                if (y < map_height)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_xm1y0r.is_visible = true;
                    }
                }
            }
            {
                int y = player_y - 1;
                if (y >= 0)
                {
                    if (map_data_get_at(&map, x, y) != 0)
                    {
                        sprite_x1y0l.is_visible = true;
                    }
                }
            }
        }
    }
}

static void update_compass(void)
{
    switch (player_f)
    {
    case 0:
        sprite_ui_compass.texture = texture_ui_compass_north;
        break;
    case 1:
        sprite_ui_compass.texture = texture_ui_compass_east;
        break;
    case 2:
        sprite_ui_compass.texture = texture_ui_compass_south;
        break;
    case 3:
        sprite_ui_compass.texture = texture_ui_compass_west;
        break;
    default:
        sprite_ui_compass.texture = texture_ui_compass_north;
        break;
    }
}

static void flip_backdrop(void)
{
    sprite_backdrop.source.width *= -1;
}
