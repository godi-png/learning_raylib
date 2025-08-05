#include "raylib.h"
#include <iostream>
#include <math.h>
// #include <stdlib.h>

int main(void) {
  std::cout << "Hello World!" << std::endl;

  // screen init
  const int screenWidth = 800;
  const int screenHeight = 450;
  const int target_fps = 60;
  const int playerSize = 50;


  InitWindow(screenWidth, screenHeight, "Testing");
  InitAudioDevice();

  Music epicMusic = LoadMusicStream("./assets/Megalovania.ogg");
  PlayMusicStream(epicMusic);
  SetMusicVolume(epicMusic,0.5f);

  Image OriginalGeorge = LoadImage("./assets/George.jpg");
  Image George = ImageCopy(OriginalGeorge);
  
  ImageResize(&George,playerSize,playerSize);
  ExportImage(George,"GeorgeResized.png");
  
  Texture2D texture = LoadTextureFromImage(George);
  UnloadImage(George);

  // fps init
  SetTargetFPS(target_fps);

  // world params
  const float gravity = 1.f;
  float playerY_vel = 0.0f;

  // ground init
  const float groundX = 0.0f;
  const float groundY = 350.0f;
  const float groundWidth = screenWidth * 5;
  const float groundHeight = screenHeight;

  const Rectangle ground1 = {groundX, groundY, groundWidth, groundHeight};

  // player init
  
  float playerX_start = screenWidth / 2.0f;
  float playerY_start = ground1.y - playerSize;
  const int playerSpeed = 10;
  const float jumpStrength = -15.0f;

  Rectangle player = {playerX_start, playerY_start, playerSize, playerSize};

  // player states
  bool onGround = false;

  // player camera init
  Camera2D pcam = {0};
  // center the camera on the player
  pcam.target = Vector2{player.x + player.width * 0.5f, player.y + player.height * 0.5f};

  // offset the camera so the player appears in the middle of the screen
  pcam.offset = Vector2{screenWidth * 0.5f, screenHeight * 0.5f};

  pcam.rotation = 0.0f;
  pcam.zoom = 1.0f;

  // main game loop
  while (!WindowShouldClose()) {
    UpdateMusicStream(epicMusic);
    // restart player position
    if (IsKeyPressed(KEY_R)) {
      player.x = playerX_start;
      player.y = playerY_start;
    }

    // player gravity
    if (!onGround)
      playerY_vel += gravity;
    player.y += playerY_vel;

    // player horizontal movement
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
      player.x += playerSpeed;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
      player.x -= playerSpeed;

    // player jump
    if (onGround && IsKeyPressed(KEY_SPACE)) {
      playerY_vel = jumpStrength;
      onGround = false;
    }

    // collision check
    if (CheckCollisionRecs(player, ground1)) {
      player.y = ground1.y - player.height;
      playerY_vel = 0.0f;
      onGround = true;
    } else {
      onGround = false;
    }

    // follow player

    pcam.target = {player.x + player.width / 2.0f,
                   player.y + player.height / 2.0f};

    // rendering
    BeginDrawing();

    // background render
    ClearBackground(RAYWHITE);

    // render player coords
    // Render player coordinates
    DrawTextEx(GetFontDefault(),
               TextFormat("Player Coords: [%.0f, %.0f]", player.x, player.y),
               Vector2{10.0f, 10.0f}, 20.0f, 2.0f, BLACK);

    // Render FPS
    DrawTextEx(GetFontDefault(), TextFormat("FPS: %d", GetFPS()),
               Vector2{10.0f, 40.0f}, 20.0f, 2.0f, BLACK);

    BeginMode2D(pcam);
    // ground drawn
    DrawRectangleRec(ground1, DARKGREEN);

    // player render
    DrawRectangleRec(player, BLUE);
    DrawTexture(texture,player.x,player.y,WHITE);
    EndMode2D();
    EndDrawing();
    
  }
  UnloadTexture(texture);
  UnloadMusicStream(epicMusic);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
