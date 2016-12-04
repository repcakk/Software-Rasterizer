#include "WindowManager.h"
#include <stdio.h>


WindowManager::WindowManager(unsigned int xRes, unsigned int yRes)
{
	this->window = SDL_CreateWindow(
		"Software Rasterizer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		xRes, yRes,
		0);

	this->windowSurface = SDL_GetWindowSurface(this->window);
}

WindowManager::~WindowManager()
{
}

void WindowManager::updateWindowSurface()
{
	SDL_UpdateWindowSurface(window);
}

void WindowManager::updateFramebuffer(unsigned int x, unsigned int y, glm::vec3 color)
{
	if (!SDL_LockSurface(windowSurface))
	{
		((unsigned int*)windowSurface->pixels)[y * this->windowSurface->w + x] = SDL_MapRGB(windowSurface->format, color.x, color.y, color.z);
		SDL_UnlockSurface(windowSurface);
	}

}
