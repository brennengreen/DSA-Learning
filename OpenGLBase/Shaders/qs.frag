#version 460 core
out vec4 FragColor;

in vec3 FragPos;

layout(binding = 0) uniform sampler2D _tex;

void main()
{
	FragColor = vec4(1.0);
}