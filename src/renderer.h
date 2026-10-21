#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "camera.h"
#include "geometry.h"

class Renderer {
public:
	static void draw(Shader& shader, const Camera& camera, const Sphere& sphere);
};

#endif
