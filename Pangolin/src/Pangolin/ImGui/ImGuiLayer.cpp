#include "plpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "Pangolin/Core/App/App.h"
#include "Pangolin/Events/KeyEvent.h"

namespace Pangolin {
	ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer") {}

	void ImGuiLayer::on_attach()
	{
        PL_PROFILE_FUNCTION();
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());
        const char* glsl_version = "#version 410";

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void ImGuiLayer::on_detach()
	{
        PL_PROFILE_FUNCTION();
        
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	}
    
    void ImGuiLayer::on_event(Event& event)
    {
        if (_blocking_events) {
            ImGuiIO& io = ImGui::GetIO();
            event.handled |= event.is_in_category(EventCategoryMouse) & io.WantCaptureMouse;
            event.handled |= event.is_in_category(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }
    
    void ImGuiLayer::begin()
    {
        PL_PROFILE_FUNCTION();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void ImGuiLayer::end()
    {
        PL_PROFILE_FUNCTION();
        
        ImGuiIO& io = ImGui::GetIO();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}

