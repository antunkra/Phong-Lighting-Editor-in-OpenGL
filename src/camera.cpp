#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, 10.0f)) {}

Camera::Camera(const glm::vec3& position) : Camera(position, position + glm::vec3(0.0f, 0.0f, -1.0f)) {}

Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt) : Camera(glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) {}

Camera::Camera(const glm::mat4& viewTransform)
	: viewTransform(viewTransform), projectionTransform(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)) {}