#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D _tex;

uniform float lifetime;
uniform float remaining;
uniform vec3 center;
void main()
{
	if (distance(center.xy, FragPos.xy) > .05) discard;
	FragColor = vec4(texture(_tex, TexCoords).rgb*(remaining/lifetime), 1.0);
}