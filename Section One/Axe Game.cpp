#include <iostream>
#include "raylib.h"

int main() {

	//window dimensions
	int windowWidth = 800;
	int windowHeight = 450;

	InitWindow(windowWidth, windowHeight, "Axe Game");

	//circle coordinates
	int circle_x = windowWidth / 2;
	int circle_y = windowHeight / 2;
	int circle_radius = 25;
	//circle edges
	int l_circle_x = circle_x - circle_radius;
	int r_circle_x = circle_x + circle_radius;
	int u_circle_y = circle_y - circle_radius;
	int b_circle_y = circle_y + circle_radius;


	//axe coordinates
	int axe_x = 300;
	int axe_y = 0;
	int axe_length = 50;
	int axe_width = 50;
	//axe edges
	int l_axe_x = axe_x;
	int r_axe_x = axe_x + axe_width;
	int u_axe_y = axe_y;
	int b_axe_y = axe_y + axe_length;

	int axeDirection = 10;

	bool collision_with_axe = 
							b_axe_y >= u_circle_y && 
							u_axe_y <= b_circle_y && 
							l_axe_x <= r_circle_x && 
							r_axe_x >= l_circle_x;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(WHITE);

		if (collision_with_axe) {
			DrawText("Game Over!", windowWidth / 2, windowHeight / 2, 20, RED);
		}
		else {

			//Game logic begins
			
			//collider update
			l_circle_x = circle_x - circle_radius;
			r_circle_x = circle_x + circle_radius;
			u_circle_y = circle_y - circle_radius;
			b_circle_y = circle_y + circle_radius;

			l_axe_x = axe_x;
			r_axe_x = axe_x + axe_width;
			u_axe_y = axe_y;
			b_axe_y = axe_y + axe_length;

			//draw circle and axe
			DrawCircle(circle_x, circle_y, circle_radius, BLUE);
			DrawRectangle(axe_x, axe_y, axe_width, axe_length, RED);

			//move axe
			if (axe_y > windowHeight || axe_y < 0) 	axeDirection = -axeDirection;
			axe_y += axeDirection;

			//move circle
			if (IsKeyDown(KEY_D) && circle_x < windowWidth) circle_x += 10;
			if (IsKeyDown(KEY_A) && circle_x > 0) circle_x -= 10;

			//collision detection
			collision_with_axe = b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x;

			//Game logic ends
		}
		EndDrawing();

	}

	return 0;
}