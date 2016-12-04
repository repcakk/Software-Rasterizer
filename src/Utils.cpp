#include "Utils.h"
#include <algorithm>

float Utils::clamp(float value, float min, float max)
{
	return std::max(min, std::max(value, max));
}

float Utils::calcGradient(float a, float b, float position)
{
	return a != b ? (position - a) / (b - a) : 1;
}

float Utils::interpolate(float min, float max, float gradient)
{
	return min + (max - min) * Utils::clamp(gradient);
}
