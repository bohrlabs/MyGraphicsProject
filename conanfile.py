from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake

class MyGraphicsProjectConan(ConanFile):
    name = "my_graphics_project"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "imgui/1.90.5",
        "glfw/3.4",
        "glew/2.2.0",
        "opengl/system",
        "implot/0.16",

    )
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
