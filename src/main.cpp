#include <stdlib.h>
#include <iostream>
#include "raylib.h"

int main(void){
	std::cout << "Hello World!" << std::endl;

	const int screenWidth = 800;
	const int screenHeight = 450;
	const int target_fps = 60;

	InitWindow(screenWidth, screenHeight, "Testing");

	SetTargetFPS(target_fps);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("My First Window", 190, 200, 20, LIGHTGRAY);
	EndDrawing();
	}

	CloseWindow();
	return 0;
}
