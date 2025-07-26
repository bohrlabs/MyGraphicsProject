cmake_minimum_required(VERSION 3.20)
project(ThirdPartyModules CXX)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_library(thirdparty STATIC)

target_sources(thirdparty PRIVATE 
    3rdparty.cpp

)
include(imgui-node-editor.cmake)

target_link_libraries(thirdparty 
PUBLIC 
    imgui::imgui        
    glfw
    GLEW::GLEW
    opengl::opengl
    imgui-node-editor
)

# Optionally, set include directories for consumers
# target_include_directories(thirdparty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, set C++ standard if needed
# target_compile_features(thirdparty PUBLIC cxx_std_14)

# --- Copy PDBs for Debug builds if they exist ---
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # List of possible PDBs to copy (adjust paths as needed)
    set(PDB_FILES
        "${CONAN_LIB_DIRS_GLEW}/libglew32d.pdb"
        "${CONAN_LIB_DIRS_GLFW}/glfw3.pdb"
        "${CONAN_LIB_DIRS_IMGUI}/imgui.pdb"
    )
    foreach(PDB ${PDB_FILES})
        if(EXISTS "${PDB}")
            add_custom_command(TARGET thirdparty POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PDB}" $<TARGET_FILE_DIR:thirdparty>
                COMMENT "Copying ${PDB} to output directory"
            )
        endif()
    endforeach()
endif()

