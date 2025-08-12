#include "raylib.h"
#include "rlgl.h"
#include <math.h>
#include <stdlib.h>

int main(void) {
  // screen init
  const int screenWidth = 800;
  const int screenHeight = 450;
  const int target_fps = 60;
  const int playerSize = 50;

  InitWindow(screenWidth, screenHeight, "Top Down View");
  InitAudioDevice();

  bool musicPlaying = true;
  Music epicMusic = LoadMusicStream("./assets/audio/music/Megalovania.ogg");
  PlayMusicStream(epicMusic);
  SetMusicVolume(epicMusic, 0.5f);

  Image OriginalGeorge = LoadImage("./assets/sprites/George.jpg");
  Image George = ImageCopy(OriginalGeorge);

  ImageResize(&George, playerSize, playerSize);
  ExportImage(George, "./assets/sprites/GeorgeResized.png");

  Texture2D texture = LoadTextureFromImage(George);
  UnloadImage(George);

  // fps init
  SetTargetFPS(target_fps);

  // player init

  float playerX_start = screenWidth / 2.0f;
  float playerY_start = screenHeight / 2.0f;
  const int playerSpeed = 10;
  // const float jumpStrength = -15.0f;

  Rectangle player = {playerX_start, playerY_start, playerSize, playerSize};

  // player states

  // player camera init
  Camera2D pcam = {0};
  // center the camera on the player
  pcam.target =
      Vector2{player.x + player.width * 0.5f, player.y + player.height * 0.5f};

  // offset the camera so the player appears in the middle of the screen
  pcam.offset = Vector2{screenWidth * 0.5f, screenHeight * 0.5f};

  pcam.rotation = 0.0f;
  pcam.zoom = 1.0f;

  // main game loop
  while (!WindowShouldClose()) {

    UpdateMusicStream(epicMusic);
    // if (IsKeyPressed(KEY_M)) {
    //   musicPlaying = !musicPlaying;
    //   StopMusicStream(epicMusic);
    //   PlayMusicStream(epicMusic);
    // }

    // restart player position
    if (IsKeyPressed(KEY_R)) {
      player.x = playerX_start;
      player.y = playerY_start;
    }

    // player gravity
    // if (!onGround)
    //   playerY_vel += gravity;
    // player.y += playerY_vel;

    /*
     * Need:
     * 	- Mouse input
     * 	- Player rotate to mouse pos
     * 	- Player move according to rotation
     * 	- Allow for relative "diagonal" movement
     * Extra:
     * 	- Zoom in/out with scroll wheel a limited amount
     */

    // player diagonal movemenet
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) &&
        (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
      // up and right
      player.x += playerSpeed;
      player.y -= playerSpeed;
    } else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) &&
               (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
      // up and left
      player.x -= playerSpeed;
      player.y -= playerSpeed;

    } else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) &&
               (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
      // down and right
      player.x += playerSpeed;
      player.y += playerSpeed;
    } else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) &&
               (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
      // down and left
      player.x -= playerSpeed;
      player.y += playerSpeed;
    }
    // player horizontal movement
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
      player.x += playerSpeed;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
      player.x -= playerSpeed;
    // player vertical movement
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
      player.y -= playerSpeed;
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
      player.y += playerSpeed;

    // player jump
    // if (onGround && IsKeyPressed(KEY_SPACE)) {
    //   playerY_vel = jumpStrength;
    //   onGround = false;
    // }

    // collision check
    // if (CheckCollisionRecs(player, ground1)) {
    //   player.y = ground1.y - player.height;
    //   playerY_vel = 0.0f;
    //   onGround = true;
    // } else {
    //   onGround = false;
    // }

    // follow player

    pcam.target = {player.x + player.width / 2.0f,
                   player.y + player.height / 2.0f};

    // rendering
    BeginDrawing();

    // background render
    ClearBackground(RAYWHITE);

    BeginMode2D(pcam);

    // render background grid
    rlPushMatrix();
    rlTranslatef(0, 25 * 50, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(100, 50);
    rlPopMatrix();

    // player render
    DrawRectangleRec(player, BLUE);
    DrawTexture(texture, player.x, player.y, WHITE);

    EndMode2D();

    // render player coords
    DrawTextEx(GetFontDefault(),
               TextFormat("Player Coords: [%.0f, %.0f]", player.x, player.y),
               Vector2{10.0f, 10.0f}, 20.0f, 2.0f, BLACK);

    // render FPS
    DrawTextEx(GetFontDefault(), TextFormat("FPS: %d", GetFPS()),
               Vector2{10.0f, 40.0f}, 20.0f, 2.0f, BLACK);

    // render is music on?
    // DrawTextEx(GetFontDefault(), TextFormat("Music : %s", musicPlaying),
    // Vector2{10.0f, 60.0f}, 20.0f, 2.0f, BLACK);

    pcam.target = Vector2{player.x + player.width / 2.0f,
                          player.y + player.height / 2.0f};
    pcam.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
    pcam.rotation = 0.0f;
    pcam.zoom = 1.0f;

    EndDrawing();
  }
  UnloadTexture(texture);
  UnloadMusicStream(epicMusic);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
