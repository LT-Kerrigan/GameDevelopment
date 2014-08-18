/*******************************************************************************************
*	          .--.																		   *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Graphics       *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 18.08.2014	   *
*	::::::-:.`'..`'.:-::::::			@link								               *
*	::::::::\ `--' /::::::::			@detail	Mesh header holds VAO, VBO, data		   *
*																						   *	
********************************************************************************************/

#pragma once
#include "OGLRenderer.h"

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, MAX_BUFFER};

class Mesh {
public:
	Mesh(void);
	~Mesh(void);

	virtual void Draw();
	static Mesh* GenerateTriangle();

protected: 
	void BufferData();

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint type;

	Vector3* vertices;
	Vector4* colours;
};