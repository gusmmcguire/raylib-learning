#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex) : worldPos(pos), texture(idle_tex), idle(idle_tex), run(run_tex){
	width = texture.width / maxFrames;
	height = texture.height;
}

void Enemy::tick(float deltaTime) {
	worldPosLastFrame = worldPos;

	runningTime += deltaTime;

	if (runningTime >= updateTime) {
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames) frame = 0;
	}

	Rectangle source{ frame * width , 0, rightLeft * width, height };
	Rectangle dest{ screenPos.x, screenPos.y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, {}, 0, WHITE);
}

void Enemy::undoMovement() {
	worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec() {
	return Rectangle{ screenPos.x, screenPos.y, width * scale, height * scale };
}
