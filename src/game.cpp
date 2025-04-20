
#include "headers/game.hpp"
#include "headers/ball.hpp"
#include "headers/main.hpp"
#include "headers/paddle.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	isRunning = wPressed = sPressed = upPressed = downPressed = false;
	leftPaddle = new Paddle(0,50,10);
	rightPaddle = new Paddle(WIDTH-10,50,10);
	ball = new Ball(WIDTH/2, HEIGHT/2, 10, 10, 2);
}

Game::~Game() {
	Clean();
}

bool Game::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
		std::cerr << "Failed to initialize sdl" << SDL_GetError() << "\n";
		return false;
	}

	window = SDL_CreateWindow("Pong", WIDTH, HEIGHT, 0);

	if (!window) {
		std::cerr << "Failed to initialize window" << SDL_GetError() << "\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		std::cerr << "Failed to initialize renderer" << SDL_GetError() << "\n";
		return false;
	}

	isRunning = true;
	return true;
}

void Game::Run() {
	while(isRunning) {
		HandleEvents();
		Update();
		Render();
		SDL_Delay(16);
	}
}

void Game::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_W) wPressed = true;
				if (event.key.key == SDLK_S) sPressed = true;
				if (event.key.key == SDLK_UP) upPressed = true;
				if (event.key.key == SDLK_DOWN) downPressed = true;
				break;
			case SDL_EVENT_KEY_UP:
				if (event.key.key == SDLK_W) wPressed = false;
				if (event.key.key == SDLK_S) sPressed = false;
				if (event.key.key == SDLK_UP) upPressed = false;
				if (event.key.key == SDLK_DOWN) downPressed = false;
				break;
			default:
				break;
		}
	}
}

void Game::Update() {
	leftPaddle->Update(wPressed, sPressed);
	rightPaddle->Update(upPressed, downPressed);
	ball->Update();
	if(ball->CheckCollisions(leftPaddle->GetRect())) {
		ball->BounceOffPaddle(leftPaddle->GetRect(), false);
	}
	if (ball->CheckCollisions(rightPaddle->GetRect())) {
		ball->BounceOffPaddle(rightPaddle->GetRect(), true);
	}
	if (ball->CheckWallCollision()) {
		ball->BounceOffWall();
	}
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	leftPaddle->Render(renderer);
	rightPaddle->Render(renderer);
	ball->Render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}

	if (window) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}
