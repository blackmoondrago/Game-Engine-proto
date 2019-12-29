#pragma once

#include "Mesh.h"
#include "..//..//Graphics/TextureHandler.h"
#include "..//..//..//MatLoader.h"
#include <sstream>
#include "..\\..\\Math\BoundingBox.h"

class LoadObjModel
{
public:
	LoadObjModel();
	~LoadObjModel();


	void LoadModel(const std::string fileName_);
	void LoadModel(const std::string fileName_, const std::string& matName_);
	std::vector<Vertex> GetVerts();
	std::vector<int> GetIndices();
	std::vector<SubMesh> GetSubMeshes();
	BoundingBox GetBoundingBox();
	void OnDestroy();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<int> normalIndices;
	std::vector<int> indices;
	std::vector<int> textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshs;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName);
	void LoadMaterialLibrary(const std::string& matName_);

	glm::vec3 minVert;
	glm::vec3 maxVert;

	GLuint currentTexture;
	BoundingBox boundingBox;

};

