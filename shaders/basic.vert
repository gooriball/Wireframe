#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertexColor = vec4(0.8f, 0.7f, 0.7f, 1.0f);
}