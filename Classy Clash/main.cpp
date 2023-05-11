#include "raylib.h"
#include "raymath.h"

int main() {
	const int windowDimensions[]{ 384,384 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{ 0,0 };

	const float speed{ 4 };

	Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

	Texture2D knight = knight_idle;
	Vector2 knightPos{
		windowDimensions[0] / 2.0 - 4.0 * (0.5 * knight.width / 6.0),
		windowDimensions[1] / 2.0 - 4.0 * (0.5 * knight.height)
	};
	float rightLeft{ 1 };
	float runningTime{};
	int frame{};
	const int maxFrames{ 6 };
	const float updateTime(1.f / 12.f);

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 direction{};
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;
		if (Vector2Length(direction) != 0) {
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
			direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
			knight = knight_run;
		}
		else {
			knight = knight_idle;
		}

		DrawTextureEx(map, mapPos, 0, 4, WHITE);

		runningTime += GetFrameTime();

		if (runningTime >= updateTime) {
			frame++;
			runningTime = 0.f;
			if (frame > maxFrames) frame = 0;
		}

		Rectangle knightSource{ frame * knight.width / 6.0f,0, rightLeft * knight.width / 6.0f, knight.height };
		Rectangle knightDest{ knightPos.x, knightPos.y, 4.0f * knight.width / 6.0f, 4.0f * knight.height };
		DrawTexturePro(knight, knightSource, knightDest, {}, 0, WHITE);

		EndDrawing();
	}
	UnloadTexture(map);
	CloseWindow();
	return 0;
}