#include "game_scene.h"

#include "raylib.h"

#include <string.h>

static const int virtual_screen_width = 320;
static const int virtual_screen_height = 200;

static const int screen_size_multiplier = 4;

static const int window_width = virtual_screen_width * screen_size_multiplier;
static const int window_height = virtual_screen_height * screen_size_multiplier;

struct render_texture_data
{
    RenderTexture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
};

static struct scene game_scene;

static struct render_texture_data render_texture_data;

static void game_init(void);
static void game_init_virtual_screen(void);
static void game_init_scenes(void);

static void game_free(void);
static void game_free_virtual_screen(void);
static void game_free_scenes(void);

static void game_tick(float delta);
static void game_draw(void);

int main(void)
{
    InitWindow(window_width, window_height, "Dungeon Whack");
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
    game_init_virtual_screen();
    game_init_scenes();
}

static void game_init_virtual_screen(void)
{
    render_texture_data.texture = LoadRenderTexture(virtual_screen_width, virtual_screen_height);
    render_texture_data.source = (Rectangle){0.0f, 0.0f, (float)render_texture_data.texture.texture.width, -(float)render_texture_data.texture.texture.height};
    render_texture_data.dest = (Rectangle){0.0f, 0.0f, (float)window_width, (float)window_height};
    render_texture_data.origin = (Vector2){0.0f, 0.0f};
    render_texture_data.rotation = 0.0f;
    render_texture_data.tint = WHITE;
}

static void game_init_scenes(void)
{
    scene_vtable_init();

    GAME_SCENE_TAG = scene_vtable_register((struct scene_funcs){
        .free = game_scene_free,
        .enter = game_scene_enter,
        .exit = game_scene_exit,
        .tick = game_scene_tick,
        .draw = game_scene_draw});

    game_scene = game_scene_create();

    scene_enter(&game_scene);
}

static void game_free(void)
{
    game_free_scenes();
    game_free_virtual_screen();
}

static void game_free_virtual_screen(void)
{
    UnloadRenderTexture(render_texture_data.texture);
    render_texture_data = (struct render_texture_data){0};
}

static void game_free_scenes(void)
{
    scene_exit(&game_scene);

    scene_free(&game_scene);

    GAME_SCENE_TAG = 0;

    scene_vtable_free();
}

static void game_tick(float delta)
{
    scene_tick(&game_scene, delta);
}

static void game_draw(void)
{
    BeginTextureMode(render_texture_data.texture);
    ClearBackground(BLANK);
    scene_draw(&game_scene);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexturePro(
        render_texture_data.texture.texture,
        render_texture_data.source,
        render_texture_data.dest,
        render_texture_data.origin,
        render_texture_data.rotation,
        render_texture_data.tint);
    EndDrawing();
}
