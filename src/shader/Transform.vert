#version 330

uniform mat4 world_transform;
uniform mat4 view_transform;

in vec3 in_position;

void main()
{
    vec4 pos = vec4(in_position, 1.0);

    gl_Position = pos * world_transform * view_transform;
}