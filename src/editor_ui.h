#ifndef EDITOR_UI
#define EDITOR_UI

#include <string>
#include "game_object.h"
#include <GLFW/glfw3.h>

class EditorUI {
private:
	GLFWwindow* window;
public:
	EditorUI(GLFWwindow* window);
	~EditorUI();

	void createMaterialEditor(const std::string& name, GameObject& gameObject);
	void createRenderingOptionsEditor(const std::string& name, GameObject& gameObject);
	void createFramerateText(const float deltaTime);

	void draw(GameObject& gameObject);
};

#endif