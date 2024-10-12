#include "game_scene.h"
#include "raylib.h"

// Virtual screen dimensions
static const int virtual_screen_width = 320;
static const int virtual_screen_height = 200;

// Screen size multiplier for scaling
static const int screen_size_multiplier = 4;

// Window dimensions based on virtual screen and multiplier
static const int window_width = virtual_screen_width * screen_size_multiplier;
static const int window_height = virtual_screen_height * screen_size_multiplier;

// Struct to hold render texture data
struct render_texture_data {
    RenderTexture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
};


// Game scene
static struct scene game_scene;

// Render texture data
static struct render_texture_data render_texture_data;

// Function prototypes
static void game_init(void);
static void game_init_virtual_screen(void);
static void game_init_scenes(void);

static void game_free(void);
static void game_free_virtual_screen(void);
static void game_free_scenes(void);

static void game_tick(float delta);
static void game_draw(void);

/**
 * @brief Main function of the game.
 *
 * Initializes the window, game, and runs the main game loop.
 *
 * @return 0 if the game exits successfully.
 */
int main(void)
{
    // Initialize the window
    InitWindow(window_width, window_height, "Dungeon Whack");
    SetTargetFPS(60);

    // Initialize the game
    game_init();

    float delta = 0.0f;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Restart game on 'R' key press
        if (IsKeyPressed(KEY_R))
        {
            game_free();
            game_init();
        }

        // Get frame time
        delta = GetFrameTime();

        // Update game state
        game_tick(delta);

        // Draw game
        game_draw();
    }

    // Free game resources
    game_free();

    // Close window
    CloseWindow();

    return 0;
}

/**
 * @brief Initializes the game.
 *
 * Initializes the virtual screen and game scenes.
 */
static void game_init(void)
{
    game_init_virtual_screen();
    game_init_scenes();
}

/**
 * @brief Initializes the virtual screen.
 *
 * Loads the render texture for the virtual screen and sets up rendering parameters.
 */
static void game_init_virtual_screen(void)
{
    render_texture_data.texture = LoadRenderTexture(virtual_screen_width, virtual_screen_height);
    render_texture_data.source = (Rectangle){0.0f, 0.0f, (float)render_texture_data.texture.texture.width, -(float)render_texture_data.texture.texture.height};
    render_texture_data.dest = (Rectangle){0.0f, 0.0f, (float)window_width, (float)window_height};
    render_texture_data.origin = (Vector2){0.0f, 0.0f};
    render_texture_data.rotation = 0.0f;
    render_texture_data.tint = WHITE;
}

/**
 * @brief Initializes the game scenes.
 *
 * Initializes the scene virtual table and creates the game scene.
 */
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

/**
 * @brief Frees game resources.
 *
 * Frees the virtual screen and game scenes.
 */
static void game_free(void)
{
    game_free_scenes();
    game_free_virtual_screen();
}

/**
 * @brief Frees the virtual screen resources.
 *
 * Unloads the render texture for the virtual screen and resets rendering parameters.
 */
static void game_free_virtual_screen(void)
{
    UnloadRenderTexture(render_texture_data.texture);
    render_texture_data.source = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    render_texture_data.dest = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    render_texture_data.origin = (Vector2){0.0f, 0.0f};
    render_texture_data.rotation = 0.0f;
    render_texture_data.tint = BLANK;
}

/**
 * @brief Frees the game scenes resources.
 *
 * Exits and frees the game scene and frees the scene virtual table.
 */
static void game_free_scenes(void)
{
    scene_exit(&game_scene);

    scene_free(&game_scene);

    GAME_SCENE_TAG = 0;

    scene_vtable_free();
}

/**
 * @brief Updates the game state.
 *
 * Updates the game scene based on the elapsed time.
 * @param delta Time elapsed since the last frame.
 */
static void game_tick(float delta)
{
    scene_tick(&game_scene, delta);
}

/**
 * @brief Draws the game.
 *
 * Renders the game scene to the virtual screen and then draws the virtual screen to the main screen.
 */
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
