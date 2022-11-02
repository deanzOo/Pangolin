#include "gepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h> // Will drag system OpenGL headers
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "GamEngine/App.h"
#include "GamEngine/Events/KeyEvent.h"

namespace GamEngine {
    static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key)
    {
        switch (key)
        {
        case GLFW_KEY_TAB: return ImGuiKey_Tab;
        case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
        case GLFW_KEY_UP: return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
        case GLFW_KEY_HOME: return ImGuiKey_Home;
        case GLFW_KEY_END: return ImGuiKey_End;
        case GLFW_KEY_INSERT: return ImGuiKey_Insert;
        case GLFW_KEY_DELETE: return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE: return ImGuiKey_Space;
        case GLFW_KEY_ENTER: return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
        case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
        case GLFW_KEY_COMMA: return ImGuiKey_Comma;
        case GLFW_KEY_MINUS: return ImGuiKey_Minus;
        case GLFW_KEY_PERIOD: return ImGuiKey_Period;
        case GLFW_KEY_SLASH: return ImGuiKey_Slash;
        case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
        case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
        case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
        case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
        case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
        case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
        case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
        case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
        case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
        case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
        case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
        case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
        case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
        case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
        case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
        case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
        case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
        case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
        case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
        case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
        case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
        case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
        case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
        case GLFW_KEY_MENU: return ImGuiKey_Menu;
        case GLFW_KEY_0: return ImGuiKey_0;
        case GLFW_KEY_1: return ImGuiKey_1;
        case GLFW_KEY_2: return ImGuiKey_2;
        case GLFW_KEY_3: return ImGuiKey_3;
        case GLFW_KEY_4: return ImGuiKey_4;
        case GLFW_KEY_5: return ImGuiKey_5;
        case GLFW_KEY_6: return ImGuiKey_6;
        case GLFW_KEY_7: return ImGuiKey_7;
        case GLFW_KEY_8: return ImGuiKey_8;
        case GLFW_KEY_9: return ImGuiKey_9;
        case GLFW_KEY_A: return ImGuiKey_A;
        case GLFW_KEY_B: return ImGuiKey_B;
        case GLFW_KEY_C: return ImGuiKey_C;
        case GLFW_KEY_D: return ImGuiKey_D;
        case GLFW_KEY_E: return ImGuiKey_E;
        case GLFW_KEY_F: return ImGuiKey_F;
        case GLFW_KEY_G: return ImGuiKey_G;
        case GLFW_KEY_H: return ImGuiKey_H;
        case GLFW_KEY_I: return ImGuiKey_I;
        case GLFW_KEY_J: return ImGuiKey_J;
        case GLFW_KEY_K: return ImGuiKey_K;
        case GLFW_KEY_L: return ImGuiKey_L;
        case GLFW_KEY_M: return ImGuiKey_M;
        case GLFW_KEY_N: return ImGuiKey_N;
        case GLFW_KEY_O: return ImGuiKey_O;
        case GLFW_KEY_P: return ImGuiKey_P;
        case GLFW_KEY_Q: return ImGuiKey_Q;
        case GLFW_KEY_R: return ImGuiKey_R;
        case GLFW_KEY_S: return ImGuiKey_S;
        case GLFW_KEY_T: return ImGuiKey_T;
        case GLFW_KEY_U: return ImGuiKey_U;
        case GLFW_KEY_V: return ImGuiKey_V;
        case GLFW_KEY_W: return ImGuiKey_W;
        case GLFW_KEY_X: return ImGuiKey_X;
        case GLFW_KEY_Y: return ImGuiKey_Y;
        case GLFW_KEY_Z: return ImGuiKey_Z;
        case GLFW_KEY_F1: return ImGuiKey_F1;
        case GLFW_KEY_F2: return ImGuiKey_F2;
        case GLFW_KEY_F3: return ImGuiKey_F3;
        case GLFW_KEY_F4: return ImGuiKey_F4;
        case GLFW_KEY_F5: return ImGuiKey_F5;
        case GLFW_KEY_F6: return ImGuiKey_F6;
        case GLFW_KEY_F7: return ImGuiKey_F7;
        case GLFW_KEY_F8: return ImGuiKey_F8;
        case GLFW_KEY_F9: return ImGuiKey_F9;
        case GLFW_KEY_F10: return ImGuiKey_F10;
        case GLFW_KEY_F11: return ImGuiKey_F11;
        case GLFW_KEY_F12: return ImGuiKey_F12;
        default: return ImGuiKey_None;
        }
    }

    static int ImGui_ImplGlfw_KeyToModifier(int key)
    {
        if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
            return GLFW_MOD_CONTROL;
        if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
            return GLFW_MOD_SHIFT;
        if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
            return GLFW_MOD_ALT;
        if (key == GLFW_KEY_LEFT_SUPER || key == GLFW_KEY_RIGHT_SUPER)
            return GLFW_MOD_SUPER;
        return 0;
    }

    static void ImGui_ImplGlfw_UpdateKeyModifiers(int mods)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(ImGuiMod_Ctrl, (mods & GLFW_MOD_CONTROL) != 0);
        io.AddKeyEvent(ImGuiMod_Shift, (mods & GLFW_MOD_SHIFT) != 0);
        io.AddKeyEvent(ImGuiMod_Alt, (mods & GLFW_MOD_ALT) != 0);
        io.AddKeyEvent(ImGuiMod_Super, (mods & GLFW_MOD_SUPER) != 0);
    }

    static int ImGui_ImplGlfw_TranslateUntranslatedKey(int key, int scancode)
    {
        #if GLFW_HAS_GETKEYNAME && !defined(__EMSCRIPTEN__)
        // GLFW 3.1+ attempts to "untranslate" keys, which goes the opposite of what every other framework does, making using lettered shortcuts difficult.
        // (It had reasons to do so: namely GLFW is/was more likely to be used for WASD-type game controls rather than lettered shortcuts, but IHMO the 3.1 change could have been done differently)
        // See https://github.com/glfw/glfw/issues/1502 for details.
        // Adding a workaround to undo this (so our keys are translated->untranslated->translated, likely a lossy process).
        // This won't cover edge cases but this is at least going to cover common cases.
        if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_EQUAL)
            return key;
        const char* key_name = glfwGetKeyName(key, scancode);
        if (key_name && key_name[0] != 0 && key_name[1] == 0)
        {
            const char char_names[] = "`-=[]\\,;\'./";
            const int char_keys[] = { GLFW_KEY_GRAVE_ACCENT, GLFW_KEY_MINUS, GLFW_KEY_EQUAL, GLFW_KEY_LEFT_BRACKET, GLFW_KEY_RIGHT_BRACKET, GLFW_KEY_BACKSLASH, GLFW_KEY_COMMA, GLFW_KEY_SEMICOLON, GLFW_KEY_APOSTROPHE, GLFW_KEY_PERIOD, GLFW_KEY_SLASH, 0 };
            IM_ASSERT(IM_ARRAYSIZE(char_names) == IM_ARRAYSIZE(char_keys));
            if (key_name[0] >= '0' && key_name[0] <= '9') { key = GLFW_KEY_0 + (key_name[0] - '0'); }
            else if (key_name[0] >= 'A' && key_name[0] <= 'Z') { key = GLFW_KEY_A + (key_name[0] - 'A'); }
            else if (key_name[0] >= 'a' && key_name[0] <= 'z') { key = GLFW_KEY_A + (key_name[0] - 'a'); }
            else if (const char* p = strchr(char_names, key_name[0])) { key = char_keys[p - char_names]; }
        }
        // if (action == GLFW_PRESS) printf("key %d scancode %d name '%s'\n", key, scancode, key_name);
        #else
        IM_UNUSED(scancode);
        #endif
        return key;
    }

    enum GlfwClientApi
    {
        GlfwClientApi_Unknown,
        GlfwClientApi_OpenGL,
        GlfwClientApi_Vulkan
    };

    struct ImGui_ImplGlfw_Data
    {
        GLFWwindow* Window;
        GlfwClientApi           ClientApi;
        double                  Time;
        GLFWwindow* MouseWindow;
        GLFWcursor* MouseCursors[ImGuiMouseCursor_COUNT];
        ImVec2                  LastValidMousePos;
        bool                    InstalledCallbacks;

        // Chain GLFW callbacks: our callbacks will call the user's previously installed callbacks, if any.
        GLFWwindowfocusfun      PrevUserCallbackWindowFocus;
        GLFWcursorposfun        PrevUserCallbackCursorPos;
        GLFWcursorenterfun      PrevUserCallbackCursorEnter;
        GLFWmousebuttonfun      PrevUserCallbackMousebutton;
        GLFWscrollfun           PrevUserCallbackScroll;
        GLFWkeyfun              PrevUserCallbackKey;
        GLFWcharfun             PrevUserCallbackChar;
        GLFWmonitorfun          PrevUserCallbackMonitor;

        ImGui_ImplGlfw_Data() { memset((void*)this, 0, sizeof(*this)); }
    };

    static ImGui_ImplGlfw_Data* ImGui_ImplGlfw_GetBackendData()
    {
        return ImGui::GetCurrentContext() ? (ImGui_ImplGlfw_Data*)ImGui::GetIO().BackendPlatformUserData : nullptr;
    }

	ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::on_attach()
	{
        GLFWwindow* window = (GLFWwindow*)App::get().get_window().get_native_window();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
        ImGui_ImplGlfw_InitForOpenGL(window, false);
	}

	void ImGuiLayer::on_detach()
	{
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
	}

	void ImGuiLayer::on_update()
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());
		
		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::on_event(Event& event)
	{
        EventDispatcher dispatcher(event);

        dispatcher.dispatch<MouseButtonPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_mouse_button_pressed_event));
        dispatcher.dispatch<MouseButtonReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_mouse_button_released_event));
        dispatcher.dispatch<MouseMovedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_mouse_moved_event));
        dispatcher.dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_mouse_scrolled_event));

        dispatcher.dispatch<KeyPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_key_pressed_event));
        dispatcher.dispatch<KeyReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_key_released_event));
        dispatcher.dispatch<KeyTypedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_key_typed_event));

        dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(ImGuiLayer::on_window_resize_event));
	}
    bool ImGuiLayer::on_mouse_button_pressed_event(MouseButtonPressedEvent& event)
    {
        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());
        int button = event.get_button();
        int mods = event.get_mods();

        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackMousebutton != nullptr && window == bd->Window)
            bd->PrevUserCallbackMousebutton(window, button, GLFW_PRESS, mods);

        ImGui_ImplGlfw_UpdateKeyModifiers(mods);

        ImGuiIO& io = ImGui::GetIO();
        if (button >= 0 && button < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(button, true);

        GE_CORE_INFO("ImGuiLayer: MouseButtonPressedEvent ({0})", button);

        return true;
    }
    bool ImGuiLayer::on_mouse_button_released_event(MouseButtonReleasedEvent& event)
    {
        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());
        int button = event.get_button();
        int mods = event.get_mods();
        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackMousebutton != nullptr && window == bd->Window)
            bd->PrevUserCallbackMousebutton(window, button, GLFW_RELEASE, mods);

        ImGui_ImplGlfw_UpdateKeyModifiers(mods);

        ImGuiIO& io = ImGui::GetIO();
        if (button >= 0 && button < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(button, false);

        GE_CORE_INFO("ImGuiLayer: MouseButtonReleasedEvent ({0})", button);

        return true;
    }
    bool ImGuiLayer::on_mouse_moved_event(MouseMovedEvent& event)
    {
        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());
        float x = event.get_x();
        float y = event.get_y();

        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackCursorPos != nullptr && window == bd->Window)
            bd->PrevUserCallbackCursorPos(window, x, y);

        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(x, y);

        GE_CORE_INFO("ImGuiLayer: MouseMovedEvent ({0},{1})", x, y);

        return true;
    }
    bool ImGuiLayer::on_mouse_scrolled_event(MouseScrolledEvent& event)
    {

        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());
        int x_offset = event.get_x_offset();
        int y_offset = event.get_y_offset();
        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackScroll != nullptr && window == bd->Window)
            bd->PrevUserCallbackScroll(window, x_offset, y_offset);

        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(x_offset, y_offset);

        GE_CORE_INFO("ImGuiLayer: MouseScrolledEvent ({0},{1})", x_offset, y_offset);

        return true;
    }
    bool ImGuiLayer::on_key_pressed_event(KeyPressedEvent& event)
    {
        int keycode = event.get_keycode();
        int scancode = event.get_scancode();
        int mods = event.get_mods();
        GLFWwindow* window = (GLFWwindow *)(App::get().get_window().get_native_window());

        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackKey != nullptr && window == bd->Window)
            bd->PrevUserCallbackKey(window, keycode, scancode, GLFW_PRESS, mods);

        // Workaround: X11 does not include current pressed/released modifier key in 'mods' flags. https://github.com/glfw/glfw/issues/1630
        if (int keycode_to_mod = ImGui_ImplGlfw_KeyToModifier(keycode))
            mods = mods | keycode_to_mod;
        ImGui_ImplGlfw_UpdateKeyModifiers(mods);

        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode);
        io.AddKeyEvent(imgui_key, true);
        io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)

        GE_CORE_INFO("ImGuiLayer: KeyPressedEvent ({0},{1},{2})", keycode, scancode, mods);

        return true;
    }
    bool ImGuiLayer::on_key_released_event(KeyReleasedEvent& event)
    {
        int keycode = event.get_keycode();
        int scancode = event.get_scancode();
        int mods = event.get_mods();
        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());

        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackKey != nullptr && window == bd->Window)
            bd->PrevUserCallbackKey(window, keycode, scancode, GLFW_RELEASE, mods);

        // Workaround: X11 does not include current pressed/released modifier key in 'mods' flags. https://github.com/glfw/glfw/issues/1630
        if (int keycode_to_mod = ImGui_ImplGlfw_KeyToModifier(keycode))
            mods = mods | keycode_to_mod;
        ImGui_ImplGlfw_UpdateKeyModifiers(mods);

        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode);
        io.AddKeyEvent(imgui_key, false);
        io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)

        GE_CORE_INFO("ImGuiLayer: KeyReleasedEvent ({0},{1},{2})", keycode, scancode, mods);

        return true;
    }
    bool ImGuiLayer::on_key_typed_event(KeyTypedEvent& event)
    {
        GLFWwindow* window = (GLFWwindow*)(App::get().get_window().get_native_window());
        unsigned int codepoint = event.get_codepoint();

        ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
        if (bd->PrevUserCallbackChar != nullptr && window == bd->Window)
            bd->PrevUserCallbackChar(window, codepoint);

        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(codepoint);
        GE_CORE_INFO("ImGuiLayer: KeyTypedEvent ({0})", codepoint);
        return true;
    }
    bool ImGuiLayer::on_window_resize_event(WindowResizeEvent& evnet)
    {
        ImGuiIO& io = ImGui::GetIO();
        App& app = App::get();

        int width = app.get_window().get_width();
        int height = app.get_window().get_height();

        io.DisplaySize = ImVec2(width, height);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, width, height);

        GE_CORE_INFO("ImGuiLayer: WindowResizeEvent ({0},{1})", width, height);

        return true;
    }
}

