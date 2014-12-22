#version 440

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;

out vec4 color;

void main() {
	gl_Position = pos;
	color = col;
}
