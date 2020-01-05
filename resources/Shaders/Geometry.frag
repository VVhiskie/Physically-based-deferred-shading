#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;

in vec3 position;
in vec3 normal;
in vec3 uv;

uniform samplerCube albedo;

void main()
{
    gPosition = position;
    gNormal = normal;
    gAlbedo = texture(albedo, uv).rgb;
} 