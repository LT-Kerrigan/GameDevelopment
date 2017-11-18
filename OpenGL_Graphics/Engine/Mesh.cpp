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


//Mesh*	Mesh::LoadMeshFile(const string &filename) {
//	ifstream f(filename);
//
//	if (!f) {
//		return NULL;
//	}
//
//	Mesh*m = new Mesh();
//	f >> m->m_NumVertices;
//
//	int hasTex = 0;
//	int hasColour = 0;
//
//	f >> hasTex;
//	f >> hasColour;
//
//	m->m_Vertices = new Vector3[m->m_NumVertices];
//
//	if (hasTex) {
//		m->m_TextureCoords = new Vector2[m->m_NumVertices];
//		m->m_Colours = new Vector4[m->m_NumVertices];
//	}
//
//	for (unsigned int i = 0; i < m->m_NumVertices; ++i) {
//		f >> m->m_Vertices[i].x;
//		f >> m->m_Vertices[i].y;
//		f >> m->m_Vertices[i].z;
//	}
//
//	if (hasColour) {
//		for (unsigned int i = 0; i < m->m_NumVertices; ++i) {
//			unsigned int r, g, b, a;
//
//			f >> r;
//			f >> g;
//			f >> b;
//			f >> a;
//			//OpenGL can use floats for colours directly - this will take up 4x as
//			//much space, but could avoid any byte / float conversions happening
//			//behind the scenes in our shader executions
//			m->m_Colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
//		}
//	}
//
//	if (hasTex) {
//		for (unsigned int i = 0; i < m->m_NumVertices; ++i) {
//			f >> m->m_TextureCoords[i].x;
//			f >> m->m_TextureCoords[i].y;
//		}
//	}
//
//	m->BufferData();
//	return m;
//}

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

Mesh*	Mesh::GeneratePointArray(float width, float height) {
	Mesh*m = new Mesh();

	m->m_Type = GL_POINTS;

	m->m_NumVertices = width * height;

	m->m_Vertices = new Vector3[m->m_NumVertices];
	m->m_TextureCoords = new Vector2[m->m_NumVertices];
	m->m_Colours = new Vector4[m->m_NumVertices];

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = (y*width) + x;

			m->m_Vertices[index] = Vector3(-1.0f + ((x / width) * 2.0f), -1.0f + ((y / height) * 2.0f), 0.0f);

			m->m_TextureCoords[index] = Vector2(x / width, y / height);

			m->m_Colours[index] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	m->BufferData();

	return m;
}

Mesh* Mesh::GenerateSphereMesh(float radius, unsigned int rings, unsigned int sectors) {
	Mesh* sphereMesh = new Mesh();
	sphereMesh->m_Type = GL_TRIANGLES;

	// Generate a sphere
	float const RingsRecip = 1.0 / (float)(rings - 1);
	float const SectorsRecip = 1.0 / (float)(sectors - 1);
	int countRings, countSectors;

	sphereMesh->m_NumVertices = rings * sectors;
	sphereMesh->m_NumIndices = (rings - 1) * (sectors - 1) * 6;

	sphereMesh->m_Vertices = new Vector3[sphereMesh->m_NumVertices];
	sphereMesh->m_TextureCoords = new Vector2[sphereMesh->m_NumVertices];
	sphereMesh->m_Colours = new Vector4[sphereMesh->m_NumVertices];

	sphereMesh->m_Indices = new unsigned int[sphereMesh->m_NumIndices];

	int at = 0;

	// Calculate vertices' position and their respective texture coordinates 
	for (countRings = 0; countRings < rings; countRings++) {
		float const y = sin(-PI / 2 + PI * countRings * RingsRecip) * radius;

		for (countSectors = 0; countSectors < sectors; countSectors++) {
			float const x = cos(2 * PI * countSectors * SectorsRecip) * sin(PI * countRings * RingsRecip);
			float const z = sin(2 * PI * countSectors * SectorsRecip) * sin(PI * countRings * RingsRecip);

			sphereMesh->m_TextureCoords[at].x = countSectors * SectorsRecip;
			sphereMesh->m_TextureCoords[at].y = countRings * RingsRecip;

			sphereMesh->m_Vertices[at].x = x * radius;
			sphereMesh->m_Vertices[at].y = y;
			sphereMesh->m_Vertices[at].z = z * radius;

			sphereMesh->m_Colours[at] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

			at++;
		}
	}

	at = 0;
	for (countRings = 0; countRings < rings - 1; countRings++) {
		for (countSectors = 0; countSectors < sectors - 1; countSectors++) {
			sphereMesh->m_Indices[at++] = (countRings + 0) * sectors + countSectors;				// added for half-symmetry
			sphereMesh->m_Indices[at++] = (countRings + 0) * sectors + (countSectors + 1);
			sphereMesh->m_Indices[at++] = (countRings + 1) * sectors + (countSectors + 1);
			sphereMesh->m_Indices[at++] = (countRings + 0) * sectors + countSectors;
			sphereMesh->m_Indices[at++] = (countRings + 1) * sectors + countSectors;
			sphereMesh->m_Indices[at++] = (countRings + 1) * sectors + (countSectors + 1);			// since we're using GL_TRIANGLE with indices to draw the mesh
		}
	}

	sphereMesh->GenerateNormals();
	sphereMesh->GenerateTangents();
	sphereMesh->BufferData();

	return sphereMesh;
}


Mesh* Mesh::GenerateCubeMesh(Vector3 dim) {
	Mesh* cube = new Mesh();
	cube->m_Type = GL_TRIANGLES;
	cube->m_NumVertices = 24;
	cube->m_NumIndices = 36;
	cube->m_Vertices = new Vector3[cube->m_NumVertices];
	cube->m_Indices = new unsigned int[cube->m_NumIndices];
	cube->m_Colours = new Vector4[cube->m_NumVertices];

	std::vector<unsigned int> indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Right face
		7, 6, 5, 5, 4, 7,
		// Back face
		11, 10, 9, 9, 8, 11,
		// Left face
		15, 14, 13, 13, 12, 15,
		// Top Face	
		19, 18, 17, 17, 16, 19,
		// Bottom Face
		23, 22, 21, 21, 20, 23 };

	for (int j = 0; j < indices.size(); j++) {
		cube->m_Indices[j] = indices[j];
	}

	dim = dim / 2.0f;

	//front
	cube->m_Vertices[0] = Vector3(-1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[1] = Vector3(1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[2] = Vector3(1.0f, 1.0f, 1.0f)*dim;
	cube->m_Vertices[3] = Vector3(-1.0f, 1.0f, 1.0f)*dim;

	// Right face
	cube->m_Vertices[4] = Vector3(1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[5] = Vector3(1.0f, -1.0f, -1.0f)*dim;
	cube->m_Vertices[6] = Vector3(1.0f, 1.0f, -1.0f)*dim;
	cube->m_Vertices[7] = Vector3(1.0f, 1.0f, 1.0f)*dim;

	// Back face
	cube->m_Vertices[8] = Vector3(1.0f, -1.0f, -1.0f)*dim;
	cube->m_Vertices[9] = Vector3(-1.0f, -1.0f, -1.0f)*dim;
	cube->m_Vertices[10] = Vector3(-1.0f, 1.0f, -1.0f)*dim;
	cube->m_Vertices[11] = Vector3(1.0f, 1.0f, -1.0f)*dim;

	// Left face
	cube->m_Vertices[12] = Vector3(-1.0f, -1.0f, -1.0f)*dim;
	cube->m_Vertices[13] = Vector3(-1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[14] = Vector3(-1.0f, 1.0f, 1.0f)*dim;
	cube->m_Vertices[15] = Vector3(-1.0f, 1.0f, -1.0f)*dim;

	// Top Face	
	cube->m_Vertices[16] = Vector3(-1.0f, 1.0f, 1.0f)*dim;
	cube->m_Vertices[17] = Vector3(1.0f, 1.0f, 1.0f)*dim;
	cube->m_Vertices[18] = Vector3(1.0f, 1.0f, -1.0f)*dim;
	cube->m_Vertices[19] = Vector3(-1.0f, 1.0f, -1.0f)*dim;

	// Bottom Face
	cube->m_Vertices[20] = Vector3(1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[21] = Vector3(-1.0f, -1.0f, 1.0f)*dim;
	cube->m_Vertices[22] = Vector3(-1.0f, -1.0f, -1.0f)*dim;
	cube->m_Vertices[23] = Vector3(1.0f, -1.0f, -1.0f)*dim;

	for (int i = 0; i < cube->m_NumVertices; i++) {
		cube->m_Colours[i] = Vector4(0.0f, 0.0f, 1.0f, 1.0f); //blue
	}

	cube->BufferData();

	return cube;
}

Mesh* Mesh::GenerateCubeMesh(Vector3 O, float len) {
	Mesh* cube = new Mesh();
	cube->m_Type = GL_TRIANGLES;
	cube->m_NumVertices = 24;
	cube->m_NumIndices = 36;
	cube->m_Vertices = new Vector3[cube->m_NumVertices];
	cube->m_Indices = new unsigned int[cube->m_NumIndices];
	cube->m_Colours = new Vector4[cube->m_NumVertices];

	std::vector<Vector3> vertices;
	std::vector<Vector4> color;

	std::vector<unsigned int> indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Right face
		7, 6, 5, 5, 4, 7,
		// Back face
		11, 10, 9, 9, 8, 11,
		// Left face
		15, 14, 13, 13, 12, 15,
		// Top Face	
		19, 18, 17, 17, 16, 19,
		// Bottom Face
		23, 22, 21, 21, 20, 23 };
	//front

	for (int j = 0; j < indices.size(); j++) {
		cube->m_Indices[j] = indices[j];
	}

	float dim = len / 2.0f;


	//front
	cube->m_Vertices[0] = Vector3(O.x - dim, O.y - dim, O.z + dim);
	cube->m_Vertices[1] = Vector3(O.x + dim, O.y - dim, O.z + dim);
	cube->m_Vertices[2] = Vector3(O.x + dim, O.y + dim, O.z + dim);
	cube->m_Vertices[3] = Vector3(O.x - dim, O.y + dim, O.z + dim);

	// Right face
	cube->m_Vertices[4] = Vector3(O.x + dim, O.y - dim, O.z + dim);
	cube->m_Vertices[5] = Vector3(O.x + dim, O.y - dim, O.z - dim);
	cube->m_Vertices[6] = Vector3(O.x + dim, O.y + dim, O.z - dim);
	cube->m_Vertices[7] = Vector3(O.x + dim, O.y + dim, O.z + dim);

	// Back face
	cube->m_Vertices[8] = Vector3(O.x + dim, O.y - dim, O.z - dim);
	cube->m_Vertices[9] = Vector3(O.x - dim, O.y - dim, O.z - dim);
	cube->m_Vertices[10] = Vector3(O.x - dim, O.y + dim, O.z - dim);
	cube->m_Vertices[11] = Vector3(O.x + dim, O.y + dim, O.z - dim);

	// Left face
	cube->m_Vertices[12] = Vector3(O.x - dim, O.y - dim, O.z - dim);
	cube->m_Vertices[13] = Vector3(O.x - dim, O.y - dim, O.z + dim);
	cube->m_Vertices[14] = Vector3(O.x - dim, O.y + dim, O.z + dim);
	cube->m_Vertices[15] = Vector3(O.x - dim, O.y + dim, O.z - dim);

	// Top Face	
	cube->m_Vertices[16] = Vector3(O.x - dim, O.y + dim, O.z + dim);
	cube->m_Vertices[17] = Vector3(O.x + dim, O.y + dim, O.z + dim);
	cube->m_Vertices[18] = Vector3(O.x + dim, O.y + dim, O.z - dim);
	cube->m_Vertices[19] = Vector3(O.x - dim, O.y + dim, O.z - dim);

	// Bottom Face
	cube->m_Vertices[20] = Vector3(O.x + dim, O.y - dim, O.z + dim);
	cube->m_Vertices[21] = Vector3(O.x - dim, O.y - dim, O.z + dim);
	cube->m_Vertices[22] = Vector3(O.x - dim, O.y - dim, O.z - dim);
	cube->m_Vertices[23] = Vector3(O.x + dim, O.y - dim, O.z - dim);

	for (int i = 0; i < cube->m_NumVertices; i++) {
		cube->m_Colours[i] = Vector4(0.0f, 0.0f, 1.0f, 1.0f); //blue
	}

	cube->BufferData();

	return cube;
}

Mesh* Mesh::GenAABB(std::vector<Vector3> triangle) {
	GLfloat min_x, max_x, min_y, max_y, min_z, max_z;
	min_x = max_x = triangle[0].x;
	min_y = max_y = triangle[0].y;
	min_z = max_z = triangle[0].z;

	for (int i = 0; i < triangle.size(); i++) {
		if (triangle[i].x < min_x) min_x = triangle[i].x;
		if (triangle[i].x > max_x) max_x = triangle[i].x;
		if (triangle[i].y < min_y) min_y = triangle[i].y;
		if (triangle[i].y > max_y) max_y = triangle[i].y;
		if (triangle[i].z < min_z) min_z = triangle[i].z;
		if (triangle[i].z > max_z) max_z = triangle[i].z;
	}

	Vector3 size = Vector3(max_x - min_x, max_y - min_y, max_z - min_z);
	Vector3 centre = Vector3((min_x + max_x) / 2.0f, (min_y + max_y) / 2.0f, (min_z + max_z) / 2.0f);

	//rescale and centre
	//Matrix4 transform = Matrix4::Translation(centre) * Matrix4::Scale(size);

	Mesh* aabb = new Mesh();
	aabb = Mesh::GenerateCubeMesh(size);
	return aabb;
}

Mesh* Mesh::GenAABB(Vector3* verts, int numverts) {
	GLfloat min_x, max_x, min_y, max_y, min_z, max_z;

	min_x = max_x = verts[0].x;
	min_y = max_y = verts[0].y;
	min_z = max_z = verts[0].z;

	for (int i = 0; i < numverts; i++) {
		if (verts[i].x < min_x) min_x = verts[i].x;
		if (verts[i].x > max_x) max_x = verts[i].x;
		if (verts[i].y < min_y) min_y = verts[i].y;
		if (verts[i].y > max_y) max_y = verts[i].y;
		if (verts[i].z < min_z) min_z = verts[i].z;
		if (verts[i].z > max_z) max_z = verts[i].z;
	}

	Vector3 size = Vector3(max_x - min_x, max_y - min_y, max_z - min_z);
	Vector3 centre = Vector3((min_x + max_x) / 2.0f, (min_y + max_y) / 2.0f, (min_z + max_z) / 2.0f);

	//rescale and centre
	//Matrix4 transform = Matrix4::Translation(centre) * Matrix4::Scale(size);

	Mesh* aabb = new Mesh();
	aabb = Mesh::GenerateCubeMesh(centre, size.x);
	return aabb;
}

Mesh* Mesh::GenerateTiltedTriangle(float scale) {
	Mesh*m = new Mesh();
	m->m_NumVertices = 3;

	m->m_Vertices = new Vector3[m->m_NumVertices];
	m->m_Vertices[0] = Vector3(0.0f, 0.5f, 1.0f)		* scale;
	m->m_Vertices[1] = Vector3(0.5f, -0.5f, -1.0f)	* scale;
	m->m_Vertices[2] = Vector3(-0.5f, -0.5f, -1.0f)	* scale;

	m->m_TextureCoords = new Vector2[m->m_NumVertices];
	m->m_TextureCoords[0] = Vector2(0.5f, 0.0f);
	m->m_TextureCoords[1] = Vector2(1.0f, 1.0f);
	m->m_TextureCoords[2] = Vector2(0.0f, 1.0f);

	m->m_Colours = new Vector4[m->m_NumVertices];
	m->m_Colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->m_Colours[1] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->m_Colours[2] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	m->BufferData();

	return m;
}

Mesh* Mesh::GenerateQuad() {
	Mesh* mesh          = new Mesh();
	mesh->m_NumVertices = 4;
	mesh->m_Type        = GL_TRIANGLE_STRIP;

	mesh->m_Vertices      = new Vector3[mesh->m_NumVertices];
	mesh->m_TextureCoords = new Vector2[mesh->m_NumVertices];
	mesh->m_Colours       = new Vector4[mesh->m_NumVertices];
	mesh->m_Tangents	  = new Vector3[mesh->m_NumVertices];
	mesh->m_Normals		  = new Vector3[mesh->m_NumVertices];

	mesh->m_Vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	mesh->m_Vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);
	mesh->m_Vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
	mesh->m_Vertices[3] = Vector3(1.0f, 1.0f, 0.0f);

	mesh->m_TextureCoords[0] = Vector2(0.0f, 1.0f);
	mesh->m_TextureCoords[1] = Vector2(0.0f, 0.0f);
	mesh->m_TextureCoords[2] = Vector2(1.0f, 1.0f);
	mesh->m_TextureCoords[3] = Vector2(1.0f, 0.0f);

	for (int i = 0; i < 4; ++i) {
		mesh->m_Colours[i]  = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		mesh->m_Normals[i]  = Vector3(0.0f, 0.0f, -1.0f);
		mesh->m_Tangents[i] = Vector3(1.0f, 0.0f, 0.0f);
	}

	//mesh->GenerateNormals();
	//mesh->GenerateTangents();
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

void Mesh::DrawInstanced(unsigned int instances, GLuint dataVBO, Vector3* positions) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpTexture);

	glBindVertexArray(m_ArrayObject);
	
	//upload the instance data
	glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * instances, &positions, GL_DYNAMIC_DRAW);
	glDrawElementsInstanced(m_Type, m_NumVertices, GL_UNSIGNED_INT, 0, instances);

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
	if (!m_TextureCoords) {
		return;
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