#pragma once
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
public:
	Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
	virtual void tick(float deltaTime) override;
	void setTarget(Character* tar) { target = tar; }
	virtual Vector2 getScreenPos() override;
private:
	Character* target{};
	float damagePerSec{ 10.f };
	float radius{ 2.5f };
};