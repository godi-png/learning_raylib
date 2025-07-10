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

	InitWindow(screenWidth, screenHeight, "pene");

	// fps init
	SetTargetFPS(target_fps);
	
	// player init
	const int playerSize = 100;
	float playerX_start = 100;//screenWidth/2.0f;
	float playerY_start = 100;//screenHeight/2.0f;

	Rectangle player = {playerX_start, playerY_start, playerSize};

	// player camera init
	Camera2D pcam = {0};
	pcam.target = (Vector2){player.x + 20.0f, player.y + 20.0f};
	pcam.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
	pcam.rotation = 0.0f;
	pcam.zoom = 1.0f;

	// main game loop
	while(!WindowShouldClose()){
		// player horizontal movment
		if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += 4;
		else if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= 4;

		// rendering
		BeginDrawing();
			// background render
			ClearBackground(RAYWHITE);
			DrawRectangle(0, screenHeight-(screenHeight/2.0f), screenWidth, screenHeight, DARKGREEN);
			BeginMode2D(pcam);
				// player render
				DrawRectangleRec(player, BLUE);
				std::cout << "Player x: " << player.x << std::endl;
				std::cout << "Player y: " << player.y << std::endl;
			EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
