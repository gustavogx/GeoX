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
    src/Logger.cpp
    src/Application.cpp
    src/Layer.cpp
    src/LayerStack.cpp
    src/ImGui.cpp
    src/ImGuiLayer.cpp
    src/Platform/LinuxWindow.cpp
    src/Platform/LinuxInput.cpp
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

