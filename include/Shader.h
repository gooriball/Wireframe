#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);
		~Shader();

		void use();
		
	private:
		void init(const std::string& vertexFile, const std::string& fragmentFile);
		unsigned int compileShader(GLenum type, const std::string& filePath);
		void linkShader();

		unsigned int vertexShader_;
		unsigned int fragmentShader_;
		unsigned int shaderProgram_;
};