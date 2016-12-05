#include "HeightMap.h"
//#include "../glm/glm/glm.hpp"

//// Enable multitexture blending across heightmap.
//#ifndef ENABLE_MULTITEXTURE
//#define ENABLE_MULTITEXTURE 1
//#endif

//// Enable blend constants based on heightmap's slope.
//#ifndef ENABLE_SLOPE_BASED_BLEND
//#define ENABLE_SLOPE_BASED_BLEND 1
//#endif

//// Alleviate int - * conversion warning (wizardry)
//#define BUFFER_OFFSET(i) ((char*)NULL +(i))

HeightMap::HeightMap(std::string name){
	std::ifstream file(name.c_str(), ios::binary);
	if (!file){
		return;
	}

	m_NumVertices = RAW_WIDTH * RAW_HEIGHT;
	m_NumIndices = (RAW_WIDTH - 1)*(RAW_HEIGHT - 1) * 6;
	m_Vertices = new Vector3[m_NumVertices];
	m_TextureCoords = new Vector2[m_NumVertices];
	m_Indices = new GLuint[m_NumIndices];

	unsigned char* data = new unsigned char[m_NumVertices];
	file.read((char*)data, m_NumVertices*sizeof(unsigned char));
	file.close();

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			m_Vertices[offset] = Vector3(x * HEIGHTMAP_X, data[offset] * HEIGHTMAP_Y, z * HEIGHTMAP_Z);

			m_TextureCoords[offset] = Vector2(x * HEIGHTMAP_TEX_X, z * HEIGHTMAP_TEX_Z);
		}
	}

	delete data;

	m_NumIndices = 0;

	for (int x = 0; x < RAW_WIDTH - 1; ++x){
		for (int z = 0; z < RAW_HEIGHT - 1; ++z){
			int a = (x     * (RAW_WIDTH)) + z;
			int b = ((x + 1) * (RAW_WIDTH)) + z;
			int c = ((x + 1) * (RAW_WIDTH)) + (z + 1);
			int d = (x     * (RAW_WIDTH)) + (z + 1);

			m_Indices[m_NumIndices++] = c;
			m_Indices[m_NumIndices++] = b;
			m_Indices[m_NumIndices++] = a;

			m_Indices[m_NumIndices++] = a;
			m_Indices[m_NumIndices++] = d;
			m_Indices[m_NumIndices++] = c;
		}
	}
	GenerateNormals();
	GenerateTangents();
	BufferData();
}

// Return ration of _value in [_min, _max]. If its <= _min, ret 0 else ret 1.
//inline float GetPercentage(float value, const float min, const float max) {
//	value = glm::clamp(value, min, max);
//	return (value - min) / (max - min);
//}

// Translate incoming char to float array in [0, 1]. BitSizes{8,16,32}
// Intel standard byte encoding / little-endian (low order bytes first)
// For LSB MSB array indices must be reversed forval > 8bit
//inline float GetHeightValue(const unsigned char* data, unsigned char numBytes) {
//	switch (numBytes)
//	{
//	case 1:
//		return (unsigned char)(data[0]) / (float)0xff;
//		break;
//	case 2:
//		return (unsigned short)(data[1] << 8 | data[0]) / (float)0xffff;
//		break;
//	case 4:
//		return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / (float)0xffffffff;
//		break;
//	default:
//		assert(false);  // Height field with non standard pixle sizes
//		break;
//	}
//	return 0.0f;
//}

//void HeightMap::BindToTex(unsigned char* data){
//	//locTex = glGetUniformLocation(grassShader->GetProgram(), "vertexTexture");
//
//	glGenTextures(1, &vertexTexture);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, vertexTexture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, RAW_WIDTH, RAW_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, data);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
