/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	Physics Engine   *
*																						       *
************************************************************************************************/

#pragma once

#include "PhysicsEntity.h"
#include <vector>

using std::vector;

/*
integrating the collision volumes:
- keep pointers to all types inside a physics node, and check to see which ones are NULL. 
- make all collision volumes inherit from a base class; a single pointer inside each Physics Node. 
- use a process of dynamic casting to determine which exact type of volume the pointer is,
- use an enum member, variable

enum CollisionVolumeType {
COLLISION_SPHERE,
COLLISION_AABB,
COLLISION_PLANE
}


class CollisionVolume {
public:
CollisionVolumeType GetType() { return type;}


protected:
CollisionVolumeType type;
};

*/

//
class CollisionSphere {

};

class CollisionAABB {

};

class CollisionData {

};


class PhysicsEngine	{
public:
	friend class GameClass;

	void		Update(float msec);

	void		BroadPhaseCollisions();
	void		NarrowPhaseCollisions();

	//Statics
	static void Initialise() {
		instance = new PhysicsEngine();
	}

	static void Destroy() {
		delete instance;
	}

	static PhysicsEngine& GetPhysicsSystem() {
		return *instance;
	}

	void	AddNode(PhysicsEntity* n);

	void	RemoveNode(PhysicsEntity* n);

protected:
	PhysicsEngine(void);
	~PhysicsEngine(void);

	bool SphereSphereCollision(const CollisionSphere &s0, const CollisionSphere &s1, CollisionData *collisionData = NULL) const;
	bool AABBCollision(const CollisionAABB &cube0, const CollisionAABB &cube1) const;

	//bool SphereAABBCollision(const CollisionSphere &sphere, const CollisionAABB &cube, CollisionData *collisionData = NULL) const; //Research!!!! :-)


	//Sphere plane collisions we started in the previous module, and expand upon via the Plane class..

	bool PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const;



	//Statics
	static PhysicsEngine* instance;

	vector<PhysicsEntity*> allNodes;
};