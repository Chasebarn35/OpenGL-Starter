#version 400 compatibility
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
uniform float rotation;

void main()
{

float h = sqrt( pow(aPos.x,2) + pow(aPos.y,2) );
gl_Position = vec4(h * cos(acos(aPos.x / h) + rotation), h * sin(asin(aPos.y / h) + rotation), aPos.z, 1.0);
vertexColor = vec4(0.6, 0.0, 0.0, 1.0);
}