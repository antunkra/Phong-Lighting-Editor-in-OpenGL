#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 lookDirection;

public:
	glm::vec3 position;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;

public:
	Camera();
	Camera(const glm::vec3& position);
	Camera(const glm::vec3& position, const glm::vec3& lookAt);
	Camera(const glm::mat4& viewTransform);

	void translate(const glm::vec3& direction);
	void rotate(const float& yaw, const float& pitch, const float& roll);
};

#endif