#ifndef MESH_H
#define MESH_H

#include "../..//Camera/Camera.h"
#include "..//..//Graphics/MatHandler.h"

#include <glew.h>
#include <vector>
#include <glm/glm.hpp> //Header++
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color; 
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera, std::vector<glm::mat4> &instances);
	void OnDestroy();
private:
	void GenerateBuffers();
	GLuint VA0, VB0;
	GLuint shaderProgram;
	GLuint modleLoc, viewLoc, projLoc, textureLoc;
	SubMesh submesh;
	//LoadObjModel* obj;
};
#endif // !MESH_H
