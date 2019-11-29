#pragma once
#include <vector>
#include "../VecTemplate.h"

class ShapeGenerator
{
public:
	std::vector<VecFloat> static star(
		float innerRadius,
		float outerRadius,
		int numberOfAngles
	);
	std::vector<VecFloat> static gear(
		const float radius,
		const int numberOfCorners
	);
	std::vector<VecFloat> static rectangle(
		const int length,
		const int width
	);
};

