#ifndef BALL
#define BALL

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
class Ball {
	private:
		SDL_FRect rect;
		float dx, dy;
		float speed;

	public:
		Ball(int x, int y, int w, int h, float speed);
		void Update();
		void Render(SDL_Renderer *renderer);
		// Will return the angle of deviation
		bool CheckCollisions(SDL_FRect *rect);
		void BounceOffPaddle(SDL_FRect *rect, bool fromLeft);
		bool CheckWallCollision();
		void BounceOffWall();
};

#endif
