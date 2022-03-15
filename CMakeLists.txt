cmake_minimum_required(VERSION 3.11)

project(OpenGL)

# Dependencies
# -- submodules
add_subdirectory(ext/GLFW ext/GLFW/build EXCLUDE_FROM_ALL)
add_subdirectory(ext/glm ext/glm/build EXCLUDE_FROM_ALL)

# -- system packages
find_package(OpenGL REQUIRED)

# -- sources
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/ext/glad/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/ext/glad/include")

# Group external libraries in a "Dependencies" folder in the IDE
set_property(TARGET glfw PROPERTY FOLDER "Dependencies")
set_property(TARGET glad PROPERTY FOLDER "Dependencies")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/main.cpp
)
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/IndexBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/VertexBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Window.h
)

# Collect glm headers (only needed for display in VS solution explorer)
file(GLOB_RECURSE GLM_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/glm/**.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/glm/**.inl"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${GLM_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm ${OPENGL_LIBRARY})

# Make 'OpenGL' the default startup project in Visual Studio
if (MSVC_IDE)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/ext/" PREFIX "3rd party" FILES ${GLM_HEADERS})
endif()