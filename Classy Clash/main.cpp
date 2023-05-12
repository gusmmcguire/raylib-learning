#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main() {
	const int windowDimensions[]{ 768,768 };
	InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{ 0,0 };
	const float mapScale{ 8.f };

	Character knight{ windowDimensions[0], windowDimensions[1] };
	Enemy goblin{
		Vector2{1600.f, 300.f},
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png")
	};


	Enemy slime{
		Vector2{500.f, 700.f},
		LoadTexture("characters/slime_idle_spritesheet.png"),
		LoadTexture("characters/slime_run_spritesheet.png") };

	Enemy* enemies[]{
		&goblin,
		&slime };

	for (auto enemy : enemies) {
		enemy->setTarget(&knight);
	}


	Prop props[2]{
		Prop{ Vector2{1200,600}, LoadTexture("nature_tileset/Rock.png") },
		Prop{ Vector2{800,1000}, LoadTexture("nature_tileset/Log.png") },
	};

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		mapPos = Vector2Scale(knight.getWorldPos(), -1);

		DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

		//draw props
		for (Prop prop : props) {
			prop.Render(knight.getWorldPos());
		}

		knight.tick(GetFrameTime());
		//check map bounds
		if (knight.getWorldPos().x < 0.f ||
			knight.getWorldPos().y < 0.f ||
			knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
			knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale) {
			knight.undoMovement();
		}

		for (Prop prop : props) {
			if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos()))) {
				knight.undoMovement();
			}
		}

		for (Enemy* enemy : enemies) {
			enemy->tick(GetFrameTime());
		}

		if (!knight.getAlive()) {
			DrawText("Game Over!", 110.f, 90.f, 80, RED);
			EndDrawing();
			continue;
		}
		else {
			std::string knightsHealth = "Health: ";
			knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
			DrawText(knightsHealth.c_str(), 110.f, 90.f, 80, RED);
		}


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			for (Enemy* enemy : enemies)
				if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec()))
					enemy->setAlive(false);
		}

		EndDrawing();
	}
	UnloadTexture(map);
	CloseWindow();
	return 0;
}