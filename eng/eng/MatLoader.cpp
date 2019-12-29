#include "MatLoader.h"



//MatLoader::MatLoader() 
//{
//
//}

MatLoader::~MatLoader()
{
}

void MatLoader::LoadMat(std::string file_)
{
	std::ifstream in(file_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("could not open mtlFile: " + file_, "LoadObjModel.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MatHandler::GetInstance()->AddMat(matName, m);
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(line.substr(7));
			
		}
	}
	if (m.diffuseMap != 0)
	{
		MatHandler::GetInstance()->AddMat(matName, m);
	}
}

GLuint MatLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Engine\Textures" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
