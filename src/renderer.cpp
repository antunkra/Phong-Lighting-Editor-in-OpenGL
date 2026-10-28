#include "renderer.h"
#include "game_object.h"

void Renderer::draw(const Camera& camera, GameObject& gameObject) {
	gameObject.shader.setMatrix4("viewTransform", camera.viewTransform);
	gameObject.shader.setMatrix4("projectionTransform", camera.projectionTransform);
	gameObject.shader.setVector3("viewpointDirection", glm::vec3(0.0f, 0.0f, 1.0f)); // TODO: MAKE viewpointDirection A CAMERA FIELD

	gameObject.shader.setVector3("lightDirection", glm::vec3(0.58f, 0.58f, 0.58f));

	gameObject.shader.setVector3("materialColor", gameObject.material.color);
	gameObject.shader.setFloat("diffuseReflectivity", gameObject.material.diffuseReflectivity);
	gameObject.shader.setFloat("specularReflectivity", gameObject.material.specularReflectivity);
	gameObject.shader.setFloat("specularExponent", gameObject.material.specularExponent);
	gameObject.shader.setFloat("ambientReflectivity", gameObject.material.ambientReflectivity);
	gameObject.shader.setFloat("emissivity", gameObject.material.emissivity);

	gameObject.shader.use();
	glBindVertexArray(gameObject.mesh.getVAO());
	glDrawElements(GL_TRIANGLES, gameObject.mesh.getElementCount(), GL_UNSIGNED_INT, (void*) 0);
}