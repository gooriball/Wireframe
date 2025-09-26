#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

class Shader
{
	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);
		~Shader();

		void setMat4(const std::string& name, const glm::mat4& mat);

		void use();
		
	private:
		void init(const std::string& vertexFile, const std::string& fragmentFile);
		unsigned int compileShader(GLenum type, const std::string& filePath);
		void linkShader();

		unsigned int vertexShader_;
		unsigned int fragmentShader_;
		unsigned int shaderProgram_;
};