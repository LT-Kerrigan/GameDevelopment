#include "TestEngine.h"

TestEngine::TestEngine()	{
	gameCamera = new Camera(-30.0f, 0.0f, Vector3(0, 450, 850));

	Renderer::GetRenderer().SetCamera(gameCamera);

	CubeRobot::CreateCube();

	/*
	manage the meshes in the game class
	'get / load texture' part of the Renderer or OGLRenderer,
	*/
	cube = new OBJMesh("../Meshes/cube.obj");
	quad = Mesh::GenerateQuad();
	sphere = new OBJMesh("../Meshes/ico.obj");

	/*
	A more 'robust' system would check the entities vector for duplicates so as
	to not cause problems
	*/
	allEntities.push_back(BuildRobotEntity());
	allEntities.push_back(BuildQuadEntity(1000.0f));
}

TestEngine::~TestEngine(void)	{
	delete cube;
	delete quad;
	delete sphere;

	CubeRobot::DeleteCube();

	//GameClass destructor will destroy entities
}

/*
base 'skeleton' of your game update loop! 
game logic will be added to this function.
*/
void TestEngine::UpdateGame(float msec) {
	if (gameCamera) {
		gameCamera->UpdateCamera(msec);
	}

	for (vector<GameEntity*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i) {
		(*i)->Update(msec);
	}

	/*
	draw squares, lines, crosses and circles, of varying size and
	colour - in either perspective or orthographic mode.

	Orthographic debug drawing uses a 'virtual canvas' of 720 * 480 -
	that is 0,0 is the top left, and 720,480 is the bottom right. A function
	inside OGLRenderer is provided to convert clip space coordinates into
	this canvas space coordinates. determine clip space via renderer  
	getters for the view and projection matrix

	Camera class could be extended to contain a projection matrix
	--> game would be able to determine clip space coordinates for its
	active Camera without having to involve the Renderer

	Perspective debug drawing relies on the view and projection matrices inside
	the renderer being correct at the point where 'SwapBuffers' is called. As
	long as these are valid, perspective drawing will appear in the world.

	This gets a bit more tricky with advanced rendering techniques like deferred
	rendering, as there's no guarantee of the state of the depth buffer, or that
	the perspective matrix isn't othographic --> draw debug lines before the 
	inbuilt position before SwapBuffers - there are two OGLRenderer functions 
	DrawDebugPerspective and DrawDebugOrtho that can
	be called at the appropriate place in the pipeline. Both take in a viewProj
	matrix as an optional parameter.

	Debug rendering uses its own debug shader, and so should be unnaffected by
	and shader changes made 'outside' of debug drawing
	*/

	// draw a box around the cube robot!
	Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, Vector3(0, 51, 0), Vector3(100, 100, 100), Vector3(1, 0, 0));

	// draw a line from the cube robot to the target
	// The 1 on the y axis is simply to prevent z-fighting!
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, Vector3(0, 1, 0), Vector3(200, 1, 200), Vector3(0, 0, 1), Vector3(1, 0, 0));

	// draw intersection
	Renderer::GetRenderer().DrawDebugCross(DEBUGDRAW_PERSPECTIVE, Vector3(200, 1, 200), Vector3(50, 50, 50), Vector3(0, 0, 0));

	// swap
	Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, Vector3(-200, 1, -200), 50.0f, Vector3(0, 1, 0));
}

/*
Makes an entity that looks like a CubeRobot! You'll probably want to modify
this so that you can have different sized robots, with different masses and
so on!
*/
GameEntity* TestEngine::BuildRobotEntity() {
	GameEntity*g = new GameEntity(new CubeRobot(), new PhysicsEntity());

	g->ConnectToSystems();
	return g;
}

/*
Makes a cube. Every game has a crate in it somewhere!
*/
GameEntity* TestEngine::BuildCubeEntity(float size) {
	GameEntity*g = new GameEntity(new SceneNode(cube), new PhysicsEntity());
	g->ConnectToSystems();

	SceneNode &test = g->GetRenderNode();

	test.SetModelScale(Vector3(size, size, size));
	test.SetBoundingRadius(size);

	return g;
}
/*
Makes a sphere.
*/
GameEntity* TestEngine::BuildSphereEntity(float radius) {
	SceneNode* s = new SceneNode(sphere);

	s->SetModelScale(Vector3(radius, radius, radius));
	s->SetBoundingRadius(radius);

	GameEntity*g = new GameEntity(s, new PhysicsEntity());
	g->ConnectToSystems();
	return g;
}

/*
Makes a flat quad, initially oriented such that we can use it as a simple
floor.
*/
GameEntity* TestEngine::BuildQuadEntity(float size) {
	SceneNode* s = new SceneNode(quad);

	s->SetModelScale(Vector3(size, size, size));
	//Oh if only we had a set texture function...we could make our brick floor again WINK WINK
	s->SetBoundingRadius(size);

	PhysicsEntity*p = new PhysicsEntity(Quaternion::AxisAngleToQuaterion(Vector3(1, 0, 0), 90.0f), Vector3());

	GameEntity*g = new GameEntity(s, p);
	g->ConnectToSystems();
	return g;
}