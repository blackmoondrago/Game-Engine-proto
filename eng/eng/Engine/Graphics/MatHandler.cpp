#include "MatHandler.h"

 std::unique_ptr<MatHandler> MatHandler::matInstance = nullptr;
 //std::default_delete<MatHandler>;

std::map<std::string, Material> MatHandler::materials = std::map<std::string, Material>();

MatHandler::MatHandler() 
{

}

MatHandler* MatHandler::GetInstance()
{
	if (matInstance.get() == nullptr)
	{
		matInstance.reset(new MatHandler);

	}
	return matInstance.get();
}

void MatHandler::AddMat(const std::string& name_, Material mat_)
{
	materials[name_] = mat_;
}

const Material MatHandler::GetMat(const std::string& name_)
{
	if (materials.find(name_) != materials.end())
	{
		return materials[name_];
	}
	
	return Material();
}

void MatHandler::OnDestroy()
{
	if (materials.size() > 0)
	{
		materials.clear();
	}
}

MatHandler::~MatHandler()
{
	OnDestroy();
}
