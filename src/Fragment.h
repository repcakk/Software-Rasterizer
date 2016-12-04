#pragma once
#pragma warning(disable : 4201)

#include <glm\glm.hpp>

class Fragment
{
public:
	Fragment(glm::vec3 position, glm::vec3 color);
	~Fragment();

	const glm::vec3 position;
	const glm::vec3 color;
};

