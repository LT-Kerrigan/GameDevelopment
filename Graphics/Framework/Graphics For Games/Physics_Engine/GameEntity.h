/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	represents the connection of physics+renderer  *
************************************************************************************************/

/*
The sub systems handle the updating of the 'sub components' of a GameEntity,
so in the Update function of this class will just be the 'gameplay' specific
type functionality(has the player picked up some health / has he shot an enemy
and so forth).

The sub components of the GameEntity are accessible through 'Getter' functions,
but note that they return references, rather than the pointer type they have
been initialised to.This is to better encapsulate the data components, and to
prevent the components being deleted / new'd on top of - this should be only
allowable 'inside' the class that owns the sub components(ie 'this')

In order to 'hook' into the sub systems of the game, there are two functions to
add and remove the SceneNode / PhysicsEntity from the Renderer and PhysicsEngine.
By doing this, the GameEntity has control over when it will be processed or
visible.*/


#pragma once

#include "../../nclgl/SceneNode.h"
#include "PhysicsEntity.h"

class GameEntity	{
public:
	friend class GameClass;

	GameEntity(void);
	GameEntity(SceneNode* s, PhysicsEntity* p);
	virtual ~GameEntity(void);

	virtual void	Update(float msec);

	SceneNode&		GetRenderNode()		{ return *renderNode; }
	PhysicsEntity&	GetPhysicsNode()	{ return *physicsNode; }

	void			ConnectToSystems();
	void			DisconnectFromSystems();

protected:
	SceneNode*		renderNode;
	PhysicsEntity*	physicsNode;
};
