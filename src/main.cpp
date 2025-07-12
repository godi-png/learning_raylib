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
		ClearBackground(BLACK);
		DrawRectangle(screenWidth/2, screenHeight/2,screenWidth/4,screenHeight/4,WHITE);
		DrawText("Job application",screenWidth/2, screenHeight/2,5,BLACK);
	EndDrawing();
	}

	CloseWindow();
	return 0;
}
