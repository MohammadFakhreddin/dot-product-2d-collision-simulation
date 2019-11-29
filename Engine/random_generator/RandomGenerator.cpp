#pragma once

#include "RandomGenerator.h"

std::unique_ptr<RandomGenerator> & RandomGenerator::getInstance() {
	if (instance == nullptr) {
		instance = std::unique_ptr<RandomGenerator>();
	}
	return instance;
}

std::unique_ptr<RandomGenerator> RandomGenerator::instance = nullptr;


int RandomGenerator::generateIntRangeValue(int minimum, int maximum) {
	std::random_device randomDevice;
	std::mt19937 randomEngine = std::mt19937(randomDevice());
	std::uniform_int_distribution<int> distribution(minimum, maximum);
	int number = distribution(randomEngine);
	return number;
}

VecInt & RandomGenerator::generateVecIntRangeValue(int minimumVectorValue, int maximumVectorValue) {
	int xValue = generateIntRangeValue(minimumVectorValue, maximumVectorValue);
	int doubleXValue = xValue * xValue;
	int yValue = generateIntRangeValue(
		int(sqrt(minimumVectorValue * minimumVectorValue - doubleXValue)),
		int(sqrt(maximumVectorValue * maximumVectorValue - doubleXValue))
	);
	return VecInt(xValue, yValue);
}

VecInt & RandomGenerator::generateVecIntWithSeperateRangeValue(int minimumVectorXValue, int minimumVectorYValue, int maximumVectorXValue, int maximumVectorYValue)
{
	int xValue = generateIntRangeValue(minimumVectorXValue, maximumVectorXValue);
	int yValue = generateIntRangeValue(minimumVectorYValue, maximumVectorYValue);
	auto vector = VecInt(xValue, yValue);
	return vector;
}
