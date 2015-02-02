#include "PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::instance = 0;

PhysicsEngine::PhysicsSystem(void)	{

}

PhysicsEngine::~PhysicsSystem(void)	{

}

void	PhysicsEngine::Update(float msec) {
	BroadPhaseCollisions();
	NarrowPhaseCollisions();

	for (vector<PhysicsEntity*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		(*i)->Update(msec);
	}
}

void	PhysicsEngine::BroadPhaseCollisions() {

}

void	PhysicsEngine::NarrowPhaseCollisions() {

}

void	PhysicsEngine::AddNode(PhysicsEntity* n) {
	allNodes.push_back(n);
}

void	PhysicsEngine::RemoveNode(PhysicsEntity* n) {
	for (vector<PhysicsEntity*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		if ((*i) == n) {
			allNodes.erase(i);
			return;
		}
	}
}

bool PhysicsEngine::SphereSphereCollision(const CollisionSphere &s0, const CollisionSphere &s1, CollisionData *collisionData) const {
	return false;
}

bool PhysicsEngine::AABBCollision(const CollisionAABB &cube0, const CollisionAABB &cube1) const{
	return false;
}

bool PhysicsEngine::PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const {
	return false;
}