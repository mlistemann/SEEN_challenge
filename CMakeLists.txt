cmake_minimum_required(VERSION 3.11)

project(SEEN_challenge)

add_subdirectory(ext/GLFW ext/GLFW/build)
# TODO: use post-build command to copy the generated .lib file into deps/lib/

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARY})

