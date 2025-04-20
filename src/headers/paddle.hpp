#ifndef PADDLE
#define PADDLE

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
class Paddle {
	private:
		SDL_FRect rect;
		int speed;
	
	public:
		Paddle(int x, int y, int speed);
		void Update(bool moveUp, bool moveDown);
		void Render(SDL_Renderer *renderer) const;
		SDL_FRect* GetRect();
};

#endif
