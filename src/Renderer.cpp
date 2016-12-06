#include "Renderer.h"
#include <algorithm>
#include <vector>
#include <glm/gtx/transform.hpp>

void Renderer::processScanLine(int scanLineY, Vertex *a, Vertex *b, Vertex *c, Vertex *d, WindowManager *windowManager)
{
	float grad0 = Utils::calcGradient(a->position.y, b->position.y, scanLineY);
	float grad1 = Utils::calcGradient(c->position.y, d->position.y, scanLineY);

	//calucate sx and ex - start and the end of the scan line
	float sx = Utils::interpolate(a->position.x, b->position.x, grad0);
	float ex = Utils::interpolate(c->position.x, d->position.x, grad1);

	float r0 = Utils::interpolate(a->color.r, b->color.r, grad0);
	float g0 = Utils::interpolate(a->color.g, b->color.g, grad0);
	float b0 = Utils::interpolate(a->color.b, b->color.b, grad0);

	float r1 = Utils::interpolate(c->color.r, d->color.r, grad0);
	float g1 = Utils::interpolate(c->color.g, d->color.g, grad0);
	float b1 = Utils::interpolate(c->color.b, d->color.b, grad0);

	float z0 = Utils::interpolate(a->position.z, b->position.z, grad0);
	float z1 = Utils::interpolate(c->position.z, d->position.z, grad1);

	for (int x = sx; x < ex; ++x)
	{
		float colorGrad = Utils::calcGradient(sx, ex, x);

		float finalR = Utils::interpolate(r0, r1, colorGrad);
		float finalG = Utils::interpolate(g0, g1, colorGrad);
		float finalB = Utils::interpolate(b0, b1, colorGrad);

		float zGrad = Utils::calcGradient(sx, ex, x);

		float z = Utils::interpolate(z0, z1, zGrad);


		windowManager->updateFramebuffer(x + windowManager->getWindowWidth()/2, scanLineY + windowManager->getWindowHeight()/2, z, glm::vec3(finalR, finalG, finalB));
	}
}


void Renderer::drawTriangle(Vertex *vtx0, Vertex *vtx1, Vertex *vtx2, WindowManager *windowManager)
{
	if (vtx0->position.y > vtx1->position.y)
	{
		std::swap(vtx0, vtx1);
	}

	if (vtx1->position.y > vtx2->position.y)
	{
		std::swap(vtx1, vtx2);
	}

	if (vtx0->position.y > vtx1->position.y)
	{
		std::swap(vtx0, vtx1);
	}

	float invSlope0 = 0, invSlope1 = 0;
	
	bool right = false, left = false;

	if (vtx1->position.y - vtx0->position.y > 0)
	{
		invSlope0 = (vtx1->position.x - vtx0->position.x) / (vtx1->position.y - vtx0->position.y);
	}
	else if (vtx1->position.x > vtx0->position.x)
	{
		right = true;
	}
	else
	{
		left = true;
	}

	if (vtx2->position.y - vtx0->position.y > 0)
	{
		invSlope1 = (vtx2->position.x - vtx0->position.x) / (vtx2->position.y - vtx0->position.y);
	}
	else if (vtx2->position.x > vtx0->position.x)
	{
		right = true;
	}
	else
	{
		left = true;
	}

	if (right || (!left && invSlope0 > invSlope1))
	{
		for (int y = vtx0->position.y; y <= vtx2->position.y; ++y)
		{
			if (y < vtx1->position.y)
			{
				Renderer::processScanLine(y, vtx0, vtx2, vtx0, vtx1, windowManager);
			}
			else
			{
				Renderer::processScanLine(y, vtx0, vtx2, vtx1, vtx2, windowManager);
			}
		}
	}
	else
	{
		for (int y = vtx0->position.y; y <= vtx2->position.y; ++y)
		{
			if (y < vtx1->position.y)
			{
				Renderer::processScanLine(y, vtx0, vtx1, vtx0, vtx2, windowManager);
			}
			else
			{
				Renderer::processScanLine(y, vtx1, vtx2, vtx0, vtx2, windowManager);
			}
		}
	}

}

void Renderer::render(Camera *camera, Mesh *mesh, WindowManager *windowManager)
{
	windowManager->clearScreen(glm::vec3(0, 0, 0));

	glm::mat4 viewMatrix = glm::lookAt(camera->position, camera->target, glm::vec3(0, -1, 0));
	glm::mat4 projectionMatrix = glm::perspective(30.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * mesh->modelMatrix;
	
	for (int faceIdx = 0; faceIdx < mesh->faces.size(); ++faceIdx)
	{
		Vertex *vtx0 = new Vertex(mvpMatrix * glm::vec4((mesh->vertices)[(mesh->faces)[faceIdx].a].position), (mesh->vertices)[(mesh->faces)[faceIdx].a].color);
		Vertex *vtx1 = new Vertex(mvpMatrix * glm::vec4((mesh->vertices)[(mesh->faces)[faceIdx].b].position), (mesh->vertices)[(mesh->faces)[faceIdx].b].color);
		Vertex *vtx2 = new Vertex(mvpMatrix * glm::vec4((mesh->vertices)[(mesh->faces)[faceIdx].c].position), (mesh->vertices)[(mesh->faces)[faceIdx].c].color);
		
		Renderer::drawTriangle(vtx0, vtx1, vtx2, windowManager);
		
		delete(vtx0);
		delete(vtx1);
		delete(vtx2);
	}
	windowManager->updateWindowSurface();
}
