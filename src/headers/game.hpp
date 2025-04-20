#ifndef GAME
#define GAME

#include "ball.hpp"
#include "paddle.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
class Game {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		bool isRunning;

		Paddle *leftPaddle, *rightPaddle;
		Ball *ball;

		bool wPressed, sPressed, upPressed, downPressed;
	
	public:
		Game();
		~Game();
		bool Init();
		void Run();
		void HandleEvents();
		void Update();
		void Render();
		void Clean();
};

#endif
