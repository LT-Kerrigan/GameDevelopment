#include "Mesh.h"

Mesh::Mesh() {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		m_BufferObject[i] = 0;
	}

	glGenVertexArrays(1, &m_ArrayObject);

	m_NumVertices   = 0;
	m_Vertices      = NULL;
	m_Colours	    = NULL;
	m_Texture       = 0;
	m_TextureCoords = NULL;
	m_Type		    = GL_TRIANGLES;
	m_Indices		= NULL;
	m_NumIndices = 0;
	m_Normals = NULL;
	m_Tangents = NULL;
	bumpTexture = 0;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_ArrayObject);
	glDeleteBuffers(MAX_BUFFER, m_BufferObject);
	delete[] m_Vertices;
	delete[] m_Colours;
	glDeleteTextures(1, &m_Texture);
	glDeleteTextures(1, &bumpTexture);
	delete[] m_TextureCoords;

	delete[] m_Indices;
	delete[] m_Normals;
	delete[] m_Tangents;
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* mesh = new Mesh();

	mesh->m_NumVertices = 3;
	mesh->m_Vertices = new Vector3[mesh->m_NumVertices];
	mesh->m_Vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	mesh->m_Vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	mesh->m_Vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

	mesh->m_TextureCoords = new Vector2[mesh->m_NumVertices];
	mesh->m_TextureCoords[0] = Vector2(0.5f, 0.0f);
	mesh->m_TextureCoords[1] = Vector2(1.0f, 1.0f);
	mesh->m_TextureCoords[2] = Vector2(0.0f, 1.0f);

	mesh->m_Colours = new Vector4[mesh->m_NumVertices];
	mesh->m_Colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->m_Colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->m_Colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

	mesh->BufferData();

	return mesh;
}

Mesh* Mesh::GenerateQuad() {
	Mesh* mesh          = new Mesh();
	mesh->m_NumVertices = 4;
	mesh->m_Type        = GL_TRIANGLE_STRIP;

	mesh->m_Vertices      = new Vector3[mesh->m_NumVertices];
	mesh->m_TextureCoords = new Vector2[mesh->m_NumVertices];
	mesh->m_Colours       = new Vector4[mesh->m_NumVertices];

	mesh->m_Vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	mesh->m_Vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);
	mesh->m_Vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
	mesh->m_Vertices[3] = Vector3(1.0f, 1.0f, 0.0f);

	mesh->m_TextureCoords[0] = Vector2(0.0f, 1.0f);
	mesh->m_TextureCoords[1] = Vector2(0.0f, 0.0f);
	mesh->m_TextureCoords[2] = Vector2(1.0f, 1.0f);
	mesh->m_TextureCoords[3] = Vector2(1.0f, 0.0f);

	for (int i = 0; i < 4; ++i) {
		/*mesh->m_Colours[i]  = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		mesh->m_Normals[i]  = Vector3(0.0f, 0.0f, -1.0f);
		mesh->m_Tangents[i] = Vector3(1.0f, 0.0f, 0.0f);*/
	}

	mesh->BufferData();
	return mesh;
}

void Mesh::BufferData() {
	glBindVertexArray(m_ArrayObject);

	glGenBuffers(1, &m_BufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof (Vector3), m_Vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if (m_TextureCoords) {
		glGenBuffers(1, &m_BufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof (Vector2), m_TextureCoords, GL_STATIC_DRAW);

		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if (m_Colours) {
		glGenBuffers(1, &m_BufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof (Vector4), m_Colours, GL_STATIC_DRAW);

		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	if (m_Indices) {
		glGenBuffers(1, &m_BufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof (GLuint), m_Indices, GL_STATIC_DRAW);
	}

	if (m_Normals){
		glGenBuffers(1, &m_BufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vector3), m_Normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if (m_Tangents){
		glGenBuffers(1, &m_BufferObject[TANGENT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferObject[TANGENT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vector3), m_Tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TANGENT_BUFFER);
	}

	glBindVertexArray(0);
}

void Mesh::Draw() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpTexture);
	
	glBindVertexArray(m_ArrayObject);
	
	if (m_BufferObject[INDEX_BUFFER]) {
		glDrawElements(m_Type, m_NumIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(m_Type, 0, m_NumVertices);
	}
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateNormals(){
	if (!m_Normals) {
		m_Normals = new Vector3[m_NumVertices];
	}
	for (GLuint i = 0; i < m_NumVertices; ++i){
		m_Normals[i] = Vector3();
	}

	if (m_Indices) {
		for (GLuint i = 0; i < m_NumIndices; i += 3){
			unsigned int a = m_Indices[i];
			unsigned int b = m_Indices[i + 1];
			unsigned int c = m_Indices[i + 2];

			Vector3 normal = Vector3::Cross((m_Vertices[b] - m_Vertices[a]), (m_Vertices[c] - m_Vertices[a]));
			m_Normals[a] += normal;
			m_Normals[b] += normal;
			m_Normals[c] += normal;
		}
	}

	else{
		for (GLuint i = 0; i < m_NumVertices; i += 3){
			Vector3 &a = m_Vertices[i];
			Vector3 &b = m_Vertices[i + 1];
			Vector3 &c = m_Vertices[i + 2];

			Vector3 normal = Vector3::Cross(b - a, c - a);

			m_Normals[i] = normal;
			m_Normals[i + 1] = normal;
			m_Normals[i + 2] = normal;
		}
	}
	for (GLuint i = 0; i < m_NumVertices; ++i){
		m_Normals[i].Normalise();
	}
}

void Mesh::GenerateTangents(){
	if (!m_Tangents) {
		m_Tangents = new Vector3[m_NumVertices];
	}
	for (GLuint i = 0; i < m_NumVertices; ++i){
		m_Tangents[i] = Vector3();
	}

	if (m_Indices) {
		for (GLuint i = 0; i < m_NumIndices; i += 3){
			unsigned int a = m_Indices[i];
			unsigned int b = m_Indices[i + 1];
			unsigned int c = m_Indices[i + 2];

			Vector3 tangent = GenerateTangent(m_Vertices[a], m_Vertices[b], m_Vertices[c], m_TextureCoords[a], m_TextureCoords[b], m_TextureCoords[c]);
			m_Tangents[a] += tangent;
			m_Tangents[b] += tangent;
			m_Tangents[c] += tangent;
		}
	}

	else{
		for (GLuint i = 0; i < m_NumVertices; i += 3){
			Vector3 tangent = GenerateTangent(m_Vertices[i], m_Vertices[i + 1],
				m_Vertices[i + 2], m_TextureCoords[i],
				m_TextureCoords[i + 1], m_TextureCoords[i + 2]);

			m_Tangents[i] = tangent;
			m_Tangents[i + 1] = tangent;
			m_Tangents[i + 2] = tangent;
		}
	}
	for (GLuint i = 0; i < m_NumVertices; ++i){
		m_Tangents[i].Normalise();
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