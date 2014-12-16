#version 330 core

layout(location = 0) in vec3 aVertexPosition; 
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

out vec3 vPosition_view;
out vec3 vNormal_view;
out vec2 vTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


void main() {

	vec4 vertexPosition = vec4(aVertexPosition, 1); 
  vec4 vertexNormal = vec4(aVertexNormal, 0);
	
	vPosition_view = vec3(uMVMatrix * vertexPosition);
  vNormal_view = vec3(vertexNormal); //*uNormalMatrix * 
  vTexCoords = aVertexTexCoords;

 	gl_Position = uMVPMatrix * vertexPosition;
};