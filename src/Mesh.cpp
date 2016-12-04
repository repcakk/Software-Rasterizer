#include "Mesh.h"


Face::Face(unsigned int a, unsigned int b, unsigned int c): a(a), b(b), c(c)
{
}

Mesh::Mesh()
{
	this->vertices = new std::vector<glm::vec3*>;
	this->faces = new std::vector<Face*>;
}


Mesh::~Mesh()
{
	delete(this->vertices);
	delete(this->faces);
}
