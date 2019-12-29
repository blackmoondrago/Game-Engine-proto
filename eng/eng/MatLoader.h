#pragma once
#include "Engine/Graphics/MatHandler.h"
#include "Engine/Rendering/3D/LoadObjModel.h"
#include <sstream>
class MatLoader
{



public:
	MatLoader(const MatLoader&) = delete;
	MatLoader(MatLoader&&) = delete;
	MatLoader& operator=(const MatLoader&) = delete;
	MatLoader& operator=(MatLoader&&) = delete;


	MatLoader() = delete;
	~MatLoader();

	static void LoadMat(std::string file_);

private:
	static GLuint LoadTexture(std::string fileName_);
};

