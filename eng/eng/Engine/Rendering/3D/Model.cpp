#include "Model.h"


Model::Model(const std::string objPath, const std::string matPath, GLuint ShaderProgram_) : subMeshes(std::vector<Mesh*>())
{
	subMeshes = std::vector<Mesh*>();
	shaderProgram = 0;
	shaderProgram = ShaderProgram_;
	obj = new LoadObjModel();
	obj->LoadModel(objPath, matPath);
	this->LoadModel();
	

}

Model::~Model()
{
	OnDestroy();
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}

void Model::Render( Camera* camera)
{
	glUseProgram(shaderProgram);
	for (auto m : subMeshes)
	{
		m->Render( camera, modleInstance);
	}
}

void Model::OnDestroy()
{
	if (subMeshes.size() > 0)
	{
		for (auto m : subMeshes)
		{
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
	modleInstance.clear();
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modleInstance.push_back(GetTransform(position_, angle_, rotation_, scale_));
	return modleInstance.size() - 1;
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modleInstance[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(int index_) const
{
	return modleInstance[index_];
}

BoundingBox Model::GetBoundingBox()
{
	return boundingBox;
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 modle;
	modle = glm::translate(modle, position_);
	modle = glm::rotate(modle, angle_, rotation_);
	modle = glm::scale(modle, scale_);
	return modle;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	boundingBox = obj->GetBoundingBox();
	delete obj;
	obj = nullptr;
}





