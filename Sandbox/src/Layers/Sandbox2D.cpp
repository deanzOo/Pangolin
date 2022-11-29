#include "plpch.h"
#include "Sandbox2D.h"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D(): Pangolin::Layer("Sandbox2D"), _camera_controller(1280.0f / 720.0f, true)
{
}

void Sandbox2D::on_attach()
{
	PL_PROFILE_FUNCTION();
	
	_texture = Pangolin::Texture2D::create("assets/textures/PL.png");
	_sprite_sheet = Pangolin::Texture2D::create("assets/textures/RPGpack_sheet_2X.png");
	_stairs_sprite = Pangolin::SubTexture2D::create_from_coordinates(_sprite_sheet, { 7, 6 }, { 128, 128 });
	_barrel_sprite = Pangolin::SubTexture2D::create_from_coordinates(_sprite_sheet, { 8, 2 }, { 128, 128 });
	_tree_sprite = Pangolin::SubTexture2D::create_from_coordinates(_sprite_sheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Pangolin::Timestep step)
{
	PL_PROFILE_FUNCTION();
	
	_camera_controller.on_update(step);

	Pangolin::Renderer2D::reset_statistics();

	{
		PL_PROFILE_SCOPE("Renderer Prep");

		Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
		Pangolin::RenderCommand::clear();
	}

	{
		PL_PROFILE_SCOPE("Renderer Draw");
		_rotation += 2.0f;

		Pangolin::Renderer2D::begin_scene(_camera_controller.get_camera());
		/*Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Pangolin::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Pangolin::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _texture, 1.0f);

		Pangolin::Renderer2D::draw_rotated_quad({ 7.0f, 7.0f, -0.1f }, { 5.0f, 5.0f }, _rotation, _texture);
		Pangolin::Renderer2D::draw_rotated_quad({ -7.0f, -7.0f }, { 0.8f, 0.8f }, -45.0f, _square_color);

		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
				Pangolin::Renderer2D::draw_quad({ x, y, 0.1f }, { 0.45f, 0.45f }, color);
			}
		}*/
		Pangolin::Renderer2D::draw_quad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, _stairs_sprite);
		Pangolin::Renderer2D::draw_quad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, _barrel_sprite);
		Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, _tree_sprite);
		Pangolin::Renderer2D::end_scene();

	}
}

void Sandbox2D::on_imgui_render()
{
	PL_PROFILE_FUNCTION();
	
	ImGui::Begin("Settings");

	auto stats = Pangolin::Renderer2D::get_stats();

	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.draw_calls);
	ImGui::Text("Quads: %d", stats.quad_count);
	ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
	ImGui::Text("Indices: %d", stats.get_total_index_count());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));

	ImGui::End();
}

void Sandbox2D::on_event(Pangolin::Event& event)
{
	_camera_controller.on_event(event);
}
