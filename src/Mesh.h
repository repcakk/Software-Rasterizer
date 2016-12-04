#pragma once
#pragma warning(disable : 4201)

#include <glm\glm.hpp>
#include <vector>

class Face
{
public:
	Face(unsigned int a, unsigned int b, unsigned int c);

	const unsigned int a;
	const unsigned int b;
	const unsigned int c;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	glm::mat4 modelMatrix;
	std::vector<glm::vec3*> *vertices;
	std::vector<Face*> *faces;
};

