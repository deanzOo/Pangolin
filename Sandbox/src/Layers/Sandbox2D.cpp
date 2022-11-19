#include "plpch.h"
#include "Sandbox2D.h"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D(): Pangolin::Layer("Sandbox2D"), _camera_controller(1280.0f / 720.0f, true)
{
}

void Sandbox2D::on_attach()
{
	_texture = Pangolin::Texture2D::create("assets/textures/PL.png");
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Pangolin::Timestep step)
{
	_camera_controller.on_update(step);

	Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
	Pangolin::RenderCommand::clear();

	Pangolin::Renderer2D::begin_scene(_camera_controller.get_camera());
	Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, _square_color);
	Pangolin::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.8f, 0.2f, 0.3f, 1.0f});
	Pangolin::Renderer2D::draw_quad({ 0.0f, 0.5f, -0.1f }, { 5.0f, 5.0f }, _texture);
	Pangolin::Renderer2D::end_scene();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));
	float pos[3] = { _square_pos.x, _square_pos.y, _square_pos.z };
	ImGui::InputFloat3("Square Pos", pos, NULL, NULL);
	_square_pos = { pos[0], pos[1], pos[2] };

	ImGui::End();
}

void Sandbox2D::on_event(Pangolin::Event& event)
{
	_camera_controller.on_event(event);
}
