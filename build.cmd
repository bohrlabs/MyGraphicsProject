setlocal
mkdir build
cd build
conan install ..  --build=missing -s build_type=Release
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake
::cmake --build . --config Release
endlocal