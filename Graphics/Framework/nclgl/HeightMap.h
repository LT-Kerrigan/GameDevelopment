/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  HeightMap	   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../nclgl/Vector3.h"
#include "../nclgl/Mesh.h"

#define RAW_WIDTH		513
#define RAW_HEIGHT		513
#define HEIGHTMAP_X		32.0f//16.0f
#define HEIGHTMAP_Z		32.0f//16.0f
#define HEIGHTMAP_Y     5.5f//2.25f
#define HEIGHTMAP_TEX_X 1.0f / 16.0f
#define HEIGHTMAP_TEX_Z 1.0f / 16.0f

class HeightMap : public Mesh {
public:
	HeightMap(std::string name);
	~HeightMap(void){};

	void BindToTex(unsigned char* data);

	float GetHeightAt(const Vector3 &position);
                  
	GLuint vertexBuffer;
	GLuint vertexTexture;
	GLuint heightmapY;
};