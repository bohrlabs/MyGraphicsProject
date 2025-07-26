cmake_minimum_required(VERSION 3.20)
project(MyGraphicsProject CXX)

# Suppress LNK4099 warning on MSVC (Visual Studio)
if (MSVC)
    add_link_options(/ignore:4099)
endif()



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

#	imnodes
    thirdparty
)

add_subdirectory(3rdparty)
target_link_libraries(${PROJECT_NAME} PRIVATE thirdparty)

target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_BACKEND_DIR}")



#set startup project for visual studio

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()


