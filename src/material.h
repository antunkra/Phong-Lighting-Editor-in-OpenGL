#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

struct Material {
	glm::vec3 color;
	float diffuseReflectivity;
	float specularReflectivity, specularExponent;
	float ambientReflectivity;
	float emissivity;

	Material() : 
		color(glm::vec3(0.0f, 1.0f, 1.0f)), 
		diffuseReflectivity(1.0f), 
		specularReflectivity(1.0f), 
		specularExponent(25.0f), 
		ambientReflectivity(0.0f), 
		emissivity(0.0f) { }
};

#endif