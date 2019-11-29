/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "random_generator/RandomGenerator.h"
#include "entity/Entity.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	for (int i = 0; i < NUM_OF_ENTITIES; i++) {
		pendingEntities.emplace_back(Entity(circlePolyLine, VecInt(0, 0), VecInt(0, 0)));
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed('A')) {
		stick.addRotation(-0.01);
	}
	else if (wnd.kbd.KeyIsPressed('D'))
	{
		stick.addRotation(0.01);
	}
	stick.update(1);
	if(activeEntities.size()==0 && pendingEntities.size()!=0){
		auto& newActiveEntity = pendingEntities.at(0);
		pendingEntities.erase(pendingEntities.begin() + 0);
		auto center = RandomGenerator::getInstance()->generateVecIntWithSeperateRangeValue(
			600,
			500,
			800,
			600
		);
		auto velocity = RandomGenerator::getInstance()->generateVecIntWithSeperateRangeValue(
			-4,
			-4,
			-2,
			-2
		);
		newActiveEntity.reset(VecDouble(center), VecDouble(velocity));
		activeEntities.emplace_back(newActiveEntity);
	}
	for (int i = activeEntities.size() - 1; i >= 0; i--) {
		if (activeEntities[i].getIsOutOfScreen()) {
			const auto& newPendingEntity = activeEntities.at(i);
			activeEntities.erase(activeEntities.begin() + i);
			pendingEntities.emplace_back(newPendingEntity);
			continue;
		}
		if (activeEntities[i].getCollisionCooldown() <=0) {
			collisionVector->erase(collisionVector->begin(), collisionVector->end());
			Entity::isPolyLineColliding(stick, activeEntities[i], collisionVector);
			if (collisionVector->size() > 0) {
				activeEntities[i].setColissionCooldown(100);
				VecDouble colidedVector = VecDouble(collisionVector->at(0) - collisionVector->at(1));
				VecDouble colidedVectorHat = colidedVector.hat();
				VecDouble activeEntityVector = VecDouble(activeEntities[i].getVelocity());
				VecDouble activeEntityHat = activeEntityVector.hat();
				VecDouble newVelocity =  colidedVectorHat * 2 * (activeEntityVector * colidedVectorHat) - activeEntityVector;
				activeEntities[i].setVelocity(newVelocity.getX(), newVelocity.getY());
			}
		}
	}
	for (int i = activeEntities.size() - 1; i >= 0; i--) {
		//TODO Use frame timer instead
		activeEntities.at(i).update(1);
	}
}

void Game::ComposeFrame()   
{
	for (int i = 0; i < activeEntities.size(); i++) {
		activeEntities.at(i).draw(gfx);
	}
	stick.draw(gfx);
}
