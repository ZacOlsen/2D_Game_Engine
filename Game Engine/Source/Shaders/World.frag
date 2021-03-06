#version 330 core

out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColor;
uniform vec4 lightColor;
uniform vec2 light;

in DATA {
	vec2 uv;
	vec2 texCoord;
	vec2 worldPos;
	vec2 screenPos;
} fs_in;

void main() {
	color = spriteColor * texture(image, fs_in.texCoord);
}  
