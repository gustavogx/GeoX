cmake_minimum_required(VERSION 3.10)
project(GeoX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdparty/spdlog)
add_subdirectory(3rdparty/imgui)
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glm)


add_library(GeoX
    src/GeoX.cpp
    src/Core/Application.cpp
    src/Core/Logger.cpp
    src/Core/Layer.cpp
    src/Core/LayerStack.cpp
    src/Core/Input/Input.cpp
    src/ImGui/ImGui.cpp
    src/ImGui/ImGuiLayer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/Buffers.cpp
    src/Renderer/Cameras.cpp
    src/Renderer/VertexArray.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/RendererAPI.cpp
    src/Renderer/RendererCommands.cpp
    src/Platform/Linux/LinuxWindow.cpp
    src/Platform/Linux/LinuxInput.cpp
    src/Platform/OpenGL/OpenGLContext.cpp
    src/Platform/OpenGL/OpenGLBuffers.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLRendererAPI.cpp
)

target_include_directories(GeoX 
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(GeoX
    PUBLIC
    spdlog
    imgui
    glfw
    glm
    GL
    GLU
    glad
)

