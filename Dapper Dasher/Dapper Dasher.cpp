#include "raylib.h"

int main() {
	const int windowWidth = 512;
	const int windowHeight = 380;

	//rect dimensions
	const int width = 50;
	const int height = 80;

	int posY = windowHeight - height;
	int vel = 0;

	//acceleration due to gravity (pixels/frame)/frame
	const int gravity = 1;
	const int jumpVel = -20;
	bool isInAir = false;


	InitWindow(windowWidth, windowHeight, "Dapper Dasher");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		//start drawing
		BeginDrawing();
		ClearBackground(WHITE);
		
		if (isInAir) vel += gravity;
		else vel = 0;

		if (IsKeyPressed(KEY_SPACE) && !isInAir) vel = jumpVel;

		//update position
		posY += vel;
		isInAir = posY <= windowHeight - height;


		DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

		//stop drawing
		EndDrawing();
	}
	CloseWindow();
	return 0;
}