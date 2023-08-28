#include <SDL.h>
#include <numeric>
#include <complex>
#include <cmath>
#include <iostream>



int isInSet(std::complex<double> c)
{
	std::complex<double> z(0, 0);
	for (int i = 0; i < 256; i++)
	{
		z = std::pow(z, 2) + c;
		if (std::norm(z) > 10)
		{
			return i;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(2000, 2000, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 2, 2);

	for (double x = 0.0; x < 1.0; x += 0.0005)
		for (double y = 0.0; y < 1.0; y += 0.0005)
		{
			double pointX = std::lerp(-2.0, 2.0, x);
			double pointY = std::lerp(-2.0, 2.0, y);
			int iters = isInSet(std::complex<double>(pointX, pointY));
			if (iters == 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 3 * iters % 255, 3 * iters % 255, 3 * iters % 255, 255);
				//SDL_SetRenderDrawColor(renderer, (int)(x * 1000) * iters % 255, (int)(y * 1000) * iters % 255, (int)(x * 1000) * iters % 255, 255);
				SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
			}
			std::cout << x << std::endl;
		}

	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
			{
				quit = true;
			}
		}
	}

	return 0;
}