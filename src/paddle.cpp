#include "headers/paddle.hpp"
#include "headers/main.hpp"
#include <SDL3/SDL_render.h>
#include <iostream>

Paddle::Paddle(int x, int y, int mSpeed) {
	rect.x = x;
	rect.y = y;
	rect.h = 150;
	rect.w = 10;
	speed = mSpeed;
}

void Paddle::Update(bool moveUp, bool moveDown) {
	if (moveUp && rect.y > 0) {
		rect.y = rect.y-speed;
	}
	if (moveDown && rect.y < HEIGHT-150) {
		rect.y = rect.y+speed;
	}
}

void Paddle::Render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect* Paddle::GetRect()  {
	return &this->rect;
}
