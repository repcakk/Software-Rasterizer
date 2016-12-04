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
		x += this->windowSurface->w/2;
		y += this->windowSurface->h/2;

		((unsigned int*)windowSurface->pixels)[y * this->windowSurface->w + x] = SDL_MapRGB(windowSurface->format, color.x, color.y, color.z);
		SDL_UnlockSurface(windowSurface);
	}

}

void WindowManager::clearScreen(glm::vec3 color)
{	
	SDL_Rect rect = { 0, 0, this->windowSurface->w, this->windowSurface->h };

	SDL_FillRect(this->windowSurface, &rect, SDL_MapRGB(windowSurface->format, color.x, color.y, color.z));
}
