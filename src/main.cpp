#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

static GLFWwindow* s_Window;

void glfwSetup() {
	if (!glfwInit())
		std::cout << "Failed to initialize GLFW!" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glfwWindowSetup(GLFWwindow*& window) {
	window = glfwCreateWindow(600, 600, "Phong lighting in OpenGL", NULL, NULL);
	
	if (window == NULL) {
		std::cout << "Failed to create GLFW window!" << std::endl;
		exit(-1);
		return;
	}

	glfwMakeContextCurrent(window);
}

void gladSetup() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!" << std::endl;
		exit(-1);
		return;
	}
}

int main() {
	glfwSetup();
	glfwWindowSetup(s_Window);
	gladSetup();
	glViewport(0, 0, 600, 600);

	Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
	shader.use();

	Camera camera;
	Sphere sphere(1.0f, 50);

	Renderer renderer;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(s_Window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.draw(shader, camera, sphere);

		glfwSwapBuffers(s_Window);
		glfwPollEvents();
	}
}