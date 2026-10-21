#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

void Shader::createShader(unsigned int& id, GLenum shaderType, const std::string& sourceCode) {
	const char* sourceCode_cstr = sourceCode.c_str();
	int success;
	char infoLog[512];

	id = glCreateShader(shaderType);
	glShaderSource(id, 1, &sourceCode_cstr, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		if (shaderType == GL_VERTEX_SHADER)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		else if (shaderType == GL_FRAGMENT_SHADER)
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
		std::cout << infoLog << std::endl;
	}
}

void Shader::createProgram(unsigned int& id, unsigned int& vertexShader, unsigned int& fragmentShader) {
	int success;
	char infoLog[512];

	id = glCreateProgram();

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
		std::cout << infoLog << std::endl;
	}
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	unsigned int vertexShader, fragmentShader;
	createShader(vertexShader, GL_VERTEX_SHADER, vertexCode);
	createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentCode);

	createProgram(ID, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, const bool& value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setInt(const std::string& name, const int& value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, const float& value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector3(const std::string& name, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVector4(const std::string& name, const glm::vec4& value) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}