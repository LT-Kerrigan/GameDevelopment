#include "GameEntity.h"
#include "Renderer.h"
#include "PhysicsEngine.h"

GameEntity::GameEntity(void)	{
	renderNode = NULL;
	physicsNode = NULL;
}

GameEntity::GameEntity(SceneNode* s, PhysicsEntity* p) {
	renderNode = s;
	physicsNode = p;
}

GameEntity::~GameEntity(void)	{
	DisconnectFromSystems();

	delete renderNode;
	delete physicsNode;
}

void	GameEntity::Update(float msec) {

}

void	GameEntity::ConnectToSystems() {
	if (renderNode) {
		Renderer::GetRenderer().AddNode(renderNode);
	}

	if (physicsNode) {
		PhysicsEngine::GetPhysicsSystem().AddNode(physicsNode);
	}

	if (renderNode && physicsNode) {
		physicsNode->SetTarget(renderNode);
	}
}

void	GameEntity::DisconnectFromSystems() {
	if (renderNode) {
		Renderer::GetRenderer().RemoveNode(renderNode);
	}

	if (physicsNode) {
		PhysicsEngine::GetPhysicsSystem().RemoveNode(physicsNode);
	}
}