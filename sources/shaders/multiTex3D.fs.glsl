#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudsTexture;

void main() {
	vec3 tex1 = texture(uEarthTexture, vTexCoords).xyz;
	vec3 tex2 = texture(uCloudsTexture, vTexCoords).xyz;
	fFragColor = tex1 + tex2;
};