/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   01.01.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Mesh Interface	@details Advanced Programming 	 *
*																						 *
*****************************************************************************************/

#pragma once
#include "OGLRenderer.h"

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, NORMAL_BUFFER,TANGENT_BUFFER, INDEX_BUFFER, MAX_BUFFER };

class Mesh {
public:
	Mesh(void);
	~Mesh(void);

	virtual void Draw();
	virtual void DrawInstance(unsigned int numInstances);

	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuad();
    void SetRandomPositions(unsigned int numInstances, float LO, float HI);

	void   SetTexture(GLuint tex) { texture = tex;  }
	GLuint GetTexture()           { return texture; }

	void SetBumpMap(GLuint tex)   { bumpTexture = tex; }
	GLuint GetBumpMap()			  { return bumpTexture; }

	Vector3* GetVertices()		  { return vertices; }

protected:
	void	 BufferData();
	void	 GenerateNormals();

	void GenerateTangents();
	Vector3 GenerateTangent( const Vector3 &a, const Vector3 &b,
							 const Vector3 &c, const Vector2 &ta,
							 const Vector2 &tb,const Vector2 &tc);
	GLuint   arrayObject;
	GLuint   bufferObject[MAX_BUFFER];
	GLuint   numVertices;
	GLuint   type;
	GLuint   texture;
	GLuint   numIndices;
	Vector2* textureCoords;
	Vector3* vertices;

	Vector3* rndPos;
	GLuint   rndPosObject;
	
	Vector3* normals;
	Vector3* tangents;
	Vector4* colours;
	unsigned int* indices;
	GLuint   bumpTexture;
};