#version 330 core

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

in vec3 vPosition_view[];
in vec3 vNormal_view[];
in vec2 vTexCoords[];

out vec3 gPosition_view;
out vec3 gNormal_view;

void main(void) {
	int i;
	for(i = 0; i < gl_in.length(); i++) {
		gl_Position = gl_in[i].gl_Position;
		gPosition_view = vPosition_view[i];
		gNormal_view = vNormal_view[i];
		EmitVertex();
	}

	EndPrimitive();
}
