#include "Rasterizer.h"
#include "Utils.h"


std::vector<Fragment*>* Rasterizer::processScanLine(int scanLineY, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 color)
{
	float grad0 = Utils::calcGradient(a.y, b.y, scanLineY);
	float grad1 = Utils::calcGradient(c.y, d.y, scanLineY);

	//calucate sx and ex - start and the end of the scan line
	float sx = Utils::interpolate(a.x, b.x, grad0);
	float ex = Utils::interpolate(c.x, d.x, grad1);

	std::vector<Fragment*> *fragments = new std::vector<Fragment*>;
	
	for (unsigned int x = sx; x < ex; ++x)
	{
		fragments->push_back(new Fragment(glm::vec3(x, scanLineY, 0), glm::vec3(1, 2, 3)));
	}

	return fragments;
}


