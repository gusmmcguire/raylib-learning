#include "raylib.h"

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};


int main() {
	const int windowDimensions[]{ 512, 380 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

	//acceleration due to gravity (pixels/s)/s
	const int gravity = 1000;
	int curVel = 0;
	const int jumpVel = -600;
	bool isInAir = false;

	//NEBULA VARIABLES
		//spritesheet
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	//AnimData for nebula
	const int sizeOfNebulae{6};
	AnimData nebulae[sizeOfNebulae]{};

	for (int i = 0; i < sizeOfNebulae; i++) {
		nebulae[i].rec.x = 0.0;
		nebulae[i].rec.y = 0.0;
		nebulae[i].rec.width = nebula.width / 8;
		nebulae[i].rec.height = nebula.height / 8;

		nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;

		nebulae[i].frame = 0;

		nebulae[i].runningTime = 0.0;
		nebulae[i].updateTime = 1.0 / 16.0;
		nebulae[i].pos.x = windowDimensions[0] + (300 * i);
	}

	int nebVel = -200;

	//SCARFY VARIABLES
		//spritesheet
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData{
		{ 0.0, 0.0, scarfy.width / 6, scarfy.height },
		{ windowDimensions[0] / 2 - scarfyData.rec.width / 2, windowDimensions[1] - scarfyData.rec.height },
		0,
		1.0 / 10.0,
		0
	};

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();
		scarfyData.runningTime += dt;

		//start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		//apply acceleration
		if (isInAir) curVel += gravity * dt;
		else curVel = 0;

		//check for jump
		if (IsKeyPressed(KEY_SPACE) && !isInAir) curVel = jumpVel;

		//update scarfy position
		scarfyData.pos.y += curVel * dt;
		isInAir = scarfyData.pos.y <= windowDimensions[1] - scarfy.height;

		//update scarfy animation frame
		if (!isInAir && scarfyData.runningTime >= scarfyData.updateTime) {
			scarfyData.runningTime = 0;
			scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
			if (++scarfyData.frame > 5) scarfyData.frame = 0;
		}

		//update nebulae
		for (int i = 0; i < sizeOfNebulae; i++) {
			//delta time increase
			nebulae[i].runningTime += dt;
			//move nebula
			nebulae[i].pos.x += nebVel * dt;
			//animate nebula
			if (nebulae[i].runningTime >= nebulae[i].updateTime) {
				nebulae[i].runningTime = 0;
				nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
				if (++nebulae[i].frame > 7) nebulae[i].frame = 0;
			}
			//draw nebula
			DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
		}

		//draw scarfy
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		//stop drawing
		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
	return 0;
}