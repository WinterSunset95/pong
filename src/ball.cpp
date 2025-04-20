#include "headers/ball.hpp"
#include "headers/main.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <cmath>
#include <iostream>

Ball::Ball(int x, int y, int w, int h, float bSpeed) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	speed = bSpeed;
	dx = std::cos(0 * (M_PI/180)) * speed;
	dy = (std::sin(0 * (M_PI/180)) * speed);
	std::cout << "dx: " << dx << ",dy: " << dy << "\n";
}

bool Ball::CheckCollisions(SDL_FRect *otherRect) {
	return SDL_HasRectIntersectionFloat(&rect, otherRect);
}

void Ball::BounceOffPaddle(SDL_FRect *paddRect, bool fromLeft) {
	speed = speed + 0.1;
	float ballCenter = rect.y + rect.h / 2.0;
	float paddleCenter = paddRect->y + paddRect->h / 2.0;
	float distance = ballCenter - paddleCenter;
	float normalized = distance / (paddRect->h/2.0);
	float bounceAngle = fromLeft ? (normalized * 75) + 180 : -(normalized * 75);
	std::cout << bounceAngle << "\n";
	dx = std::cos(bounceAngle * (M_PI/180)) * speed;
	dy = std::sin(bounceAngle * (M_PI/180)) * speed;
}

bool Ball::CheckWallCollision() {
	if (rect.y <= 0 || rect.y >= HEIGHT-rect.h) {
		return true;
	}
	return false;
}

void Ball::BounceOffWall() {
	dy = -dy;
}

void Ball::Update() {
	rect.x = rect.x + (dx * speed);
	rect.y = rect.y - (dy * speed);
}

void Ball::Render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
	SDL_RenderFillRect(renderer, &rect);
}
