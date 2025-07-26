# CMake configuration for imgui-node-editor as a static library

cmake_minimum_required(VERSION 3.20)

# Set the source directory for imgui-node-editor
set(IMGUI_NODE_EDITOR_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui-node-editor")



file(GLOB IMGUI_NODE_EDITOR_HEADERS
    "${IMGUI_NODE_EDITOR_DIR}/*.h"
    "${IMGUI_NODE_EDITOR_DIR}/*.hpp"
)
file(GLOB IMGUI_NODE_EDITOR_SOURCES
    "${IMGUI_NODE_EDITOR_DIR}/*.cpp"
    "${IMGUI_NODE_EDITOR_DIR}/*.c"
)

# Create the static library target
add_library(imgui-node-editor STATIC)

target_sources(imgui-node-editor PRIVATE
${IMGUI_NODE_EDITOR_HEADERS}
${IMGUI_NODE_EDITOR_SOURCES}
imgui-node-editor.cmake

)

# Set include directories for consumers
target_include_directories(imgui-node-editor PUBLIC
    "${IMGUI_NODE_EDITOR_DIR}"
)

# Check if imgui::imgui target is available
if(TARGET imgui::imgui)
    target_link_libraries(imgui-node-editor PUBLIC imgui::imgui)
else()
    message(FATAL_ERROR "imgui::imgui target not found. Please make sure ImGui is available and imported as imgui::imgui.")
endif()

# Set C++ standard
target_compile_features(imgui-node-editor PUBLIC cxx_std_14)

# Optionally, set properties or definitions if needed
# target_compile_definitions(imgui-node-editor PUBLIC SOME_DEFINE)