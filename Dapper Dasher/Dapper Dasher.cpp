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

void updateAnimData(AnimData& data, const float& deltaTime) {
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime) {
		data.runningTime = 0;
		data.rec.x = data.frame * data.rec.width;
		if (++data.frame > data.maxFrame) data.frame = 0;
	}
}

void drawBackground(Vector2 &bg1Pos, Vector2 &bg2Pos, Vector2 &mg1Pos, Vector2 &mg2Pos, Vector2 &fg1Pos, Vector2 & fg2Pos, const Texture2D& background, const Texture2D& midground, const Texture2D& foreground, const float dt) {
	bg1Pos.x -= 20 * dt;
	mg1Pos.x -= 40 * dt;
	fg1Pos.x -= 80 * dt;
	if (bg1Pos.x <= -background.width * 2) {
		bg1Pos.x = 0.0;
	}
	if (mg1Pos.x <= -midground.width * 2) {
		mg1Pos.x = 0.0;
	}
	if (fg1Pos.x <= -foreground.width * 2) {
		fg1Pos.x = 0.0;
	}
	//background
	DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
	bg2Pos.x = bg1Pos.x + background.width * 2;
	DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
	//midground
	DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
	mg2Pos.x = mg1Pos.x + midground.width * 2;
	DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
	//foreground
	DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
	fg2Pos.x = fg1Pos.x + foreground.width * 2;
	DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);
}

int main() {
	const int windowDimensions[]{ 512, 380 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

	//NEBULA VARIABLES
	int nebVel = -200;
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	const int sizeOfNebulae{ 6 };
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

	//BACKGROUND VARIABLES
	Texture2D background = LoadTexture("textures/far-buildings.png");
	Vector2 bg1Pos{ 0.0 , 0.0 };
	Vector2 bg2Pos{ background.width * 2 , 0.0 };
	
	//MIDGROUND VARIABLES
	Texture2D midground = LoadTexture("textures/back-buildings.png");
	Vector2 mg1Pos{ 0.0 , 0.0 };
	Vector2 mg2Pos{ midground.width * 2 , 0.0 };

	//FOREGROUND VARIABLES
	Texture2D foreground = LoadTexture("textures/foreground.png");
	Vector2 fg1Pos{ 0.0 , 0.0 };
	Vector2 fg2Pos{ foreground.width * 2 , 0.0 };


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		drawBackground(bg1Pos, bg2Pos, mg1Pos, mg2Pos, fg1Pos, fg2Pos, background, midground, foreground, dt);

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
	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);

	CloseWindow();
	return 0;
}