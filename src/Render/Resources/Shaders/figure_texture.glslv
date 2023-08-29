#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

out vec2 fragment_texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
     fragment_texture = vertex_texture;
     gl_Position = projection * view * model * vec4(vertex_pos, 1.0);
}