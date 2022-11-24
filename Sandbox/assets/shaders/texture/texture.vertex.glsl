#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_texture_coordinate;
layout(location = 3) in float i_texture_index;
layout(location = 4) in float i_tile_factor;

uniform mat4 u_view_projection;

out vec2 v_texture_coordinate;
out vec4 v_color;
out float v_texture_index;
out float v_tile_factor;

void main() {
	v_texture_coordinate = i_texture_coordinate;
	v_color = i_color;
	v_texture_index = i_texture_index;
	v_tile_factor = i_tile_factor;
	gl_Position = u_view_projection  * vec4(i_position, 1.0);
}