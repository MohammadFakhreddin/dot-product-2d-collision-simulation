#pragma once

#include <random>
#include "../VecTemplate.h"
#include <memory>

class RandomGenerator
{
private:
	std::random_device randomDevice;
	std::mt19937 randomEngine = std::mt19937(randomDevice());
	static std::unique_ptr<RandomGenerator> instance;
public:
	int generateIntRangeValue(int minimum, int maximum);
	VecInt & generateVecIntRangeValue(int minimumVectorValue, int maximumVectorValue);
	VecInt & generateVecIntWithSeperateRangeValue(
		int minimumVectorXValue,
		int minimumVectorYValue, 
		int maximumVectorXValue,
		int maximumVectorYValue
	);
	static std::unique_ptr<RandomGenerator> & getInstance();
};