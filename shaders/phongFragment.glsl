#version 330 core
in vec3 fragmentNormal;

out vec4 color;

uniform vec3 viewpointDirection;
uniform vec3 lightDirection;

uniform vec3 materialColor;
uniform float diffuseReflectivity;
uniform float specularReflectivity;
uniform float specularExponent;
uniform float ambientReflectivity;
uniform float emissivity;

void main() {
	vec3 halfwayVector = normalize(lightDirection + viewpointDirection);

	vec3 diffuseLight = diffuseReflectivity * dot(lightDirection, fragmentNormal) * materialColor;
	vec3 specularLight = specularReflectivity * pow(dot(halfwayVector, fragmentNormal), specularExponent) * vec3(1.0f, 1.0f, 1.0f);
	vec3 ambientLight = ambientReflectivity * materialColor; // gets light from light source
	vec3 emissiveLight = emissivity * materialColor;

	color = vec4(diffuseLight + specularLight + ambientLight + emissiveLight, 1.0f);
}