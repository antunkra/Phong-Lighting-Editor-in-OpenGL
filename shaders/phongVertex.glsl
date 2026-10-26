#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

out vec3 fragmentNormal;

uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main() {
	fragmentNormal = vertexNormal;
	gl_Position = projectionTransform * viewTransform * vec4(vertexPosition, 1.0f);
}