#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

void createMaterialEditor(const std::string& name, Material& material, Shader& phongShader, Shader& gouraudShader, Shader& activeShader) {
	ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Color:");
	ImGui::ColorPicker3("##color", glm::value_ptr(material.color), ImGuiColorEditFlags_NoInputs);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Diffuse Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##diffuseReflectivity", &material.diffuseReflectivity, 0.01f, 0.0f, 10.0f);
	
	ImGui::Text("Specular Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##specularReflectivity", &material.specularReflectivity, 0.01f, 0.0f, 10.0f);

	ImGui::Text("Specular Exponent: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##specularExponent", &material.specularExponent, 0.1f, 0.0f, 100.0f);

	ImGui::Text("Ambient Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##ambientReflectivity", &material.ambientReflectivity, 0.01f, 0.0f, 10.0f);

	ImGui::Text("Emmisivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##emissivity", &material.emissivity, 0.01f, 0.0f, 10.0f);


	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::Text("Switch between Phong/Gouraud shading:");
	static bool phongShaderActive = true;
	if (ImGui::Button("Switch shaders", ImVec2(150.0f, 20.0f))) {
		if (!phongShaderActive) {
			phongShader.use();
			activeShader = phongShader;
		}
		else {
			gouraudShader.use();
			activeShader = gouraudShader;
		}
		phongShaderActive = !phongShaderActive;
	}

	ImGui::End();
}

int main() {
	glfwSetup();
	glfwWindowSetup(s_Window);
	gladSetup();
	glViewport(0, 0, 800, 800);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(s_Window, true);
	ImGui_ImplOpenGL3_Init();

	Shader gouraudShader("shaders/gouraudVertex.glsl", "shaders/gouraudFragment.glsl");
	Shader phongShader("shaders/phongVertex.glsl", "shaders/phongFragment.glsl");
	Shader activeShader = phongShader;

	phongShader.use();

	Camera camera;
	Sphere sphere(1.0f, 20);

	Renderer renderer;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(s_Window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		createMaterialEditor("Sphere Material Editor", sphere.material, phongShader, gouraudShader, activeShader);

		renderer.draw(activeShader, camera, sphere);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(s_Window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}