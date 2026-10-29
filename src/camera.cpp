#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, 10.0f)) {}

Camera::Camera(const glm::vec3& position) : Camera(position, position + glm::vec3(0.0f, 0.0f, -1.0f)) {}

Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt) :
	position(position),
	lookDirection(lookAt - position),
	viewTransform(glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f))), 
	projectionTransform(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)) {}

void Camera::translate(const glm::vec3& direction) {
	position += direction;
	//viewTransform = glm::translate(viewTransform, direction);
	viewTransform = glm::lookAt(position, position + lookDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::rotate(const float& yaw, const float& pitch, const float& roll) {
	glm::mat4 transformation = glm::mat4(1.0f);
	transformation = glm::rotate(transformation, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	transformation = glm::rotate(transformation, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	transformation = glm::rotate(transformation, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 lookDirection4 = transformation * glm::vec4(lookDirection.x, lookDirection.y, lookDirection.z, 0.0f);

	lookDirection = glm::vec3(lookDirection4.x, lookDirection4.y, lookDirection.z);
	viewTransform = glm::lookAt(position, position + lookDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}