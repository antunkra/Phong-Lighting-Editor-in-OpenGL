#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	Vertex();
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, const glm::vec3& normal);
};

class Mesh {
private:
	unsigned int vertexCnt, indexCnt;
	Vertex* vertexData;
	unsigned int* indices;
	unsigned int VAO, VBO, EBO;

public:
	~Mesh();
	unsigned int getVAO() const;
	unsigned int getElementCount() const;

protected:
	void bufferSetup();
	unsigned int getVertexCount();
	void allocateVertexData(unsigned int numOfVertices);
	void allocateIndexData(unsigned int numOfIndices);
	unsigned int getVBO() const;
	unsigned int getEBO() const;
	Vertex getVertex(int index) const;
	void setVertex(int index, Vertex value);
	void setVertexPosition(int index, glm::vec3 value);
	void setVertexNormal(int index, glm::vec3 value);
	unsigned int getIndex(int index) const;
	void setIndex(int index, unsigned int value);
};

class Sphere : public Mesh {
private:
	float radius;
	int resolution;

public:
	Sphere();
	Sphere(float radius);
	Sphere(float radius, int resolution);

private:
	void generateBufferData();
	void generateVertexPositions();
	void generateVertexNormals();
	void generateIndices();
};

#endif