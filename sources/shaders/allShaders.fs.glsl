#version 330


in vec3 gPosition_view;
in vec3 gNormal_view;
out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;


vec3 blinnPhong(){

	vec3 w0 = normalize(-gPosition_view);
	vec3 wi = normalize(uLightPos_vs - gPosition_view);
	vec3 halfVector = normalize ((w0 + wi) / 2);

	float dist = distance(gPosition_view, uLightPos_vs);
	vec3 lightIntensityAtten = uLightIntensity /( dist * dist);

	vec3 color = vec3 (lightIntensityAtten * (uKd*(max(0, dot (wi, gNormal_view))) + uKs * pow (max(0, dot (halfVector, gNormal_view)) , uShininess) ));
	return color;
};

void main() {
	//fFragColor = blinnPhong();
	fFragColor = gNormal_view * blinnPhong();
};
