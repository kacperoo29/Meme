#version 330 core
out vec4 color;

in vec3 vPosition;
in vec2 vTexCoords;
in vec3 vNormal;

uniform sampler2D cubeTexture;
uniform samplerCube skybox;
uniform vec3 uCameraPos;

void main()
{    
    color = texture(cubeTexture, vTexCoords);
}