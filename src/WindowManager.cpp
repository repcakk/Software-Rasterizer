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
	this->depthBuffer = (float*)malloc(sizeof(float) * xRes * yRes);

	for (int depthIdx = 0; depthIdx < xRes * yRes; ++depthIdx)
	{
		this->depthBuffer[depthIdx] = 1000.0f;
	}
}

WindowManager::~WindowManager()
{
}

void WindowManager::updateWindowSurface()
{
	SDL_UpdateWindowSurface(window);
}

void WindowManager::updateFramebuffer(int x, int y, float z, glm::vec3 color)
{
	float depthValue = this->depthBuffer[y * this->windowSurface->w + x];

	if (z < depthValue)
	{
		if (!SDL_LockSurface(windowSurface))
		{
			this->depthBuffer[y * this->windowSurface->w + x] = z;

			((unsigned int*)windowSurface->pixels)[y * this->windowSurface->w + x] = SDL_MapRGB(windowSurface->format, color.x, color.y, color.z);
			SDL_UnlockSurface(windowSurface);
		}
	}
}

void WindowManager::clearScreen(glm::vec3 color)
{	
	for (int depthIdx = 0; depthIdx < this->windowSurface->w * this->windowSurface->h; ++depthIdx)
	{
		this->depthBuffer[depthIdx] = 1000.0f;
	}

	SDL_Rect rect = { 0, 0, this->windowSurface->w, this->windowSurface->h };

	SDL_FillRect(this->windowSurface, &rect, SDL_MapRGB(windowSurface->format, color.x, color.y, color.z));
}

int WindowManager::getWindowWidth()
{
	return this->windowSurface->w;
}

int WindowManager::getWindowHeight()
{
	return this->windowSurface->h;
}
