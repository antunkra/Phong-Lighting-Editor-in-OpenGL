#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "GameObject.h"

class Renderer {
public:
	static void draw(const Camera& camera, GameObject& gameObject);
};

#endif
