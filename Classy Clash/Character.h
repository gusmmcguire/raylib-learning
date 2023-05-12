#pragma once
#include "raylib.h"

class Character {
public:
	Character(const int& winWidth, const int& winHeight);
	Vector2 getWorldPos() { return worldPos; }
	void tick(float deltaTime);
	void undoMovement();
	Rectangle getCollisionRec();
private:
	Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D idle{ texture };
	Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

	Vector2 screenPos{};
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{};

	float rightLeft{ 1 };
	float runningTime{};
	int frame{};
	int maxFrames{ 6 };
	float updateTime{ 1.f / 12.f };

	float speed{ 8.f };
	float width{};
	float height{};
	float scale{ 8.f};
};