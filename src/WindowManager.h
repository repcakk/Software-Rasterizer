#pragma once

#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif

#include <glm/glm.hpp>


class WindowManager
{
public:
	WindowManager(unsigned int xRes, unsigned int yRes);
	~WindowManager();

	void updateWindowSurface();
	void updateFramebuffer(int x, int y, float z, glm::vec3 color);
	void clearScreen(glm::vec3 color);

	int getWindowWidth();
	int getWindowHeight();

private:
	SDL_Window *window;
	SDL_Surface* windowSurface;
	float *depthBuffer;
};

