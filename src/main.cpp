#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "game_object.h"
#include "editor_ui.h"

static GLFWwindow* s_Window;

Shader* gouraudShader;
Shader* phongShader;

float deltaTime;

void glfwSetup() {
	if (!glfwInit())
		std::cout << "Failed to initialize GLFW!" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glfwWindowSetup(GLFWwindow*& window) {
	window = glfwCreateWindow(1000, 800, "Phong lighting in OpenGL", NULL, NULL);
	
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
	glViewport(0, 0, 800, 800);

	gouraudShader = new Shader("shaders/gouraudVertex.glsl", "shaders/gouraudFragment.glsl");
	phongShader = new Shader("shaders/phongVertex.glsl", "shaders/phongFragment.glsl");

	Camera camera;
	Sphere sphere(1.0f, 20);
	Material defaultMaterial;
	GameObject object(&sphere, &defaultMaterial, phongShader);

	Renderer renderer;
	EditorUI editor(s_Window);

	float prevTime = glfwGetTime();
	float currTime;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(s_Window)) {
		currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		editor.draw(object);

		renderer.draw(camera, object);

		glfwSwapBuffers(s_Window);
	}

	delete phongShader;
	delete gouraudShader;
}