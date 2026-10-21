#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;

public:
	Camera();
	Camera(const glm::vec3& position);
	Camera(const glm::vec3& position, const glm::vec3& lookAt);
	Camera(const glm::mat4& viewTransform);
};

#endif