#version 330 core

layout (location = 0) in vec2 uv;

in vec2 screenPos;
in vec2 texCoord;

out DATA {
	vec2 uv;
	vec2 texCoord;
	vec2 screenPos;
} vs_out;

void main() {

	gl_Position = vec4(screenPos, 1, 1);

	vs_out.uv = uv;
	vs_out.texCoord = texCoord;
	vs_out.screenPos = screenPos;
}
