#pragma once

#include <vector>
#include "../VecTemplate.h"
#include "../Graphics.h"
#include <memory>

class Entity
{
public:
	int static calculateOrientation(VecInt& lineAPoint1, VecInt& lineAPoint2, VecInt& lineBPoint1);
	bool static isTwoLineColliding(VecInt& lineAPoint1 , VecInt& lineAPoint2, VecInt& lineBPoint1, VecInt& lineBPoint2);
	void static isPolyLineColliding(Entity& aObject, Entity& bObject, std::unique_ptr<std::vector<VecInt>> & collisionVector);
	Entity(std::vector<VecFloat>& shape, VecInt& center, VecInt& velocity, float rotation, float scale);
	Entity(std::vector<VecFloat>& shape, VecInt& center, VecInt& velocity, float rotation) :Entity(shape, center, velocity, rotation, 1) {};
	Entity(std::vector<VecFloat>& shape, VecInt& center, VecInt& velocity) :Entity(shape, center, velocity, 0) {}
	Entity(std::vector<VecFloat>& shape, VecInt& center) : Entity(shape, center, VecInt(0,0)) {}
	void draw(Graphics& gfx);
	void addRotation(float rotationDegree);
	void addTransformion(VecDouble transformation);
	void addScale(float scale);
	void addVelocity(const int velocityX, const int velocityY);
	void setVelocity(const double velocityX, const double velocityY);
	void reset(VecDouble& center,VecDouble& velocity);
	void update(float deltaTime);
	bool getIsOutOfScreen();
	const VecDouble & getVelocity() const;
	Entity& operator=(Entity& rhs);
	void setTransform(VecDouble center);
	void setColissionCooldown(int cooldown);
	int getCollisionCooldown();
private:
	bool const isPointOutOfScreen(VecInt & point);
	std::vector<VecFloat> & originalShape;
	VecDouble transformValue;
	float scaleValue;
	float rotationValue;
	std::vector<VecInt> transformAppliedShape;
	VecDouble velocity;
	bool isOutOfScreen = false;
	float collisionCooldown;
};

