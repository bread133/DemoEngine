#version 330 core

in vec2 fragment_texture;

out vec4 res_texture;
uniform sampler2D our_texture;

void main(){
    res_texture = texture(our_texture, fragment_texture);
}