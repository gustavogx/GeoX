#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace GX {

    static float GetTime() { return (float)glfwGetTime(); }

}