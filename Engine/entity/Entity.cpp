#pragma once

#include <math.h>
#include "Entity.h"
#include "../VecTemplate.h"
#include <algorithm>


int Entity::calculateOrientation(VecInt& lineAPoint1, VecInt& lineAPoint2, VecInt& lineBPoint1)
{
	const float diffrence = (lineAPoint2.getY() - lineAPoint1.getY()) * (lineBPoint1.getX() - lineAPoint2.getX()) 
		- (lineAPoint2.getX() - lineAPoint1.getX()) * (lineBPoint1.getY() - lineAPoint2.getY());
	if (diffrence > 0) {
		return 2;
	}
	if (diffrence < 0) {
		return 1;
	}
	return 0;
}

bool Entity::isTwoLineColliding(VecInt& lineAPoint1, VecInt& lineAPoint2, VecInt& lineBPoint1, VecInt& lineBPoint2)
{
	const int line1O1 = Entity::calculateOrientation(lineAPoint1, lineAPoint2, lineBPoint1);
	const int line1O2 = Entity::calculateOrientation(lineAPoint1, lineAPoint2, lineBPoint2);
	const int line2O1 = Entity::calculateOrientation(lineBPoint1, lineBPoint2, lineAPoint1);
	const int line2O2 = Entity::calculateOrientation(lineBPoint1, lineBPoint2, lineAPoint2);
	if (line1O1 != 0 && line1O2 != line1O1 && line2O1 != 0 && line2O2 != line2O1) {
		return true;
	}
	//TODO Handle 0 orientation
	return false;
}

void Entity::isPolyLineColliding(
	Entity & aObject,
	Entity & bObject,
	std::unique_ptr<std::vector<VecInt>> & collisionVector
) {
	collisionVector->erase(collisionVector->begin(), collisionVector->end());
	for (size_t aObjectIndex = 0; aObjectIndex < aObject.transformAppliedShape.size() - 1; aObjectIndex++) {
		for (size_t bObjectIndex = 0; bObjectIndex < bObject.transformAppliedShape.size() - 1; bObjectIndex++) {
			if (
				Entity::isTwoLineColliding(
					aObject.transformAppliedShape.at(aObjectIndex),
					aObject.transformAppliedShape.at(aObjectIndex + 1),
					bObject.transformAppliedShape.at(bObjectIndex),
					bObject.transformAppliedShape.at(bObjectIndex + 1)
				)
			) {
				collisionVector->emplace_back(aObject.transformAppliedShape.at(aObjectIndex));
				collisionVector->emplace_back(bObject.transformAppliedShape.at(bObjectIndex));
				break;
			}
		}
	}
	return;
}

Entity::Entity(
	std::vector<VecFloat>& shape, 
	VecInt& center, 
	VecInt& velocity, 
	float rotation,
	float scale
) :
	originalShape(shape),
	transformValue(center),
	velocity(velocity),
	rotationValue(rotation),
	scaleValue(scale),
	collisionCooldown(0)
{
	for (size_t i = 0; i < originalShape.size(); i++) {
		transformAppliedShape.emplace_back(
			VecInt(
				int(originalShape.at(i).getX()),
				int(originalShape.at(i).getY())
			)
		);
	}
}

void Entity::update(float deltaTime)
{
	if (collisionCooldown > 0) {
		collisionCooldown -= deltaTime;
	}
	this->transformValue += this->velocity;
	double degree = 0;
	long x = 0;
	long y = 0;
	unsigned long xSquare = 0;
	unsigned long ySquare = 0;
	unsigned long radius = 0;
	this->isOutOfScreen = true;
	for (size_t i = 0; i < originalShape.size(); i++)
	{
		y = long(originalShape.at(i).getY());
		x = long(originalShape.at(i).getX());
		xSquare = unsigned long(x * x);
		ySquare = unsigned long(y * y);
		radius = unsigned long(sqrt(xSquare + ySquare));
		degree = atan2(
			x,
			y
		);
		degree += rotationValue;
		x = long(sin(degree) * radius);
		y = long(cos(degree) * radius);
		transformAppliedShape.at(i).setX(
			int((x * scaleValue) + transformValue.getX())
		);
		transformAppliedShape.at(i).setY(
			int((y * scaleValue) + transformValue.getY())
		);
		if (
			this->isOutOfScreen == true &&
			isPointOutOfScreen(transformAppliedShape.at(i)) == false
		) {
			this->isOutOfScreen = false;
		}
	}
}

void Entity::draw(Graphics& gfx)
{

	for (size_t i = 0; i < transformAppliedShape.size() - 1; i++) {
		gfx.DrawLine(
			transformAppliedShape.at(i).getX(),
			transformAppliedShape.at(i).getY(),
			transformAppliedShape.at(i + 1).getX(),
			transformAppliedShape.at(i + 1).getY(),
			Colors::White
		);
	}
}

void Entity::addRotation(float rotationDegree)
{ 
	rotationValue += rotationDegree;
}

void Entity::addTransformion(VecDouble transformation)
{
	transformValue+=transformation;
}

void Entity::addScale(float scale)
{
	scaleValue += scale;
}

void Entity::reset(VecDouble& center, VecDouble& velocity)
{
	this->isOutOfScreen = false;
	this->transformValue.setX(center.getX());
	this->transformValue.setY(center.getY());
	this->velocity.setX(velocity.getX());
	this->velocity.setY(velocity.getY());
}

bool Entity::getIsOutOfScreen() {
	return isOutOfScreen;
}

Entity& Entity::operator=(Entity& rhs)
{
	originalShape = rhs.originalShape;
	transformValue = rhs.transformValue;
	velocity = rhs.velocity;
	scaleValue = rhs.scaleValue;
	rotationValue = rhs.rotationValue;
	return *this;
}

void Entity::setTransform(VecDouble center)
{
	transformValue.setX(center.getX());
	transformValue.setY(center.getY());
}

void Entity::setColissionCooldown(int cooldown)
{
	collisionCooldown = cooldown;
}

int Entity::getCollisionCooldown()
{
	return collisionCooldown;
}

bool const Entity::isPointOutOfScreen(VecInt & point)
{
	if (
		point.getX() >= 0 &&
		point.getX() < Graphics::ScreenWidth &&
		point.getY() >= 0 &&
		point.getY() < Graphics::ScreenHeight
	) {
		return false;
	}
	return true;
}

void Entity::addVelocity(const int velocityX, const int velocityY) {
	velocity.setX(velocity.getX() + velocityX);
	velocity.setY(velocity.getY() + velocityY);
}

void Entity::setVelocity(const double velocityX, const double velocityY) {
	velocity.setX(velocityX);
	velocity.setY(velocityY);
}

const VecDouble & Entity::getVelocity() const {
	return velocity;
}