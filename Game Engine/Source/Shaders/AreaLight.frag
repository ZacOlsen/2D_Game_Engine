#version 330 core

out vec4 color;

uniform sampler2D imageLight;
uniform sampler2D imageShadow;
uniform vec4 spriteColor;
uniform vec4 lightColor;
uniform vec2 light;
uniform float brightness;

in DATA {
	vec2 uv;
	vec2 texCoord;
	vec2 worldPos;
	vec2 screenPos;
} fs_in;

void main() {

	float intens = brightness / length(fs_in.worldPos - light);

	if(intens > 1.0){
		//color = spriteColor * texture(imageLight, fs_in.texCoord);
		color = lightColor * texture(imageShadow, fs_in.texCoord) + texture(imageShadow, fs_in.texCoord);
		//color = lightColor * (texture(imageShadow, fs_in.texCoord) + vec4(.1f, .1f, .1f, color.w));
	}else{
		color = spriteColor * texture(imageShadow, fs_in.texCoord);
	}

	//if(intens > 1.0){
	//	intens = 1.0;
	//}
	//vec4 shadowCol = texture(imageShadow, fs_in.texCoord);
	//vec4 lightCol = texture(imageLight, fs_in.texCoord);
	//color = mix(shadowCol, lightCol, intens) * spriteColor;
	//color = spriteColor * texture(imageLight, fs_in.texCoord);// * intens * lightColor;
}  
