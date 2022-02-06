#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D _tex;

uniform float scale;
uniform float lifetime;
uniform float remaining;
uniform vec3 center;
uniform vec3 color;
void main()
{
	if (distance(center.xy, FragPos.xy) > scale) discard;
	//FragColor = vec4(texture(_tex, TexCoords).rgb*(remaining/lifetime), 1.0);
	//FragColor = vec4(2*scale-distance(center.xy, FragPos.xy));
	FragColor = vec4(20*(scale-distance(center.xy, FragPos.xy))*color*(remaining/lifetime), 1.0);
}