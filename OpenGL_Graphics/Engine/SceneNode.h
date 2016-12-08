#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>

class SceneNode {
public:
	SceneNode(Mesh* m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
	~SceneNode();

	void SetLocalTransform(const Matrix4 &matrix) { m_LocalTransform = matrix; }
	const Matrix4& GetLocalTransform() const { return m_LocalTransform; }
	Matrix4 GetWorldTransform() const { return m_WorldTransform; }

	Vector4 GetColour() const { return m_Colour; }
	void SetColour(Vector4 c) { m_Colour = c; }

	Vector3 GetModelScale() const { return m_ModelScale; }
	void SetModelScale(Vector3 s) { m_ModelScale = s; }

	Mesh* GetMesh() const { return m_Mesh; }
	void SetMesh(Mesh*m) { m_Mesh = m; }

	void AddChild(SceneNode* s);

	virtual void Update(float msec);
	virtual void Draw(const OGLRenderer &r);

	float GetBoundingRadius() const { return m_BoundingRadius; }
	void SetBoundingRadius(float f) { m_BoundingRadius = f; }

	float GetCameraDistance() const { return m_DistanceFromCamera; }
	void SetCameraDistance(float f) { m_DistanceFromCamera; }

	//added for 2D to 3D projection
	void SetTransform(Matrix4 transform) { m_LocalTransform = transform; }
	Matrix4 GetTransform() { return m_LocalTransform; }

	static bool CompareByCameraDistance(SceneNode*a, SceneNode*b) {
	return (a->m_DistanceFromCamera < b->m_DistanceFromCamera) ? true : false;
	}
	
	std::vector<SceneNode*>::const_iterator GetChildIteratorStart() {
		return m_Children.begin();
	}

	std::vector<SceneNode*>::const_iterator GetChildIteratorEnd() {
		return m_Children.end();
	}
protected:
	SceneNode* m_Parent;
	Mesh*      m_Mesh;
	Matrix4	   m_WorldTransform;
	Matrix4    m_LocalTransform;
	Vector3	   m_ModelScale;
	Vector4	   m_Colour;
	float	   m_DistanceFromCamera;
	float	   m_BoundingRadius;

	std::vector<SceneNode*> m_Children;
};