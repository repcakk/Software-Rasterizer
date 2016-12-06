#pragma once

class Utils
{
public:
	//clamp value between min and max
	static float clamp(float value, float min = 0, float max = 1);

	//calculate position between a and b
	static float calcGradient(float a, float b, float position);

	//interpolate value between min and max with given gradient
	static float interpolate(float min, float max, float gradient);

	template <class T>
	static T FastMax(const T& left, const T& right);

	template <class T>
	static T FastMin(const T& left, const T& right);

private:
	Utils();
};

