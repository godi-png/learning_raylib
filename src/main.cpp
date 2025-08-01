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
	const float gravity = 1.f;
	float playerY_vel = 0.0f;

	// ground init
	const float groundX = 0.0f;
	const float groundY = 350.0f;
	const float groundWidth = screenWidth * 5;
	const float groundHeight = screenHeight;
	
	const Rectangle ground1 = {groundX, groundY, groundWidth, groundHeight};
	
	// player init
	const int playerSize = 50;
	float playerX_start = screenWidth/2.0f;
	float playerY_start = ground1.y - playerSize;
	const int playerSpeed = 10;
	const float jumpStrength = -15.0f;

	Rectangle player = {playerX_start, playerY_start, playerSize, playerSize};

	// player states
	bool onGround = false;

	// player camera init
	Camera2D pcam = {0};
	pcam.target = (Vector2){player.x + player.width/2.0f, player.y + player.height/2.0f};
	pcam.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
	pcam.rotation = 0.0f;
	pcam.zoom = 1.0f;

	// main game loop
	while(!WindowShouldClose()){
		// restart player position
		if(IsKeyPressed(KEY_R)){
			player.x = playerX_start;
			player.y = playerY_start;
		}

		// player gravity
		if(!onGround) playerY_vel += gravity;
		player.y += playerY_vel;

		// player horizontal movement
		if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += playerSpeed;
		else if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= playerSpeed;

		// player jump
		if(onGround && IsKeyPressed(KEY_SPACE)){
			playerY_vel = jumpStrength;
			onGround = false;
		}

		// collision check
		if(CheckCollisionRecs(player, ground1)){
			player.y = ground1.y - player.height;
			playerY_vel = 0.0f;
			onGround = true;
		} else{
			onGround = false;
		}

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
				DrawRectangleRec(ground1, DARKGREEN);

				// player render
				DrawRectangleRec(player, BLUE);
			EndMode2D();
		EndDrawing();


	}

	CloseWindow();
	return 0;
}
