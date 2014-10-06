#version 150 core

uniform sampler2D diffuseTex;

uniform vec3  cameraPos;
uniform vec4  lightColour;
uniform vec3  lightPos;
uniform float lightRadius;
uniform sampler2D vertexTexture;

in Vertex {
	vec3 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} IN;

out vec4 gl_FragColor;

void main(void){
	vec4 diffuse = texture(diffuseTex, IN.texCoord);
	
	vec3 incident = normalize(lightPos - IN.worldPos);
	float gradient = 1 - IN.normal.y;
	
	float lambert = max(0.0, dot(incident, IN.normal));
	float dist = length(lightPos - IN.worldPos);
	float atten = 1.0 - clamp(dist / lightRadius, 0.0, 1.0);

	vec3 viewDir = normalize(cameraPos - IN.worldPos);
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir, IN.normal));
	float sFactor = pow(rFactor, 50.0);

	
	vec3 colour = (diffuse.rgb * lightColour.rgb);
	colour += (lightColour.rgb * sFactor) * 0.33;
	gl_FragColor = vec4(colour * atten * lambert, diffuse.a);

	float localGradient = clamp((gradient - 0.3) * 1.25, 0, 1);
	localGradient = smoothstep(0.3,0.8,gradient);
	//localGradient = pow(localGradient, 0.75);
	gl_FragColor.rgb += (mix(diffuse.rgb, diffuse.rgb, localGradient) * lightColour.rgb) * 0.5;
	
	if(gl_FragColor.a < 0.95) discard;
	//gl_FragColor.rgb = texture(vertexTexture, IN.texCoord).xxx;
	//gl_FragColor.a = 1.0;
}