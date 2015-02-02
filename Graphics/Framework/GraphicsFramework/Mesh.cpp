/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   01.02.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Mesh CLASS   	@details Advanced Programming 	 *
*																						 *
*****************************************************************************************/

#include "../../nclgl/Mesh.h"
#include <time.h>

Mesh::Mesh(void) {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &arrayObject);

	indices		  = NULL;
	numIndices    = 0;
	numVertices   = 0;
	vertices      = NULL;
	colours       = NULL;
	type          = GL_TRIANGLES;
	texture       = 0;
	normals       = NULL;
	tangents      = NULL;
	bumpTexture   = 0;
	textureCoords = NULL;
}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteVertexArrays(MAX_BUFFER, bufferObject);
	glDeleteTextures(1,&texture);
	glDeleteTextures(1, &bumpTexture);

	delete []textureCoords;
	delete []vertices;
	delete []colours;
	delete []indices;
	delete []normals;
	delete []tangents;
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* m = new Mesh();
	
	m->numVertices = 3;
	m->vertices = new Vector3[m->numVertices];
	m->vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m->vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m->vertices[2] = Vector3(-0.5f,-0.5f, 0.0f);

	m->textureCoords = new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f, 0.0f);
	m->textureCoords[1] = Vector2(1.0f, 1.0f);
	m->textureCoords[2] = Vector2(0.0f, 1.0f);

	m->colours = new Vector4[m->numVertices];
	m->colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

	m->BufferData();
	return m;
}

Mesh* Mesh::GenerateQuad() {
	Mesh* m = new Mesh();
	m->numVertices = 4;
	m->type = GL_TRIANGLE_STRIP;

	m->vertices      = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->colours       = new Vector4[m->numVertices];
	m->normals       = new Vector3[m->numVertices];
	m->tangents      = new Vector3[m->numVertices];

	m->vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	m->vertices[1] = Vector3(-1.0f,  1.0f, 0.0f);
	m->vertices[2] = Vector3( 1.0f, -1.0f, 0.0f);
	m->vertices[3] = Vector3( 1.0f,  1.0f, 0.0f);

	m->textureCoords[0] = Vector2( 0.0f, 1.0f);
	m->textureCoords[1] = Vector2( 0.0f, 0.0f);
	m->textureCoords[2] = Vector2( 1.0f, 1.0f);
	m->textureCoords[3] = Vector2( 1.0f, 0.0f);
	
	for (int i = 0; i < 4; ++i) {
		m->colours[i]  = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		m->normals[i]  = Vector3(0.0f, 0.0f, -1.0f);
		m->tangents[i] = Vector3(1.0f, 0.0f, 0.0f);
	}

	m->BufferData();
	return m;
}

void Mesh::BufferData(){
	
	glBindVertexArray(arrayObject);
	
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0,0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if (textureCoords){
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if (colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE,0,0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	if (indices){
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	if (normals){
		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if (tangents){
		glGenBuffers(1, &bufferObject[TANGENT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TANGENT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TANGENT_BUFFER);
	}

	glBindVertexArray(0);
}

void Mesh::Draw() {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpTexture);

	glBindVertexArray(arrayObject);
	
	if (bufferObject[INDEX_BUFFER]){
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(type, 0, numVertices);
	}
	glBindVertexArray(0);
}

void Mesh::DrawInstance(unsigned int numInstances) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(arrayObject);

	glDrawArraysInstanced(type, 0, numInstances, numInstances);
	glBindVertexArray(0);
}

void Mesh::SetRandomPositions(unsigned int numInstances, float LO, float HI){
	rndPos = new Vector3[numInstances];

	srand(time(0));
	for (int i = 0; i < numInstances; ++i) {
		rndPos[i] = Vector3(LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO))), 
							DegToRad((rand() / (float)RAND_MAX)*360.0f),
							LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO))));
	}

	glBindVertexArray(arrayObject);
	glGenBuffers(1, &rndPosObject);
	glBindBuffer(GL_ARRAY_BUFFER, rndPosObject);
	glBufferData(GL_ARRAY_BUFFER, numInstances * sizeof(Vector3), rndPos, GL_STATIC_DRAW);

	glVertexAttribPointer(MAX_BUFFER + 1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(MAX_BUFFER + 1);
	glVertexAttribDivisor(MAX_BUFFER + 1, 1);

	glBindVertexArray(0);
}

void Mesh::GenerateNormals(){
	if (!normals) {
		normals = new Vector3[numVertices];
	}
	for (GLuint i = 0; i < numVertices; ++i){
		normals[i] = Vector3();
	}
	
	if (indices) {
		for (GLuint i = 0; i < numIndices; i+=3){
			unsigned int a = indices[i];
			unsigned int b = indices[i + 1];
			unsigned int c = indices[i + 2];

			Vector3 normal = Vector3::Cross( (vertices[b] - vertices[a]), (vertices[c] - vertices[a]));
			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
		}
	}

	else{
		for (GLuint i = 0; i < numVertices; i += 3){
			Vector3 &a = vertices[i];
			Vector3 &b = vertices[i + 1];
			Vector3 &c = vertices[i + 2];

			Vector3 normal = Vector3::Cross(b-a, c-a);

			normals[i] = normal;
			normals[i + 1] = normal;
			normals[i + 2] = normal;
		}
	}
	for (GLuint i = 0; i < numVertices; ++i){
		normals[i].Normalise();
	}
}

void Mesh::GenerateTangents(){
	if (!tangents) {
		tangents = new Vector3[numVertices];
	}
	for (GLuint i = 0; i < numVertices; ++i){
		tangents[i] = Vector3();
	}

	if (indices) {
		for (GLuint i = 0; i < numIndices; i += 3){
			unsigned int a = indices[i];
			unsigned int b = indices[i + 1];
			unsigned int c = indices[i + 2];

			Vector3 tangent = GenerateTangent(vertices[a], vertices[b], vertices[c], textureCoords[a], textureCoords[b], textureCoords[c]);
			tangents[a] += tangent;
			tangents[b] += tangent;
			tangents[c] += tangent;
		}
	}

	else{
		for (GLuint i = 0; i < numVertices; i += 3){
			Vector3 tangent = GenerateTangent(vertices[i], vertices[i+1],
							  vertices[i+2], textureCoords[i],
							  textureCoords[i+1], textureCoords[i+2]);
			
			tangents[i] = tangent;
			tangents[i + 1] = tangent;
			tangents[i + 2] = tangent;
		}
	}
	for (GLuint i = 0; i < numVertices; ++i){
		tangents[i].Normalise();
	}
}

Vector3 Mesh::GenerateTangent(const Vector3 &a, const Vector3 &b,
							  const Vector3 &c, const Vector2 &ta,
							  const Vector2 &tb, const Vector2 &tc){
	Vector2 coord1 = tb - ta;
	Vector2 coord2 = tc - ta;

	Vector3 vertex1 = b - a;
	Vector3 vertex2 = c - a;

	Vector3 axis = Vector3(vertex1 * coord2.y - vertex2 * coord1.y);
	float factor = 1.0f / (coord1.x * coord2.y - coord2.x * coord1.y);

	return axis * factor;
}