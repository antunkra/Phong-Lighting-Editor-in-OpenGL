#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "game_object.h"

class Renderer {
public:
	static void draw(const Camera& camera, GameObject& gameObject);
};

#endif
