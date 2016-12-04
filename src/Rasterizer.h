#pragma once
#pragma warning(disable : 4201)

#include <glm\glm.hpp>
#include "Fragment.h"
#include <vector>

class Rasterizer
{
public:
	//scan from ab edge to cd edge
	static std::vector<Fragment>* processScanLine(int scanLineY, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 color);

private:
	Rasterizer();
};

