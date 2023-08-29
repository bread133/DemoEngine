#version 330 core

in vec2 fragment_texture;

out vec4 res_texture;
uniform sampler2D diffuse_texture;

void main(){
    res_texture = texture(diffuse_texture, fragment_texture);
}