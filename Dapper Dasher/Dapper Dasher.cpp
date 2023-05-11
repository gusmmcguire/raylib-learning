#include "raylib.h"

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	const float updateTime;
	float runningTime;
};


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
	//spritesheet
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	//AnimData for nebula
	AnimData nebData{ 
		{ 0.0, 0.0, nebula.width / 8, nebula.width / 8 },
		{ windowWidth, windowHeight - nebData.rec.height },
		0,
		1.0 / 12.0,
		0
	};
	//AnimData for nebula2
	AnimData neb2Data{
		{ 0.0, 0.0, nebula.width / 8, nebula.width / 8 },
		{ windowWidth + 300, windowHeight - nebData.rec.height },
		0,
		1.0 / 16.0,
		0
	};

	int nebVel = -200;

//SCARFY VARIABLES
	//spritesheet
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData{ 
		{ 0.0, 0.0, scarfy.width / 6, scarfy.height },
		{ windowWidth / 2 - scarfyData.rec.width / 2, windowHeight - scarfyData.rec.height },
		0,
		1.0 / 10.0,
		0
	};
	

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();
		scarfyData.runningTime += dt;
		nebData.runningTime += dt;
		neb2Data.runningTime += dt;

		//start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		//apply acceleration
		if (isInAir) curVel += gravity * dt;
		else curVel = 0;

		//check for jump
		if (IsKeyPressed(KEY_SPACE) && !isInAir) curVel = jumpVel;

		//update nebula position
		nebData.pos.x += nebVel * dt;
		neb2Data.pos.x += nebVel * dt;

		//update scarfy position
		scarfyData.pos.y += curVel * dt;
		isInAir = scarfyData.pos.y <= windowHeight - scarfy.height;

		//update scarfy animation frame
		if (!isInAir && scarfyData.runningTime >= scarfyData.updateTime) {
			scarfyData.runningTime = 0;
			scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
			if (++scarfyData.frame > 5) scarfyData.frame = 0;
		}

		//update nebula animation frame
		if (nebData.runningTime >= nebData.updateTime) {
			nebData.runningTime = 0;
			nebData.rec.x = nebData.frame * nebData.rec.width;
			if (++nebData.frame > 7) nebData.frame = 0;
		}
		if (neb2Data.runningTime >= neb2Data.updateTime) {
			neb2Data.runningTime = 0;
			neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
			if (++neb2Data.frame > 7) neb2Data.frame = 0;
		}

		//draw nebula
		DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
		//draw second nebula
		DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

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