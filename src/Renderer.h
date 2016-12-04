#pragma once
#pragma warning(disable : 4201)

#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <glm\glm.hpp>
#include "Camera.h"
#include "Mesh.h"
#include "Fragment.h"
#include "WindowManager.h"

class Renderer
{
public:
	static void drawTriangle(glm::vec3 vtx0, glm::vec3 vtx1, glm::vec3 vtx2, glm::vec3 color, WindowManager *windowManager);
	static void drawFragment(Fragment *fragment);
	static glm::vec4 project(glm::vec4 vertex, glm::mat4 mvpMatrix);

	static void render(Camera *camera, Mesh *mesh, WindowManager *windowManager);

private:
	Renderer();
};

