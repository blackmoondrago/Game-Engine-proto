#ifndef MODEL_H
#define MODEL_H



#include "LoadObjModel.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <string>
class Model
{
public:
	Model(const std::string objPath, const std::string matPath, GLuint ShaderProgram_);
	~Model();
	void AddMesh(Mesh* mesh_);
	void Render(Camera* camera);
	void OnDestroy();
	
	int CreateInstance(glm::vec3 position_, float angle, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(int index_) const;
	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;

private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modleInstance;
	glm::mat4 GetTransform(glm::vec3 position_, float angle, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();
	LoadObjModel* obj;
	BoundingBox boundingBox;
};
#endif // !MESH_H
