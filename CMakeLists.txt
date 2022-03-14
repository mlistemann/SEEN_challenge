cmake_minimum_required(VERSION 3.11)

project(OpenGL)

add_subdirectory(ext/GLFW ext/GLFW/build)
# TODO: use post-build command to copy the generated .lib file into deps/lib/

find_package(OpenGL REQUIRED)

add_library(glad STATIC "${CMAKE_SOURCE_DIR}/ext/glad/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/ext/glad/include")

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glad ${GLFW3_LIBRARY} ${OPENGL_LIBRARY})