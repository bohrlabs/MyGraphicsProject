cmake_minimum_required(VERSION 3.20)
project(MyGraphicsProject CXX)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

get_target_property(IMGUI_PATH imgui::imgui INTERFACE_INCLUDE_DIRECTORIES)
get_filename_component(IMGUI_BACKEND_DIR "${IMGUI_PATH}/../res/bindings" ABSOLUTE)
message(STATUS IMGUI_PATH: ${IMGUI_BACKEND_DIR})

add_executable(${PROJECT_NAME}
    src/main.cpp
   src/imgui_impl_glfw.cpp
   src/imgui_impl_opengl3.cpp
   #"${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp"
   # "${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        imgui::imgui
        glfw
        GLEW::GLEW
        opengl::opengl
)

target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_BACKEND_DIR}")
