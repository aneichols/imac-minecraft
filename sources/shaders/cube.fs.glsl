#version 330 core

in vec3 vPosition_vs; 
in vec2 tc;
in vec3 gNormal_view;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform vec3 uCameraPos;

out vec3 fFragColor;

uniform sampler2D uTextureCube;
//uniform sampler2D uTextureSky;

vec3 blinnPhong(){
	vec3 rgbText = texture(uTextureCube, tc).rgb ;

	vec3 w0 = normalize(uCameraPos-vPosition_vs);
	vec3 wi = normalize(uLightDir_vs);
	vec3 halfVector = normalize ((w0 + wi) / 2);

	float dist = distance(vPosition_vs, uLightPos_vs);
	vec3 lightIntensityAtten = uLightIntensity /( dist * dist);

	vec3 color = vec3 (1 * (rgbText * (max(0, dot (wi, gNormal_view))) + uKs * pow (max(0, dot (halfVector, gNormal_view)) , uShininess) ));

	return color;
};

void main() {
   fFragColor = max( blinnPhong(), 0);
};
