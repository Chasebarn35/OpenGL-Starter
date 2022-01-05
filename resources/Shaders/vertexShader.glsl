#version 400 compatibility
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;

uniform float rotation;

void main()
{

float h = sqrt( pow(aPos.x,2) + pow(aPos.y,2) );
gl_Position = vec4(h * cos(acos(aPos.x / h) + rotation ), h * sin(asin(aPos.y / h) + rotation ), aPos.z, 1.0);
vertexColor = vec4(0.6, 0.0, 0.0, 1.0);//doesnt actually do anything
TexCoord = aTexCoord;
}