set(BASE_SOURCES
        ../base/BaseWindow.cpp
        ../base/BaseWindow.h
        ../base/GLEWInitializer.h
        ../base/GLFWInitializer.h
)

set(SHADER_SOURCES
        ../shader/Program.cpp
        ../shader/Program.h
        ../shader/Shader.h
        ../shader/ShaderProgram.h
)


add_executable(canabola
        ${BASE_SOURCES}
        ${SHADER_SOURCES}
        canabola/Canabola.h
        canabola/Window.cpp
        canabola/Window.h
        canabola/main.cpp
)

add_executable(test test.cpp)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(canabola glfw ${OPENGL_LIBRARIES} GLEW)
target_link_libraries(test glfw ${OPENGL_LIBRARIES} GLEW)