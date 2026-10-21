#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform vec3 viewpointDirection;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

uniform vec3 lightDirection;

uniform vec3 materialColor;
uniform float diffuseReflectivity;
uniform float specularReflectivity;
uniform float specularExponent;
uniform float ambientReflectivity;
uniform float emissivity;

out vec4 color;

void main() {
	vec3 halfwayVector = normalize(lightDirection + viewpointDirection);

	vec3 diffuseLight = diffuseReflectivity * dot(lightDirection, vertexNormal) * materialColor;
	vec3 specularLight = specularReflectivity * pow(dot(halfwayVector, vertexNormal), specularExponent) * vec3(1.0f, 1.0f, 1.0f);
	vec3 ambientLight = ambientReflectivity * materialColor; // gets light from light source
	vec3 emissiveLight = emissivity * materialColor;

	color = vec4(diffuseLight + specularLight + ambientLight + emissiveLight, 1.0f);
	gl_Position = projectionTransform * viewTransform * vec4(vertexPosition, 1.0f);

}