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
    Pangolin::FrameBufferSpecification framebuffer_spec;
    framebuffer_spec.width = 1280;
    framebuffer_spec.height = 720;
    framebuffer_spec.samples = 1;
    _frame_buffer = Pangolin::FrameBuffer::create(framebuffer_spec);
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

        _frame_buffer->bind();

		Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
		Pangolin::RenderCommand::clear();
	}

	{
		PL_PROFILE_SCOPE("Renderer Draw");
		_rotation += 2.0f;

		Pangolin::Renderer2D::begin_scene(_camera_controller.get_camera());
		Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Pangolin::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Pangolin::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _texture, 1.0f);

		Pangolin::Renderer2D::draw_rotated_quad({ 7.0f, 7.0f, -0.1f }, { 5.0f, 5.0f }, _rotation, _texture);
		Pangolin::Renderer2D::draw_rotated_quad({ -7.0f, -7.0f }, { 0.8f, 0.8f }, -45.0f, _square_color);

		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
				Pangolin::Renderer2D::draw_quad({ x, y, 0.1f }, { 0.45f, 0.45f }, color);
			}
		}
		Pangolin::Renderer2D::draw_quad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, _stairs_sprite);
		Pangolin::Renderer2D::draw_quad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, _barrel_sprite);
		Pangolin::Renderer2D::draw_quad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, _tree_sprite);
		Pangolin::Renderer2D::end_scene();
        _frame_buffer->unbind();
	}
}

void Sandbox2D::on_imgui_render()
{
	PL_PROFILE_FUNCTION();
	
	static bool p_open = true;

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;


    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;


    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);


    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            if (ImGui::MenuItem("Close", NULL, false, p_open != NULL)) {
                p_open = false;
                Pangolin::App::get().close();
            }
            ImGui::Separator();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    uint32_t texture_id = _frame_buffer->get_color_attachment_renderer_id();

    {
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
    
    {
        ImGui::Begin("Viewport");
    
        
        ImGui::Image((void*)texture_id, ImVec2(1280, 720));
    
        ImGui::End();

    }

    ImGui::End();
}

void Sandbox2D::on_event(Pangolin::Event& event)
{
	_camera_controller.on_event(event);
}
