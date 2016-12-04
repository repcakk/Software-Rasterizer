#include "Renderer.h"
#include <algorithm>
#include "Rasterizer.h"
#include <vector>
#include <glm/gtx/transform.hpp>

void Renderer::drawTriangle(glm::vec3 vtx0, glm::vec3 vtx1, glm::vec3 vtx2, glm::vec3 color, WindowManager *windowManager)
{
	if (vtx0.y > vtx1.y)
	{
		std::swap(vtx0, vtx1);
	}

	if (vtx1.y > vtx2.y)
	{
		std::swap(vtx1, vtx2);
	}

	if (vtx0.y > vtx1.y)
	{
		std::swap(vtx0, vtx1);
	}

	float invSlope0, invSlope1;
	
	if (vtx1.y - vtx0.y > 0)
	{
		invSlope0 = (vtx1.x - vtx0.x) / (vtx1.y - vtx0.y);
	}
	else
	{
		invSlope0 = 0;
	}

	if (vtx2.y - vtx0.y > 0)
	{
		invSlope1 = (vtx2.x - vtx0.x) / (vtx2.y - vtx0.y);
	}
	else
	{
		invSlope1 = 0;
	}

	std::vector<Fragment*> *line;

	if (invSlope0 > invSlope1)
	{
		for (int y = vtx0.y; y <= vtx2.y; ++y)
		{
			if (y < vtx1.y)
			{
				line = Rasterizer::processScanLine(y, vtx0, vtx2, vtx0, vtx1, color);
			}
			else
			{
				line = Rasterizer::processScanLine(y, vtx0, vtx2, vtx1, vtx2, color);
			}

			//draw line
			for (int x = 0; x < line->size(); ++x)
			{
				windowManager->updateFramebuffer(x, y, glm::vec3(155, 0, 0));
			}
		}
	}
	else
	{
		for (int y = vtx0.y; y <= vtx2.y; ++y)
		{
			if (y < vtx1.y)
			{
				line = Rasterizer::processScanLine(y, vtx0, vtx1, vtx0, vtx2, color);
			}
			else
			{
				line = Rasterizer::processScanLine(y, vtx1, vtx2, vtx0, vtx2, color);
			}

			//draw line
			for (int x = 0; x < line->size(); ++x)
			{
				windowManager->updateFramebuffer(x, y, glm::vec3(155, 0, 0));
			}
		}
	}
}

void Renderer::drawFragment(Fragment * fragment)
{
}

glm::vec4 Renderer::project(glm::vec4 vertex, glm::mat4 mvpMatrix)
{
	return mvpMatrix * vertex;
}

void Renderer::render(Camera *camera, Mesh *mesh, WindowManager *windowManager)
{
	glm::mat4 viewMatrix = glm::lookAt(camera->position, camera->target, glm::vec3(0, -1, 0));
	glm::mat4 projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * mesh->modelMatrix;

	for (unsigned int faceIdx = 0; faceIdx < mesh->faces->size(); ++faceIdx)
	{

		//glm::vec4 vtx0 = mvpMatrix * glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->a], 0);
		//glm::vec4 vtx1 = mvpMatrix * glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->b], 0);
		//glm::vec4 vtx2 = mvpMatrix * glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->c], 0);

		glm::vec4 vtx0 = glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->a], 0);
		glm::vec4 vtx1 = glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->b], 0);
		glm::vec4 vtx2 = glm::vec4(*(*mesh->vertices)[(*mesh->faces)[faceIdx]->c], 0);

		Renderer::drawTriangle(vtx0, vtx1, vtx2, glm::vec3(155, 0, 0), windowManager);
	}

	windowManager->updateWindowSurface();
}
