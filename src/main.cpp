#include <stdio.h>
#include "WindowManager.h"
#include "Renderer.h"
#include <glm/gtx/transform.hpp>

int main(int, char**)
{
	WindowManager *windowManager = new WindowManager(800, 600);
	Camera *camera = new Camera(glm::vec3(-25, 0, 15), glm::vec3(0, 0, 0));
	Mesh *mesh = new Mesh();
	
	//face vertices layout
	//	B		C
	//
	//
	//	A		D
	mesh->vertices.push_back(Vertex(glm::vec4(0, 0, 0, 0), glm::vec3(255, 0, 0)));			//A, 0
	mesh->vertices.push_back(Vertex(glm::vec4(0, 100, 0, 0), glm::vec3(0, 255, 0)));		//B, 1
	mesh->vertices.push_back(Vertex(glm::vec4(100, 100, 0, 0), glm::vec3(0, 0, 255)));		//C, 2
	mesh->vertices.push_back(Vertex(glm::vec4(100, 0, 0, 0), glm::vec3(0, 255, 255)));		//D, 3

	mesh->vertices.push_back(Vertex(glm::vec4(0, 0, -100, 0), glm::vec3(255, 255, 0)));	//A', 4
	mesh->vertices.push_back(Vertex(glm::vec4(0, 100, -100, 0), glm::vec3(0, 0, 255)));	//B', 5
	mesh->vertices.push_back(Vertex(glm::vec4(100, 100, -100, 0), glm::vec3(0, 255, 0)));	//C', 6
	mesh->vertices.push_back(Vertex(glm::vec4(100, 0, -100, 0), glm::vec3(255, 0, 0)));	//D', 7

	mesh->faces.push_back(Face(0, 1, 2));
	mesh->faces.push_back(Face(2, 3, 0));

	mesh->faces.push_back(Face(4, 5, 6));
	mesh->faces.push_back(Face(6, 7, 4));

	mesh->faces.push_back(Face(1, 5, 6));
	mesh->faces.push_back(Face(6, 2, 1));
	
	mesh->faces.push_back(Face(0, 4, 7));
	mesh->faces.push_back(Face(7, 3, 0));

	mesh->modelMatrix = glm::mat4(1.0f);

	glm::vec3 rotationAxis = glm::vec3(1, 0, 0);

	float rot = 0.001f;

	// Main loop
	bool quit = false;
	while (!quit)
	{
		mesh->modelMatrix *= glm::rotate(rot, rotationAxis);

		Renderer::render(camera, mesh, windowManager);
	}
	system("pause");
	return 0;
}
