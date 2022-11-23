#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_texture_coordinate;

uniform mat4 u_view_projection;

out vec2 v_texture_coordinate;
out vec4 v_color;

void main() {
	v_texture_coordinate = i_texture_coordinate;
	v_color = i_color;
	gl_Position = u_view_projection  * vec4(i_position, 1.0);
}