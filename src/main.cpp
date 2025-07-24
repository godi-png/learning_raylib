#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include <math.h>

int main(void){
	std::cout << "Hello World!" << std::endl;

	// screen init
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int target_fps = 60;

	InitWindow(screenWidth, screenHeight, "nepe");

	// fps init
	SetTargetFPS(target_fps);

	// world params
	const int gravity = -10;

	// ground init
	const float groundY = 350.0f;
	const int groundWidth = screenWidth * 5;
	
	// player init
	const int playerSize = 50;
	float playerX_start = screenWidth/2.0f;
	float playerY_start = groundY - playerSize;
	const int playerSpeed = 10;

	Rectangle player = {playerX_start, playerY_start, playerSize, playerSize};

	// player camera init
	Camera2D pcam = {0};
	pcam.target = (Vector2){player.x + player.width/2.0f, player.y + player.height/2.0f};
	pcam.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
	pcam.rotation = 0.0f;
	pcam.zoom = 1.0f;

	// main game loop
	while(!WindowShouldClose()){
		// player gravity
		if(player.x <= -playerSize || player.x >= groundWidth + playerSize) player.y -= gravity;

		// player horizontal movement
		if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += playerSpeed;
		else if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= playerSpeed;

		// player jump

		// follow player
		pcam.target = (Vector2){player.x + player.width/2.0f, player.y + player.height/2.0f};

		// rendering
		BeginDrawing();
			// background render
			ClearBackground(RAYWHITE);

			// render player coords
			DrawTextEx(GetFontDefault(), TextFormat("Player Coords: [%.0f, %.0f]", player.x, player.y), (Vector2){10, 10}, 20, 2, BLACK);
			// render fps
			DrawTextEx(GetFontDefault(), TextFormat("FPS: %i", GetFPS()), (Vector2){10, 40}, 20, 2, BLACK);
			BeginMode2D(pcam);
				// ground drawn
				DrawRectangle(0, groundY, groundWidth, screenHeight, DARKGREEN);

				// player render
				DrawRectangleRec(player, BLUE);
			EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
