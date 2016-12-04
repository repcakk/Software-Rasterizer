#include <stdio.h>
#include "WindowManager.h"
#include "Renderer.h"
#include <glm/gtx/transform.hpp>

int main(int, char**)
{
	WindowManager *windowManager = new WindowManager(800, 600);
	Camera *camera = new Camera(glm::vec3(-20, 0, 0), glm::vec3(0, 0, 0));
	Mesh *mesh = new Mesh();
	mesh->vertices->push_back(new glm::vec3(0, 6, 0));
	mesh->vertices->push_back(new glm::vec3(4, 2, 0));
	mesh->vertices->push_back(new glm::vec3(1, 1, 0));
	mesh->faces->push_back(new Face(0, 1, 2));

	mesh->modelMatrix = glm::mat4(1.0f);

	glm::vec3 rotationAxis = glm::vec3(0, 1, 0);

	float rot = 1.0f;

	// Main loop
	bool quit = false;
	while (!quit)
	{
		rot += 0.00001;

		Renderer::render(camera, mesh, windowManager);

	}
	system("pause");
	return 0;
}
