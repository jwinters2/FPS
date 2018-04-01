#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 N;

uniform mat4 MVP;
uniform mat4 MV;

void main()
{
  gl_Position = MVP * vec4(vertexPos,1);
  UV = vertexUV;
  N = (inverse(transpose(MV)) * vec4(vertexNormal, 1)).xyz;
}
