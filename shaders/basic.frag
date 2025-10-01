#version 330 core

out vec4 FragColor;

in float heightNormalized;

uniform vec3 lowColor;
uniform vec3 highColor;

void main()
{
	vec3 color = mix(lowColor, highColor, heightNormalized);
	FragColor = vec4(color, 1.0f);
}