#include "geometry.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Vertex::Vertex() : Vertex(glm::vec3(0.0f, 0.0f, 0.0f)) {}

Vertex::Vertex(const glm::vec3& position) : Vertex(position, glm::vec3(0.0f, 0.0f, 0.0f)) {}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal) : position(position), normal(normal) {}

void Sphere::bufferSetup() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCnt * sizeof(Vertex), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCnt * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);
}

void Sphere::generateBufferData() {
	vertexCnt = 2 + resolution * (resolution - 1);
	vertexData = new Vertex[vertexCnt];

	generateVertexPositions();
	generateVertexNormals();
	generateIndices();
}

void Sphere::generateVertexPositions() {
	vertexData[0].position = glm::vec3(0.0f, -radius, 0.0f);
	vertexData[1].position = glm::vec3(0.0f, radius, 0.0f);

	for (int i = 1; i < resolution; i++) {
		float theta = glm::radians(-90.0f) + glm::radians(180.0f) / resolution * i;
		for (int j = 0; j < resolution; j++) {
			float phi = glm::radians(360.0f) / resolution * j;
			float x = radius * glm::cos(theta) * glm::cos(phi);
			float y = radius * glm::sin(theta);
			float z = radius * glm::cos(theta) * glm::sin(phi);
			int index = 2 + (i - 1) * resolution + j;
			vertexData[index].position = glm::vec3(x, y, z);
		}
	}
}

void Sphere::generateVertexNormals() {
	for (int i = 0; i < vertexCnt; i++) {
		vertexData[i].normal = glm::normalize(vertexData[i].position);
	}
}

void Sphere::generateIndices() {
	indexCnt = 6 * resolution * (resolution - 1);
	indices = new unsigned int[indexCnt];

	int index = 0;
	for (int i = 0; i < resolution; i++) {
		indices[index++] = 0;
		indices[index++] = 2 + (i+1) % resolution;
		indices[index++] = 2 + i;
	}
	for (int i = 0; i < resolution; i++) {
		indices[index++] = 1;
		indices[index++] = vertexCnt - resolution + i;
		indices[index++] = vertexCnt - resolution + (i + 1) % resolution;
	}
	for (int i = 0; i < resolution - 2; i++) {
		for (int j = 0; j < resolution; j++) {
			int bottomLeft = 2 + i * resolution + j;
			int bottomRight = 2 + i * resolution + (j + 1) % resolution;
			int topLeft = 2 + (i + 1) * resolution + j;
			int topRight = 2 + (i + 1) * resolution + (j + 1) % resolution;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
			indices[index++] = topLeft;
			indices[index++] = bottomRight;
			indices[index++] = topRight;
			indices[index++] = topLeft;
		}
	}
}

Sphere::Sphere(float radius, int resolution) : radius(radius), resolution(resolution) {
	assert(resolution > 2);
	generateBufferData();
	bufferSetup();
}

Sphere::Sphere(float radius) : Sphere(radius, 20) {}

Sphere::Sphere() : Sphere(0.5f) {}

Sphere::~Sphere() {
	delete[] vertexData;
	delete[] indices;
}


unsigned int Sphere::getVAO() const {
	return VAO;
}
unsigned int Sphere::getVertexCount() const {
	return vertexCnt;
}
unsigned int Sphere::getElementCount() const {
	return indexCnt;
}