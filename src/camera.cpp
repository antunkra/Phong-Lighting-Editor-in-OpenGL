#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, 10.0f)) {}

Camera::Camera(const glm::vec3& position) : Camera(position, position + glm::vec3(0.0f, 0.0f, -1.0f)) {}

Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt) :
	position(position),
	lookDirection(glm::normalize(lookAt - position)),
	upDirection(0.0f, 1.0f, 0.0f),
	rightDirection(glm::normalize(glm::cross(lookDirection, upDirection))),
	viewTransform(glm::lookAt(position, lookAt, upDirection)), 
	projectionTransform(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)) {}

void Camera::translate(glm::vec3 direction) {
	direction = direction.x * rightDirection + direction.y * upDirection + direction.z * lookDirection;
	position += direction;
	viewTransform = glm::lookAt(position, position + lookDirection, upDirection);
}

glm::vec3 Camera::getPosition() const {
	return position;
}

glm::mat4 Camera::getViewTransform() const {
	return viewTransform;
}

glm::mat4 Camera::getProjectionTransform() const {
	return projectionTransform;
}

glm::vec3 Camera::getLookDirection() const {
	return lookDirection;
}

glm::vec3 Camera::getUpDirection() const {
	return upDirection;
}

glm::vec3 Camera::getRightDirection() const {
	return rightDirection;
}

void Camera::rotate(float yaw, float pitch, float roll) {
	glm::mat4 transformation = glm::mat4(1.0f);
	transformation = glm::rotate(transformation, yaw, upDirection);
	transformation = glm::rotate(transformation, pitch, rightDirection);
	transformation = glm::rotate(transformation, roll, -lookDirection);

	glm::vec4 lookDirection4 = transformation * glm::vec4(lookDirection.x, lookDirection.y, lookDirection.z, 0.0f);
	glm::vec4 upDirection4 = transformation * glm::vec4(upDirection.x, upDirection.y, upDirection.z, 0.0f);

	lookDirection = glm::vec3(lookDirection4.x, lookDirection4.y, lookDirection4.z);
	upDirection = glm::vec3(upDirection4.x, upDirection4.y, upDirection4.z);
	rightDirection = glm::normalize(glm::cross(lookDirection, upDirection));

	viewTransform = glm::lookAt(position, position + lookDirection, upDirection);
}

CameraController::CameraController(Camera* camera) : camera(camera) { }

void CameraController::checkInputs(GLFWwindow* window) {
	checkCameraActivity(window);
	pollMouseInput(window);
	pollKeyboardInput(window);
}

void CameraController::checkCameraActivity(GLFWwindow* window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
		isCameraControlActive = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
		isCameraControlActive = false;
	}
}

void CameraController::pollMouseInput(GLFWwindow* window) {
	static double lastX = 0.0, lastY = 0.0;
	double currX, currY;
	glfwGetCursorPos(window, &currX, &currY);

	double deltaX = currX - lastX;
	double deltaY = currY - lastY;

	if (!isCameraControlActive) {
		lastX = currX;
		lastY = currY;
		return;
	}

	pendingYaw = glm::radians(360 * (-deltaX / 1000) * rotateSensitivity);
	pendingPitch = glm::radians(360 * (-deltaY / 1000) * rotateSensitivity);

	lastX = currX;
	lastY = currY;
}

void CameraController::pollKeyboardInput(GLFWwindow* window) {
	if (!isCameraControlActive) {
		translationInput = glm::vec2(0.f, 0.f);
		return;
	}
	translationInput.x = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	translationInput.y = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
}

void CameraController::applyCameraMovement() {
	rotateCamera();
	translateCamera();
}

void CameraController::rotateCamera() {
	static float totalPitch = 0.0f;
	if (totalPitch + pendingPitch > glm::radians(89.0f))
		pendingPitch = glm::radians(89.0f) - totalPitch;
	if (totalPitch + pendingPitch < glm::radians(-89.0f))
		pendingPitch = glm::radians(-89.0f) - totalPitch;
	totalPitch += pendingPitch;
	camera->rotate(pendingYaw, pendingPitch, 0.f);
}

void CameraController::translateCamera() {
	camera->translate(
		glm::vec3(
			translationInput.x * moveSensitivity * deltaTime,
			0.0f,
			translationInput.y * moveSensitivity * deltaTime));
}