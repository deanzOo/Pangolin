#version 330 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_texture_coordinate;
in float v_texture_index;
in float v_tile_factor;

uniform sampler2D u_textures[32];

void main() {
	o_color = texture(u_textures[int(v_texture_index)], v_texture_coordinate * v_tile_factor) * v_color;
}