#include "LoadObjModel.h"


LoadObjModel::LoadObjModel() : currentTexture(0)
{
	
}

LoadObjModel::~LoadObjModel()
{
	OnDestroy();
}

void LoadObjModel::LoadModel(const std::string fileName_)
{
	std::ifstream in(fileName_, std::ios::in);
	if (!in)
	{
		Debug::Error("cant open obj: " + fileName_, "LoadObjModle.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line))
	{//VERT
		if (line.substr(0, 2) == "v ") 
		{
			glm::vec3 vert;
			double x, y, z;
			std::stringstream v(line.substr(2));
			v >> x >> y >> z;
			vert = glm::vec3(x, y, z);
			vertices.push_back(vert);
		}
		//normal
		if (line.substr(0, 3) == "vn ")
		{
			glm::vec3 vert;
			double x, y, z;
			std::stringstream v(line.substr(2));
			v >> x >> y >> z;
			vert = glm::vec3(x, y, z);
			normals.push_back(vert);
		}
		//Tex
		if (line.substr(0, 3) == "vt ")
		{
			glm::vec2 vert;
			double x, y;
			std::stringstream v(line.substr(2));
			v >> x >> y;
			vert = glm::vec2(x, y);
			textureCoords.push_back(vert);
		}
		//face
		if (line.substr(0, 1) == "f") 
		{
			std::stringstream v(line.substr(2));

			std::string vert1;
			v >> vert1;
			std::string vert2;
			v >> vert2;
			std::string vert3;
			v >> vert3;

			int dilimI1 = vert1.find("/", 0);
			int startT1 = dilimI1 + 1;
			int dilimT1 = vert1.find("/", startT1);
			int startN1 = dilimT1 + 1;
			int dilimN1 = vert1.find(" ", startN1);

			int dilimI2 = vert2.find("/", 0);
			int startT2 = dilimI2 + 1;
			int dilimT2 = vert2.find("/", startT2);
			int startN2 = dilimT2 + 1;
			int dilimN2 = vert2.find(" ", startN2);

			int dilimI3 = vert3.find("/", 0);
			int startT3 = dilimI3 + 1;
			int dilimT3 = vert3.find("/", startT3);
			int startN3 = dilimT3 + 1;
			int dilimN3 = vert3.find(" ", startN3);

			indices.push_back(stoi(vert1.substr(0, dilimI1)) - 1);
			indices.push_back(stoi(vert2.substr(0, dilimI2)) - 1);
			indices.push_back(stoi(vert3.substr(0, dilimI3)) - 1);


			
			textureIndices.push_back(stoi(vert1.substr(startT1, dilimT1)) - 1);
			textureIndices.push_back(stoi(vert2.substr(startT2, dilimT2)) - 1);
			textureIndices.push_back(stoi(vert3.substr(startT3, dilimT3)) - 1);

			normalIndices.push_back(stoi(vert1.substr(startN1)) - 1);
			normalIndices.push_back(stoi(vert2.substr(startN2)) - 1);
			normalIndices.push_back(stoi(vert3.substr(startN3)) - 1);

		}
		//New Mate
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadObjModel::LoadModel(const std::string fileName_, const std::string& matName_)
{
	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadObjModel::GetVerts()
{
	return meshVertices;
}

std::vector<int> LoadObjModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes()
{
	return subMeshs;
}

BoundingBox LoadObjModel::GetBoundingBox()
{
	float maxX = FLT_MAX; float maxY = FLT_MAX; float maxZ = FLT_MAX;
	float minX = -FLT_MAX; float minY = -FLT_MAX; float minZ = -FLT_MAX;

	for (auto v : vertices)
	{
		//min
		if (v.x < minVert.x)
		{
			minVert.x = v.x;
		}
		if (v.y < minVert.y)
		{
			minVert.y = v.y;
		}
		if (v.z < minVert.z)
		{
			minVert.z = v.z;
		}

		//max
		if (v.x > minVert.x)
		{
			maxVert.x = v.x;
		}
		if (v.y > minVert.y)
		{
			maxVert.y = v.y;
		}
		if (v.z > minVert.z)
		{
			maxVert.z = v.z;
		}

	}
	boundingBox.minVert.x = minVert.x;
	boundingBox.minVert.y = minVert.y;
	boundingBox.minVert.z = minVert.z;
	boundingBox.maxVert.x = maxVert.x;
	boundingBox.maxVert.y = maxVert.y;
	boundingBox.maxVert.z = maxVert.z;



	return boundingBox;
}

void LoadObjModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshs.clear();
}

void LoadObjModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		

		/*for (int j = i + 1; j < indices.size(); j++)
		{
			if (vert.position.x < vertices[indices[j] - 1].x)
			{
				minVert.x = vert.position.x;
			}
			if (vert.position.y < vertices[indices[j] - 1].y)
			{
				minVert.y = vert.position.y;
			}
			if (vert.position.z < vertices[indices[j] - 1].z)
			{
				minVert.z = vert.position.z;
			}
			if (vert.position.x < vertices[indices[j] - 1].x)
			{
				minVert.x = vert.position.x;
			}
			if (vert.position.x > vertices[indices[j] - 1].x)
			{
				maxVert.x = vert.position.x;
			}
			if (vert.position.y > vertices[indices[j] - 1].y)
			{
				maxVert.y = vert.position.y;
			}
			if (vert.position.z > vertices[indices[j] - 1].z)
			{
				maxVert.z = vert.position.z;
			}

		}*/
		meshVertices.push_back(vert);

	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;
	subMeshs.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();

	currentTexture = 0;
}

void LoadObjModel::LoadMaterial(const std::string& fileName)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(fileName);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName, "./Engine/Textures/" + fileName + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName);
	}
}

void LoadObjModel::LoadMaterialLibrary(const std::string& matName_)
{
	/*std::ifstream in(matName_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("could not open mtlFile: " + matName_, "LoadObjModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			LoadMaterial(line.substr(7));
		}
	}*/
	MatLoader::LoadMat(matName_);
}
