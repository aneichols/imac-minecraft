#version 330 core

in vec3 vPosition_vs; 
in vec2 tc;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
   fFragColor = texture(uTexture, tc).rgb;
};