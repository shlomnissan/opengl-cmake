# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

cmake_minimum_required(VERSION 3.22.1)

project(opengl-cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(${CMAKE_SOURCE_DIR}/cmake)

include(cmake/ShaderString.cmake)
ShaderString()

find_package(OpenGL REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(CORE_SOURCES
    src/core/events.h
    src/core/event_dispatcher.h
    src/core/geometry.cpp
    src/core/geometry.h
    src/core/image.h
    src/core/orthographic_camera.cpp
    src/core/orthographic_camera.h
    src/core/perspective_camera.cpp
    src/core/perspective_camera.h
    src/core/shaders.cpp
    src/core/shaders.h
    src/core/texture2d.cpp
    src/core/texture2d.h
    src/core/timer.h
    src/core/window.cpp
    src/core/window.h
    src/geometries/box_geometry.cpp
    src/geometries/box_geometry.h
    src/geometries/plane_geometry.cpp
    src/geometries/plane_geometry.h
    src/loaders/image_loader.cpp
    src/loaders/image_loader.h
    src/loaders/loader.h
    src/resources/orbit_controls.cpp
    src/resources/orbit_controls.h
)

set(DEMO_SOURCES
    src/main.cpp
)

set(EXTERNAL_SOURCES
    "${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.cpp"
)

add_executable(opengl-cmake
    ${LIBS_SOURCES}
    ${CORE_SOURCES}
    ${DEMO_SOURCES}
    ${EXTERNAL_SOURCES}
)

target_include_directories(opengl-cmake PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external
)

add_custom_command(
    TARGET opengl-cmake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:opengl-cmake>/assets
)

target_link_libraries(opengl-cmake PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
    imgui::imgui
)