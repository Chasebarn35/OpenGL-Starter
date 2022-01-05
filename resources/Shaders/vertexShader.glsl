#version 400 compatibility
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

uniform float rotation;

void main()
{

float h = sqrt( pow(aPos.x,2) + pow(aPos.y,2) );
gl_Position = vec4(h * cos(acos(aPos.x / h) + rotation ), h * sin(asin(aPos.y / h) + rotation ), aPos.z, 1.0);
vertexColor = aColor;//doesnt actually do anything
TexCoord = vec2(aTexCoord.x,aTexCoord.y);
}