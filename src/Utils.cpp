#include "Utils.h"

template <class T>
T Utils::FastMax(const T& left, const T& right)
{
	return left > right ? left : right;
}

template <class T>
T Utils::FastMin(const T& left, const T& right)
{
	return left < right ? left : right;
}

float Utils::clamp(float value, float min, float max)
{
	return Utils::FastMax(min, Utils::FastMin(value, max));
}

float Utils::calcGradient(float a, float b, float position)
{
	return a != b ? (position - a) / (b - a) : 1;
}

float Utils::interpolate(float min, float max, float gradient)
{
	float clampGrad = Utils::clamp(gradient);
	return min + (max - min) * Utils::clamp(gradient);
}
