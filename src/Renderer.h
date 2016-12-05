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
#include "WindowManager.h"
#include "Utils.h"

class Renderer
{
public:
	static void drawTriangle(Vertex *vtx0, Vertex *vtx1, Vertex *vtx2, WindowManager *windowManager);
	//scan from ab edge to cd edge
	static void processScanLine(int scanLineY, Vertex *a, Vertex *b, Vertex *c, Vertex *d, WindowManager *windowManager);
	static glm::vec4 project(glm::vec4 vertex, glm::mat4 mvpMatrix);

	static void render(Camera *camera, Mesh *mesh, WindowManager *windowManager);

private:
	Renderer();
};

