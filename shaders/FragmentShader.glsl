#version 330 core

in vec2 UV;
in vec3 N;
out vec3 color;

uniform sampler2D texSampler;
uniform vec3 shading;
uniform vec3 lightPosition;
uniform vec3 ambient;

void main()
{
  vec3 matColor = texture(texSampler, UV).rgb * shading;
  color = (ambient * matColor) + 
          clamp( (matColor * dot(normalize(lightPosition),N)), 0,1);
}
