#include "ShaderHandler.h"

std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;

std::map<std::string, GLuint> ShaderHandler::programs = std::map<std::string, GLuint>();

ShaderHandler* ShaderHandler::GetInstance()
{
	if (shaderInstance.get() == nullptr)
	{
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
	
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_)
{
	//get file name
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFileName_);
	//create
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (!linkResult)
	{
		GLint logLength = 0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> programLog(logLength);
		glGetShaderInfoLog(program, logLength, NULL, &programLog[0]);
		std::string logString(programLog.begin(), programLog.end());
		Debug::Error("Error to link program " + shaderName_ + " Error is: " + logString, "ShaderHandler.cpp", __LINE__);
		return;
	}
	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

const GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
	//if shader run 
	if (programs.find(shaderName_) != programs.end())
	{
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::onDestroy()
{
	for (auto entry : programs)
	{
		glDeleteProgram(entry.second);
	}
}

ShaderHandler::ShaderHandler()
{

}

ShaderHandler::~ShaderHandler() 
{
	onDestroy();

}

std::string ShaderHandler::ReadShader(const std::string& fileName_)
{
	std::string shaderCode;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try
	{
		file.open(fileName_.c_str());
		std::stringstream tempStream;
		tempStream << file.rdbuf();
		file.close();
		shaderCode = tempStream.str();
	}
	catch (std::ifstream::failure error_)
	{
		Debug::Error("could not read shader file " + fileName_, "ShaderHandler.cpp", __LINE__);
		return "";
	}
	return shaderCode;
	
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_)
{
	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCode = source_.c_str();
	const int shaderLength = source_.size();
	glShaderSource(shader, 1, &shaderCode, &shaderLength);

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult)
	{
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> shaderLog(logLength);
		glGetShaderInfoLog(shader, logLength, NULL, &shaderLog[0]);
		std::string logString(shaderLog.begin(), shaderLog.end());
		Debug::Error("Error compiling shader " + shaderName_ + " Error is: " + logString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}
	return shader;

}
