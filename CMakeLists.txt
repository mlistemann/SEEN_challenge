cmake_minimum_required(VERSION 3.11)

project(OpenGL)

add_subdirectory(ext/GLFW ext/GLFW/build EXCLUDE_FROM_ALL)
# TODO: use post-build command to copy the generated .lib file into deps/lib/

find_package(OpenGL REQUIRED)

add_library(glad STATIC "${CMAKE_SOURCE_DIR}/ext/glad/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/ext/glad/include")

set_property(TARGET glfw PROPERTY FOLDER "Dependencies")
set_property(TARGET glad PROPERTY FOLDER "Dependencies")

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/IndexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexArray.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw ${OPENGL_LIBRARY})

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()