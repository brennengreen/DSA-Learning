#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;

void main() {
	TexCoords = aUV;
	FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = model * vec4(aPos, 1.0);
}