#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern float deltaTime;

class Camera {
private:
	glm::vec3 position;
	glm::vec3 lookDirection;
	glm::vec3 upDirection;
	glm::vec3 rightDirection;

	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;

public:
	Camera();
	Camera(const glm::vec3& position);
	Camera(const glm::vec3& position, const glm::vec3& lookAt);
	Camera(const glm::mat4& viewTransform);

	glm::vec3 getPosition() const;
	glm::mat4 getViewTransform() const;
	glm::mat4 getProjectionTransform() const;
	glm::vec3 getLookDirection() const;
	glm::vec3 getUpDirection() const;
	glm::vec3 getRightDirection() const;

	void translate(glm::vec3 direction);
	void rotate(float yaw, float pitch, float roll);
};

class CameraController {
private:
	Camera* camera;
	double moveSensitivity = 3.0;
	double rotateSensitivity = 0.25;

	bool isCameraControlActive = false;

	float pendingYaw;
	float pendingPitch;
	glm::vec2 translationInput;

public:
	CameraController(Camera* camera);

private:
	void rotateCamera();
	void translateCamera();

	void checkCameraActivity(GLFWwindow* window);
	void pollMouseInput(GLFWwindow* window);
	void pollKeyboardInput(GLFWwindow* window);

public:
	void checkInputs(GLFWwindow* window);
	void applyCameraMovement();
};

#endif