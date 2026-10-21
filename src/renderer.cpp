#include "renderer.h"

#include "material.h"

void Renderer::draw(Shader& shader, const Camera& camera, const Sphere& sphere) {
	shader.setMatrix4("viewTransform", camera.viewTransform);
	shader.setMatrix4("projectionTransform", camera.projectionTransform);
	shader.setVector3("viewpointDirection", glm::vec3(0.0f, 0.0f, 1.0f)); // TODO: MAKE viewpointDirection A CAMERA FIELD

	shader.setVector3("lightDirection", glm::vec3(0.58f, 0.58f, 0.58f));

	shader.setVector3("materialColor", sphere.material.color);
	shader.setFloat("diffuseReflectivity", sphere.material.diffuseReflectivity);
	shader.setFloat("specularReflectivity", sphere.material.specularReflectivity);
	shader.setFloat("specularExponent", sphere.material.specularExponent);
	shader.setFloat("ambientReflectivity", sphere.material.ambientReflectivity);
	shader.setFloat("emissivity", sphere.material.emissivity);

	glBindVertexArray(sphere.getVAO());
	glDrawElements(GL_TRIANGLES, sphere.getElementCount(), GL_UNSIGNED_INT, (void*) 0);
}