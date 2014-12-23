#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; 

void main() {
	vec4 vertexPosition = vec4(aVertexPosition, 1);

	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	gl_Position = vec4(uMVPMatrix * vertexPosition);
}

