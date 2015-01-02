#version 330 core

in vec3 vPosition_vs; 
in vec3 vNormal_vs; 
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTextureSky;

void main() {
   fFragColor = texture(uTextureSky, vTexCoords).rgb;
};