#pragma once
#include "raylib.h"

class Enemy {
public:
	Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
	Vector2 getWorldPos() { return worldPos; }
	void tick(float deltaTime);
	void undoMovement();
	Rectangle getCollisionRec();
private:
	Texture2D texture{};
	Texture2D idle{};
	Texture2D run{};

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
	float scale{ 8.f };
};