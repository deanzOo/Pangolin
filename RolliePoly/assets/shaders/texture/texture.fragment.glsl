#version 330 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_texture_coordinate;
in float v_texture_index;
in float v_tile_factor;

uniform sampler2D u_textures[32];

void main() {
	switch (int(v_texture_index)) {
		case 0: o_color = texture(u_textures[0], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 1: o_color = texture(u_textures[1], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 2: o_color = texture(u_textures[2], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 3: o_color = texture(u_textures[3], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 4: o_color = texture(u_textures[4], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 5: o_color = texture(u_textures[5], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 6: o_color = texture(u_textures[6], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 7: o_color = texture(u_textures[7], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 8: o_color = texture(u_textures[8], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 9: o_color = texture(u_textures[9], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 10: o_color = texture(u_textures[10], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 11: o_color = texture(u_textures[11], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 12: o_color = texture(u_textures[12], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 13: o_color = texture(u_textures[13], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 14: o_color = texture(u_textures[14], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 15: o_color = texture(u_textures[15], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 16: o_color = texture(u_textures[16], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 17: o_color = texture(u_textures[17], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 18: o_color = texture(u_textures[18], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 19: o_color = texture(u_textures[19], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 20: o_color = texture(u_textures[20], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 21: o_color = texture(u_textures[21], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 22: o_color = texture(u_textures[22], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 23: o_color = texture(u_textures[23], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 24: o_color = texture(u_textures[24], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 25: o_color = texture(u_textures[25], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 26: o_color = texture(u_textures[26], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 27: o_color = texture(u_textures[27], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 28: o_color = texture(u_textures[28], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 29: o_color = texture(u_textures[29], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 30: o_color = texture(u_textures[30], v_texture_coordinate * v_tile_factor) * v_color; break;
		case 31: o_color = texture(u_textures[31], v_texture_coordinate * v_tile_factor) * v_color; break;
	}
}