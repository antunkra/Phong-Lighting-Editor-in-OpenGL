#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "material.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	Vertex();
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, const glm::vec3& normal);
};

class Sphere {
private:
	float radius;
	int vertexCnt, indexCnt;
	Vertex* vertexData;
	unsigned int* indices;
	int resolution;
	unsigned int VAO, VBO, EBO;
public:
	Material material;

public:
	Sphere();
	Sphere(float radius);
	Sphere(float radius, int resolution);
	~Sphere();

	unsigned int getVAO() const;
	unsigned int getVertexCount() const;
	unsigned int getElementCount() const;

private:
	void bufferSetup();
	void generateBufferData();
	void generateVertexPositions();
	void generateVertexNormals();
	void generateIndices();
};

#endif