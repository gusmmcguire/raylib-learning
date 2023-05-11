#include "raylib.h"

int main() {
	const int windowWidth = 512;
	const int windowHeight = 380;
	InitWindow(windowWidth, windowHeight, "Dapper Dasher");

	//acceleration due to gravity (pixels/s)/s
	const int gravity = 1000;
	int curVel = 0;
	const int jumpVel = -600;
	bool isInAir = false;

	//NEBULA VARIABLES
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

	//SCARFY VARIABLES
	//load character spritesheet
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	//location in sprite sheet
	Rectangle scarfyRect;
	scarfyRect.width = scarfy.width / 6;
	scarfyRect.height = scarfy.height;
	scarfyRect.x = 0;
	scarfyRect.y = 0;
	//location on screen
	Vector2 scarfyPos;
	scarfyPos.x = windowWidth / 2 - scarfyRect.width / 2;
	scarfyPos.y = windowHeight - scarfyRect.height;
	//animation
	int frame{};
	float runningTime{};
	const float updateTime = 1.0 / 10.0;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();
		runningTime += dt;
		
		//start drawing
		BeginDrawing();
		ClearBackground(WHITE);
		
		//apply acceleration
		if (isInAir) curVel += gravity * dt;
		else curVel = 0;

		//check for jump
		if (IsKeyPressed(KEY_SPACE) && !isInAir) curVel = jumpVel;

		//update position
		scarfyPos.y += curVel * dt;
		isInAir = scarfyPos.y <= windowHeight - scarfy.height;

		//update animation frame
		if (runningTime >= updateTime) {
			runningTime = 0;
			if (++frame > 5) frame = 0;
			scarfyRect.x = frame * scarfyRect.width;
		}
		

		//draw character
		DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

		//stop drawing
		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
	return 0;
}