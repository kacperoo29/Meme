#version 330 core

layout (location = 0) in vec3 aPosition;	
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
		
out vec3 vPosition;
out vec2 vTexCoords;
out vec3 vNormal;

uniform mat4 uVP;
uniform mat4 uModel;

void main()
{
	vPosition = vec3(uModel * vec4(aPosition, 1.0));
	vTexCoords = aTexCoords;				
	vNormal = mat3(transpose(inverse(uModel))) * aNormal;				
	gl_Position = uVP * uModel * vec4(aPosition, 1.0);
}