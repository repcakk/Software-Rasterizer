#pragma once
#pragma warning(disable : 4201)

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target);
	~Camera();

	glm::vec3 position;
	glm::vec3 target;
};

