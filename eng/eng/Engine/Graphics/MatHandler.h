#pragma once
#include <glm/glm.hpp>
#include <glew.h>
#include <memory>
#include <map>
#include <string>

struct Material
{
	GLuint diffuseMap;
	float shininess; //ns
	float transparancy; //d
	glm::vec3 ambiant; //ka
	glm::vec3 diffuse; //kd
	glm::vec3 specular; //ks

	inline Material() : diffuseMap(0), shininess(0.0f), transparancy(0.0f), ambiant(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3()) {}
};

class MatHandler
{
public:
	MatHandler(const MatHandler&) = delete;
	MatHandler(MatHandler&&) = delete;
	MatHandler& operator=(const MatHandler&) = delete;
	MatHandler& operator=(MatHandler&&) = delete;

	static MatHandler* GetInstance();

	void AddMat(const std::string& name_, Material mat_);
	const Material GetMat(const std::string& name_);
	void OnDestroy();

private:
	MatHandler();
	~MatHandler();

	static std::unique_ptr<MatHandler> matInstance;
	friend std::default_delete<MatHandler>;

	static std::map<std::string, Material> materials;
};

