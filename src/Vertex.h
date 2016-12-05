#pragma once

#pragma warning(disable : 4201)
#include <glm\glm.hpp>

class Vertex
{
public:
	Vertex(glm::vec4 position, glm::vec3 color);
	~Vertex();

	const glm::vec4 position;
	const glm::vec3 color;
};

