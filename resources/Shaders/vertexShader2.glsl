#version 400 compatibility
layout (location = 0) in vec3 aPos;
void main()
{
 gl_Position = vec4(aPos.x/2 + 0.1f, aPos.y/2 + 0.1f, aPos.z, 1.0);
}