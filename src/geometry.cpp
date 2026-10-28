#include "geometry.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

Vertex::Vertex() : Vertex(glm::vec3(0.0f, 0.0f, 0.0f)) {}

Vertex::Vertex(const glm::vec3& position) : Vertex(position, glm::vec3(0.0f, 0.0f, 0.0f)) {}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal) : position(position), normal(normal) {}

Mesh::~Mesh() {
	delete[] vertexData;
	delete[] indices;
}

unsigned int Mesh::getVAO() const {
	return VAO;
}
unsigned int Mesh::getElementCount() const {
	return indexCnt;
}

unsigned int Mesh::getVertexCount() {
	return vertexCnt;
}

void Mesh::bufferSetup() {
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


void Mesh::allocateVertexData(unsigned int numOfVertices) {
	vertexCnt = numOfVertices;
	vertexData = new Vertex[vertexCnt];
}
void Mesh::allocateIndexData(unsigned int numOfIndices) {
	indexCnt = numOfIndices;
	indices = new unsigned int[indexCnt];
}
unsigned int Mesh::getVBO() const {
	return VBO;
}
unsigned int Mesh::getEBO() const {
	return EBO;
}
Vertex Mesh::getVertex(int index) const {
	return vertexData[index];
}
void Mesh::setVertex(int index, Vertex value) {
	vertexData[index] = value;
}
void Mesh::setVertexPosition(int index, glm::vec3 value) {
	vertexData[index].position = value;
}
void Mesh::setVertexNormal(int index, glm::vec3 value) {
	vertexData[index].normal = value;
}
unsigned int Mesh::getIndex(int index) const {
	return indices[index];
}
void Mesh::setIndex(int index, unsigned int value) {
	indices[index] = value;
}


void Sphere::generateBufferData() {
	allocateVertexData(2 + resolution * (resolution - 1));

	generateVertexPositions();
	generateVertexNormals();
	generateIndices();
}

void Sphere::generateVertexPositions() {
	setVertexPosition(0, glm::vec3(0.0f, -radius, 0.0f));
	setVertexPosition(1, glm::vec3(0.0f, radius, 0.0f));

	for (int i = 1; i < resolution; i++) {
		float theta = glm::radians(-90.0f) + glm::radians(180.0f) / resolution * i;
		for (int j = 0; j < resolution; j++) {
			float phi = glm::radians(360.0f) / resolution * j;
			float x = radius * glm::cos(theta) * glm::cos(phi);
			float y = radius * glm::sin(theta);
			float z = radius * glm::cos(theta) * glm::sin(phi);
			int index = 2 + (i - 1) * resolution + j;
			setVertexPosition(index, glm::vec3(x, y, z));
		}
	}
}

void Sphere::generateVertexNormals() {
	for (int i = 0; i < getVertexCount(); i++) {
		setVertexNormal(i, glm::normalize(getVertex(i).position));
	}
}

void Sphere::generateIndices() {
	allocateIndexData(6 * resolution * (resolution - 1));

	int index = 0;
	for (int i = 0; i < resolution; i++) {
		setIndex(index++, 0);
		setIndex(index++, 2 + (i + 1) % resolution);
		setIndex(index++, 2 + i);
	}
	for (int i = 0; i < resolution; i++) {
		setIndex(index++, 1);
		setIndex(index++, getVertexCount() - resolution + i);
		setIndex(index++, getVertexCount() - resolution + (i + 1) % resolution);
	}
	for (int i = 0; i < resolution - 2; i++) {
		for (int j = 0; j < resolution; j++) {
			int bottomLeft = 2 + i * resolution + j;
			int bottomRight = 2 + i * resolution + (j + 1) % resolution;
			int topLeft = 2 + (i + 1) * resolution + j;
			int topRight = 2 + (i + 1) * resolution + (j + 1) % resolution;
			setIndex(index++, bottomLeft);
			setIndex(index++, bottomRight);
			setIndex(index++, topLeft);
			setIndex(index++, bottomRight);
			setIndex(index++, topRight);
			setIndex(index++, topLeft);
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
