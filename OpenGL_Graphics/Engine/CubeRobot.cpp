#include "CubeRobot.h"

Mesh* CubeRobot::cube = NULL;

CubeRobot::CubeRobot(void) {
	//optional -- create a local origin marker
	//SetMesh(cube);

	SceneNode*body = new SceneNode(cube, Vector4(1, 0, 0, 1)); 
	body->SetModelScale(Vector3(10, 15, 5));
	body->SetLocalTransform(Matrix4::Translation(Vector3(0, 35, 0)));
	AddChild(body);

	head = new SceneNode(cube, Vector4(0, 1, 0, 1));
	head->SetModelScale(Vector3(5, 5, 5));
	head->SetLocalTransform(Matrix4::Translation(Vector3(0, 30, 0)));
	body->AddChild(head);

	leftArm = new SceneNode(cube, Vector4(0, 0, 1, 1));
	leftArm->SetModelScale(Vector3(3, -18, 3));
	leftArm->SetLocalTransform(Matrix4::Translation(Vector3(-12, 30, -1)));
	body->AddChild(leftArm);

	rightArm = new SceneNode(cube, Vector4(0, 0, 1, 1));
	rightArm->SetModelScale(Vector3(3, -18, 3));
	rightArm->SetLocalTransform(Matrix4::Translation(Vector3(12, 30, -1)));
	body->AddChild(rightArm);

	SceneNode* leftLeg = new SceneNode(cube, Vector4(0, 0, 1, 1));
	leftLeg->SetModelScale(Vector3(3, -17.5, 3));
	leftLeg->SetLocalTransform(Matrix4::Translation(Vector3(-8, 0, 0)));
	body->AddChild(leftLeg);

	SceneNode* rightLeg = new SceneNode(cube, Vector4(0, 0, 1, 1));
	rightLeg->SetModelScale(Vector3(3, -17.5, 3));
	rightLeg->SetLocalTransform(Matrix4::Translation(Vector3(8, 0, 0)));
	body->AddChild(rightLeg);

	body->SetBoundingRadius(15.0f);
	head->SetBoundingRadius(5.0f);
	leftArm->SetBoundingRadius(18.0f);
	rightArm->SetBoundingRadius(18.0f);
	leftLeg->SetBoundingRadius(18.0f);
	rightLeg->SetBoundingRadius(18.0f);
}

void CubeRobot::Update(float msec) {
	m_LocalTransform = m_LocalTransform *Matrix4::Rotation(msec / 10.0f, Vector3(0, 1, 0));
	head->SetLocalTransform(head->GetLocalTransform() * Matrix4::Rotation(-msec / 10.0f, Vector3(0, 1, 0)));
	leftArm->SetLocalTransform(leftArm->GetLocalTransform() * Matrix4::Rotation(-msec / 10.0f, Vector3(1, 0, 0)));
	rightArm->SetLocalTransform(rightArm->GetLocalTransform() * Matrix4::Rotation(msec / 10.0f, Vector3(1, 0, 0)));

	SceneNode::Update(msec);
}
