cmake_minimum_required(VERSION 3.20)
project(MyGraphicsProject CXX)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(implot REQUIRED)

add_subdirectory(3rdparty/imnodes)

add_executable(${PROJECT_NAME}
    src/main.cpp
   src/imgui_impl_glfw.cpp
   src/imgui_impl_opengl3.cpp
   #"${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp"
   # "${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp"
   
   #text files
    conanfile.py

)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        imgui::imgui
        implot::implot
        glfw
        GLEW::GLEW
        opengl::opengl
	imnodes
)

target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_BACKEND_DIR}")
