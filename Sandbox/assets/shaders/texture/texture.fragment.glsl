#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_texture_coord;

uniform sampler2D u_texture;

void main() {
	o_color = texture(u_texture, v_texture_coord);
}