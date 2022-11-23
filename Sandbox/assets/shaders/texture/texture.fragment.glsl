#version 330 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_texture_coordinate;

uniform vec4 u_color;
uniform float u_tile_factor;
uniform sampler2D u_texture;

void main() {
	o_color = v_color;
	//o_color = texture(u_texture, v_texture_coord * u_tile_factor) * u_color;
}