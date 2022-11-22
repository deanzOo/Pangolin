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
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Pangolin::Timestep step)
{
	PL_PROFILE_FUNCTION();
	
	_camera_controller.on_update(step);

	{
		PL_PROFILE_SCOPE("Renderer Prep");

		Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
		Pangolin::RenderCommand::clear();
	}

	{
		PL_PROFILE_SCOPE("Renderer Draw");

		Pangolin::Renderer2D::begin_scene(_camera_controller.get_camera());
		Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, _square_color);
		Pangolin::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Pangolin::Renderer2D::draw_quad({ 0.0f, 0.5f, -0.1f }, { 5.0f, 5.0f }, _texture, 5.0f, { 0.8f, 0.3f, 0.2f, 1.0f });

		Pangolin::Renderer2D::draw_rotated_quad({ 7.0f, 7.0f, -0.1f }, { 5.0f, 5.0f }, glm::radians(45.0f), _texture);
		Pangolin::Renderer2D::draw_rotated_quad({ -7.0f, -7.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), _square_color);

		Pangolin::Renderer2D::end_scene();
	}
}

void Sandbox2D::on_imgui_render()
{
	PL_PROFILE_FUNCTION();
	
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));

	ImGui::End();
}

void Sandbox2D::on_event(Pangolin::Event& event)
{
	_camera_controller.on_event(event);
}