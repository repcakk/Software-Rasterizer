#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target);
	~Camera();

	glm::vec3 position;
	glm::vec3 target;
};

