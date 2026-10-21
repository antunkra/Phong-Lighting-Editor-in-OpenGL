#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
private:
	unsigned int ID;

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	void use();

	void setBool(const std::string& name, const bool& value);
	void setInt(const std::string& name, const int& value);
	void setFloat(const std::string& name, const float& value);
	void setVector3(const std::string& name, const glm::vec3& value);
	void setVector4(const std::string& name, const glm::vec4& value);
	void setMatrix4(const std::string& name, const glm::mat4& value);
	
	static void createShader(unsigned int& id, GLenum shaderType, const std::string& sourceCode);
	static void createProgram(unsigned int& id, unsigned int& vertexShader, unsigned int& fragmentShader);
};

#endif