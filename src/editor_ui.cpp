#include "editor_ui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Shader* phongShader;
extern Shader* gouraudShader;

extern float deltaTime;

EditorUI::EditorUI(GLFWwindow* window) : window(window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
}

EditorUI::~EditorUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorUI::draw(GameObject& gameObject) { // function name doesn't fully describe it's scope, we sometimes change the gameobject via the editorUI
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	createMaterialEditor("Sphere Material Editor", gameObject);
	createRenderingOptionsEditor("Rendering Options", gameObject);
	ImGui::End();

	createFramerateText(deltaTime);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::createMaterialEditor(const std::string& name, GameObject& gameObject) {
	ImGui::BeginChild(name.c_str(), ImVec2(0, 0), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders);

	ImGui::Text("Color:");
	ImGui::ColorPicker3("##color", glm::value_ptr(gameObject.material->color), ImGuiColorEditFlags_NoInputs);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Diffuse Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##diffuseReflectivity", &gameObject.material->diffuseReflectivity, 0.01f, 0.0f, 10.0f);

	ImGui::Text("Specular Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##specularReflectivity", &gameObject.material->specularReflectivity, 0.01f, 0.0f, 10.0f);

	ImGui::Text("Specular Exponent: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##specularExponent", &gameObject.material->specularExponent, 0.1f, 0.0f, 100.0f);

	ImGui::Text("Ambient Reflectivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##ambientReflectivity", &gameObject.material->ambientReflectivity, 0.01f, 0.0f, 10.0f);

	ImGui::Text("Emmisivity: ");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(60);
	ImGui::DragFloat("##emissivity", &gameObject.material->emissivity, 0.01f, 0.0f, 1.0f);

	ImGui::EndChild();
}

void EditorUI::createRenderingOptionsEditor(const std::string& name, GameObject& gameObject) {
	ImGui::BeginChild(name.c_str(), ImVec2(0, 0), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders);

	ImGui::Text("Switch between Phong/Gouraud shading:");
	static bool phongShaderActive = true;
	if (ImGui::Button("Switch shaders", ImVec2(150.0f, 20.0f))) {
		if (!phongShaderActive) {
			gameObject.shader = phongShader;
		}
		else {
			gameObject.shader = gouraudShader;
		}
		phongShaderActive = !phongShaderActive;
	}

	ImGui::EndChild();
}

void EditorUI::createFramerateText(const float deltaTime) {
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::Begin("Framerate", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

	ImGui::Text("FPS: ");
	ImGui::SameLine();
	ImGui::Text("%.0f", 1 / deltaTime);

	ImGui::End();
}