#include "../include/Player.h"
#include "../include/constants.h"
#include "raylib.h"
#include <iostream>

int main() {
  Player p;

  InitWindow(cfg::window::WIDTH, cfg::window::HEIGHT, cfg::window::TITLE);
  InitAudioDevice();
  SetTargetFPS(cfg::window::TARGET_FPS);

  Music epicMusic = LoadMusicStream(cfg::asset::MUSIC);
  PlayMusicStream(epicMusic);

  Image img = LoadImage(cfg::asset::GEORGEIMG);
  ImageResize(&img, cfg::player::SIZE, cfg::player::SIZE);
  Texture2D texture = LoadTextureFromImage(img);
  UnloadImage(img);

  const float gravity = cfg::world::GRAVITY;
  const Rectangle ground = {0.0f, cfg::world::GROUND_Y,
                            cfg::window::WIDTH * 5.0f,
                            cfg::window::HEIGHT * 1.0f};

  Rectangle player = {cfg::window::WIDTH * 0.5f - cfg::player::SIZE * 0.5f,
                      ground.y - cfg::player::SIZE,
                      static_cast<float>(cfg::player::SIZE),
                      static_cast<float>(cfg::player::SIZE)};
  Vector2 velocity{0.0f, 0.0f};
  const float moveSpeed = cfg::player::SPEED.x; // pixels per frame
  const float jumpStrength = -15.0f;            // negative = up
  bool onGround = true;

  Camera2D cam{};
  cam.offset = {cfg::window::WIDTH * 0.5f, cfg::window::HEIGHT * 0.5f};
  cam.target = {player.x + player.width * 0.5f,
                player.y + player.height * 0.5f};
  cam.rotation = 0.0f;
  cam.zoom = 1.0f;

  while (!WindowShouldClose()) {
    // Update audio
    UpdateMusicStream(epicMusic);

    // -------- Update --------
    // Horizontal input
    if (IsKeyDown(KEY_D))
      velocity.x += moveSpeed;
    if (IsKeyDown(KEY_A))
      velocity.x -= moveSpeed;

    // Jump
    if (onGround && IsKeyPressed(KEY_SPACE)) {
      velocity.y = jumpStrength;
      onGround = false;
    }
    // this does not work, I have to fix it :'v
    p.updatePosition();
    // Gravity
    velocity.y += gravity;

    // Apply movement
    player.x += velocity.x;
    player.y += velocity.y;

    // Ground collision, this also does not work well
    if (player.y + player.height >= ground.y) {
      player.y = ground.y - player.height;
      velocity.y = 0.0f;
      onGround = true;
    }

    // Camera follow (center on player)
    cam.target = {player.x + player.width * 0.5f,
                  player.y + player.height * 0.5f};

    // -------- Draw --------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(cam);
    DrawRectangleRec(ground, GREEN);                    // ground
    DrawTextureV(texture, {player.x, player.y}, WHITE); // player
    EndMode2D();

    DrawText("this shit does not have falling object support :v", 10, 10, 20,
             DARKGRAY);

    EndDrawing();
  }

  // --- De-init ---
  UnloadTexture(texture);
  UnloadMusicStream(epicMusic);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
