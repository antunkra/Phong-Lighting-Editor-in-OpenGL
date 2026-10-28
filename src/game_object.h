#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "geometry.h"
#include "shader.h"

class GameObject {
public:
	Mesh& mesh;
	Material& material;
	Shader& shader;

	GameObject(Mesh& mesh, Material& material, Shader& shader) : 
		mesh(mesh), 
		material(material), 
		shader(shader) { }
};

#endif
