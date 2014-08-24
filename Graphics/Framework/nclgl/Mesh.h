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

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, MAX_BUFFER};

class Mesh {
public:
	Mesh(void);
	~Mesh(void);

	virtual void Draw();
	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuad();

	void SetTexture(GLuint tex) { texture = tex; }
	GLuint GetTexture() { return texture; }

protected: 
	void BufferData();

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint type;
	GLuint texture;

	Vector2* textureCoords;
	Vector3* vertices;
	Vector4* colours;
};