#version 330 core

in vec3 vPosition_vs; 
in vec2 tc;
in vec3 gNormal_view;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform vec3 uCameraPos;

uniform float uPunctLightPos[100];
uniform int uNumberOfPunctLights;

out vec3 fFragColor;

uniform sampler2D uTextureCube;

vec3 blinnPhongDirectional() {
	vec3 rgbText = texture(uTextureCube, tc).rgb ;

	vec3 w0 = normalize(uCameraPos-vPosition_vs);
	vec3 wi = normalize(uLightDir_vs);
	vec3 halfVector = normalize ((w0 + wi) / 2);

	vec3 color = vec3 (1 * (rgbText * (max(0, dot (wi, gNormal_view))) + uKs * pow (max(0, dot (halfVector, gNormal_view)) , uShininess) ));

	return color;
}

vec3 blinnPhongPunctual() {
	vec3 rgbText = texture(uTextureCube, tc).rgb ;
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < uNumberOfPunctLights; i+=3) {
		vec3 lightPos = vec3(
			uPunctLightPos[i],
			uPunctLightPos[i+1],
			uPunctLightPos[i+2]
		);

		vec3 w0 = normalize(-vPosition_vs);
		vec3 wi = normalize(lightPos - vPosition_vs);
		vec3 halfVector = normalize ((w0 + wi) / 2);

		float dist = distance(vPosition_vs, lightPos);
		vec3 lightIntensityAtten = uLightIntensity /( dist * dist);

		vec3 color = vec3 (lightIntensityAtten * (max(0, dot (wi, gNormal_view))) + uKs * pow (max(0, dot (halfVector, gNormal_view)) , uShininess) );

		finalColor = finalColor + color;
	}

	return finalColor * rgbText;
}

void main() {
   fFragColor = max( /*blinnPhongDirectional() +*/ blinnPhongPunctual(), 0);
};
