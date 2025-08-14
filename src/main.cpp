#include "raylib.h"
#include "constants.h"
#include "Player.h"

int main() {
    // --- Initialization ---
    InitWindow(cfg::window::WIDTH, cfg::window::HEIGHT, cfg::window::TITLE);
    InitAudioDevice();
    SetTargetFPS(cfg::window::TARGET_FPS);

    Music epicMusic = LoadMusicStream(cfg::asset::MUSIC);
    PlayMusicStream(epicMusic);

    Image img = LoadImage(cfg::asset::GEORGEIMG);
    ImageResize(&img, cfg::player::SIZE, cfg::player::SIZE);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    // Create player
    Player player;

    const Rectangle ground = {
        0.0f,
        cfg::world::GROUND_Y,
        cfg::window::WIDTH * 5.0f,
        cfg::window::HEIGHT * 1.0f
    };

    Camera2D cam{};
    cam.offset = { cfg::window::WIDTH * 0.5f, cfg::window::HEIGHT * 0.5f };
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;
    cam.target = {
            player.getPosition().x + cfg::player::SIZE * 0.5f,
            player.getPosition().y + cfg::player::SIZE * 0.5f
    };
    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        UpdateMusicStream(epicMusic);

        // -------- Update --------
        // All player logic does not work but now it is inside of the function :D 
        player.updatePosition();
        

        // Camera follows the player object
        cam.target = {
            player.getPosition().x + cfg::player::SIZE * 0.5f,
            player.getPosition().y + cfg::player::SIZE * 0.5f
        };

        // -------- Draw --------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(cam);
        DrawRectangleRec(ground, GREEN);
        // Draw the player at its correct position
        DrawTextureV(texture, player.getPosition(), WHITE);
        EndMode2D();

        DrawText("still does not work", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    // --- De-initialization ---
    UnloadTexture(texture);
    UnloadMusicStream(epicMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}