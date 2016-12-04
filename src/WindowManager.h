#pragma once

#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif

#pragma warning(disable : 4201)

#include <glm/glm.hpp>


class WindowManager
{
public:
	WindowManager(unsigned int xRes, unsigned int yRes);
	~WindowManager();

	void updateWindowSurface();
	void updateFramebuffer(unsigned int x, unsigned int y, glm::vec3 color);

private:
	SDL_Window *window;
	SDL_Surface* windowSurface;
};

