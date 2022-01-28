#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D _tex;

void main()
{
	FragColor = vec4(texture(_tex, TexCoords).rgb, 1.0);
}