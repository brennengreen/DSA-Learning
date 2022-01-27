#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D _tex;

void main()
{
	if (distance(FragPos, vec3(0.0, 0.0, 0.0)) > 0.49 && distance(FragPos, vec3(0.0, 0.0, 0.0)) <= 0.5) {
		FragColor = vec4(1.0);
	} else if (distance(FragPos, vec3(0.0, 0.0, 0.0)) > 0.5) {
		discard;
	} else {
		FragColor = vec4(texture(_tex, TexCoords).rgb, 1.0);
	}
}