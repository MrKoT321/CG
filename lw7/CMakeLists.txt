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

set(WINDOW
        Window.cpp
        Window.h
)


add_executable(shader
        ${BASE_SOURCES}
        ${SHADER_SOURCES}
        ${WINDOW}
        canabola/Canabola.h
        transformation/Transformation.h
        main.cpp
)


find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(shader glfw ${OPENGL_LIBRARIES} GLEW)
