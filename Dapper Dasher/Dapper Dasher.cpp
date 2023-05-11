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

void drawBackground(Vector2& bg1Pos, Vector2& bg2Pos, Vector2& mg1Pos, Vector2& mg2Pos, Vector2& fg1Pos, Vector2& fg2Pos, const Texture2D& background, const Texture2D& midground, const Texture2D& foreground, const float& dt) {
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

void handlePlayer(int& curVel, const int& gravity, const float& dt, const int& jumpVel, AnimData& scarfyData, const int& windowHeight, const Texture2D& scarfy) {
	bool isInAir = !isOnGround(scarfyData, windowHeight);
	if (isInAir) curVel += gravity * dt;
	else curVel = 0;
	if (IsKeyPressed(KEY_SPACE) && !isInAir) curVel = jumpVel;

	scarfyData.pos.y += curVel * dt;

	if (!isInAir) updateAnimData(scarfyData, dt);
	DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
}

void handleNebulae(const int& sizeOfNebulae, AnimData nebulae[6], int nebVel, const float& dt, const Texture2D& nebula) {
	for (int i = 0; i < sizeOfNebulae; i++) {
		nebulae[i].pos.x += nebVel * dt;

		updateAnimData(nebulae[i], dt);
		DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
	}
}

void setupNebulae(const int& sizeOfNebulae, AnimData  nebulae[6], Texture2D& nebula, const int  windowDimensions[2]);

int main() {
	const int windowDimensions[]{ 512, 380 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

	//NEBULA VARIABLES
	int nebVel = -200;
	float nebColliderPad{ 40 };
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	const int sizeOfNebulae{ 6 };
	AnimData nebulae[sizeOfNebulae]{};
	setupNebulae(sizeOfNebulae, nebulae, nebula, windowDimensions);

	float finishLine{ nebulae[sizeOfNebulae - 1].pos.x + 100 };

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
	bool collision{};

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
	float dt{};
	while (!WindowShouldClose()) {
		dt = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		drawBackground(bg1Pos, bg2Pos, mg1Pos, mg2Pos, fg1Pos, fg2Pos, background, midground, foreground, dt);

		for (const AnimData& nebula : nebulae) {
			Rectangle nebRec{
				nebula.pos.x + nebColliderPad,
				nebula.pos.y + nebColliderPad,
				nebula.rec.width - 2 * nebColliderPad,
				nebula.rec.height - 2 * nebColliderPad
			};
			Rectangle scarfyRec{
				 scarfyData.pos.x,	
				 scarfyData.pos.y, 
				 scarfyData.rec.width, 
				 scarfyData.rec.height
			};

			collision = CheckCollisionRecs(nebRec, scarfyRec);
			if (collision) break;
		}

		if (collision) {
			DrawText("Game Over!\nPress Space To Restart", 0, 0, 40, RED);
			if (IsKeyPressed(KEY_SPACE)) {
				setupNebulae(sizeOfNebulae, nebulae, nebula, windowDimensions);
				collision = false;
				finishLine = nebulae[sizeOfNebulae - 1].pos.x + 100;
			}
		}
		else if (finishLine <= scarfyData.pos.x) {
			DrawText("You Win!\nPress Space To Restart", 0, 0, 40, GREEN);
			if (IsKeyPressed(KEY_SPACE)) {
				setupNebulae(sizeOfNebulae, nebulae, nebula, windowDimensions);
				collision = false;
				finishLine = nebulae[sizeOfNebulae - 1].pos.x + 100;
			}
		}
		else {
			handleNebulae(sizeOfNebulae, nebulae, nebVel, dt, nebula);
			handlePlayer(curVel, gravity, dt, jumpVel, scarfyData, windowDimensions[1], scarfy);
			finishLine += nebVel * dt;
		}


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

void setupNebulae(const int& sizeOfNebulae, AnimData  nebulae[6], Texture2D& nebula, const int  windowDimensions[2]) {
	for (int i = 0; i < sizeOfNebulae; i++) {
		nebulae[i] = {
			{ 0.0,0.0, nebula.width / 8.0f, nebula.height / 8.0f },
			{ (float)windowDimensions[0] + (300 * i), (float)windowDimensions[1] - nebula.height / 8.0f },
			0,
			1.0 / 16.0,
			0,
			7
		};
	}

}


