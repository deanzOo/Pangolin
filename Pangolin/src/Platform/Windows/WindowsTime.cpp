#include "plpch.h"
#include "WindowsTime.h"
#include <GLFW/glfw3.h>

namespace Pangolin {
    Time* Time::create() {
        return new WindowsTime();
    }
    float WindowsTime::get_time() const
    {
        return (float)glfwGetTime();
    }
}
