#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
  
out vec4 vertexColor;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 worldPos = vec4(in_position, 1.0);

    vertexColor = vec4(1.0, 1.0, 1.0, 1.0);

    gl_Position = projection * view * worldPos;
}