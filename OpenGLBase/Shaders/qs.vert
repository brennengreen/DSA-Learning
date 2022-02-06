#version 460 core
layout (location = 0) in vec4 vertex;

out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;

void main() {
	TexCoords = vertex.zw;
	FragPos = vec3(model * vec4(vertex.xy, 0.0, 1.0));
    gl_Position = model * vec4(vertex.xy, 0.0, 1.0);
}