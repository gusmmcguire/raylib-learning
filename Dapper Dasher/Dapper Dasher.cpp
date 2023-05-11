#include "raylib.h"

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
	float maxFrame;
};

bool isOnGround(const AnimData& data, const int& windowHeight) {
	return data.pos.y >= windowHeight - data.rec.height;
}

void updateAnimData(AnimData &data, const float& deltaTime) {
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime) {
		data.runningTime = 0;
		data.rec.x = data.frame * data.rec.width;
		if (++data.frame > data.maxFrame) data.frame = 0;
	}
}

int main() {
	const int windowDimensions[]{ 512, 380 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

	//NEBULA VARIABLES
	int nebVel = -200;
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	const int sizeOfNebulae{6};
	AnimData nebulae[sizeOfNebulae]{};
	for (int i = 0; i < sizeOfNebulae; i++) {
		nebulae[i].rec.x = 0.0;
		nebulae[i].rec.y = 0.0;
		nebulae[i].rec.width = nebula.width / 8;
		nebulae[i].rec.height = nebula.height / 8;

		nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;

		nebulae[i].frame = 0;
		nebulae[i].maxFrame = 7;

		nebulae[i].runningTime = 0.0;
		nebulae[i].updateTime = 1.0 / 16.0;
		nebulae[i].pos.x = windowDimensions[0] + (300 * i);
	}

	//SCARFY VARIABLES
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData{
		{ 0.0, 0.0, scarfy.width / 6, scarfy.height },
		{ windowDimensions[0] / 2 - scarfyData.rec.width / 2, windowDimensions[1] - scarfyData.rec.height },
		0,
		1.0 / 10.0,
		0,
		5
	};
	
	const int gravity = 1000;
	int curVel = 0;
	const int jumpVel = -600;
	bool isInAir = false;

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);


		for (int i = 0; i < sizeOfNebulae; i++) {
			nebulae[i].pos.x += nebVel * dt;

			updateAnimData(nebulae[i], dt);
			DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
		}

		if (isInAir) curVel += gravity * dt;
		else curVel = 0;
		if (IsKeyPressed(KEY_SPACE) && !isInAir) curVel = jumpVel;

		scarfyData.pos.y += curVel * dt;
		isInAir = !isOnGround(scarfyData, windowDimensions[1]);

		if (!isInAir) updateAnimData(scarfyData, dt);
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		//stop drawing
		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
	return 0;
}