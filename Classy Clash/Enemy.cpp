#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex){
	worldPos = pos;
	texture = idle_tex;
	idle = idle_tex;
	run = run_tex;

	width = texture.width / maxFrames;
	height = texture.height;

	speed = 3.5f;
}

void Enemy::tick(float deltaTime) {
	if (!getAlive()) return;
	velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
	if (Vector2Length(velocity) < radius) velocity = {};
	BaseCharacter::tick(deltaTime);

	if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())) 
		target->takeDamage(damagePerSec * deltaTime);
}

Vector2 Enemy::getScreenPos() {
	return Vector2Subtract(worldPos, target->getWorldPos());
}
