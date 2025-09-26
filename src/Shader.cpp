#include "Shader.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) :
shaderProgram_(0)
{
	init(vertexFile, fragmentFile);
}

Shader::~Shader()
{
	if (shaderProgram_)
	{
		glDeleteProgram(shaderProgram_);
	}
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	unsigned int location = glGetUniformLocation(shaderProgram_, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::use()
{
	glUseProgram(shaderProgram_);
}

void Shader::init(const std::string& vertexFile, const std::string& fragmentFile)
{
	vertexShader_ = compileShader(GL_VERTEX_SHADER, vertexFile);
	fragmentShader_ = compileShader(GL_FRAGMENT_SHADER, fragmentFile);
	linkShader();
}


unsigned int Shader::compileShader(GLenum type, const std::string& filePath)
{
	unsigned int shader = glCreateShader(type);
	
	std::ifstream shaderFile{filePath};
	if (!shaderFile.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filePath);
	}

	std::string shaderSourceString{(std::istreambuf_iterator<char>(shaderFile)),
									std::istreambuf_iterator<char>()};
	const char* shaderSource = shaderSourceString.c_str();

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		glDeleteShader(shader);
		throw std::runtime_error("ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog));
	}

	return (shader);
}

void Shader::linkShader()
{
	shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, vertexShader_);
	glAttachShader(shaderProgram_, fragmentShader_);
	glLinkProgram(shaderProgram_);

	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram_, 512, NULL, infoLog);
		glDeleteShader(vertexShader_);
		glDeleteShader(fragmentShader_);
		glDeleteProgram(shaderProgram_);
		throw std::runtime_error("ERROR::SHADER::LINK_FAILED\n" + std::string(infoLog));
	}
		
	glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
}