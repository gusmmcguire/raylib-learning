#pragma once
#include "raylib.h"
class BaseCharacter {
public:
	BaseCharacter();
	virtual void tick(float deltaTime);
	Vector2 getWorldPos() { return worldPos; }
	void undoMovement();
	Rectangle getCollisionRec();
	virtual Vector2 getScreenPos() = 0;
	bool getAlive() { return alive; }
	void setAlive(bool isAlive) { alive = isAlive; }
protected:
	Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D idle{ texture };
	Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

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

	Vector2 velocity{};
private:
	bool alive{ true };
};