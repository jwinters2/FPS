#version 330 core

in vec2 UV;
out vec3 color;

uniform sampler2D texSampler;
uniform vec3 shading;

void main()
{
  color = texture(texSampler, UV).rgb;
  color.x *= shading.x;
  color.y *= shading.y;
  color.z *= shading.z;
}
