cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)
find_package(X11 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)

set(SOIL_SOURCES
        lib/soil/src/SOIL.c
        lib/soil/src/image_DXT.c
        lib/soil/src/image_helper.c
        lib/soil/src/stb_image_aug.c
)

set(TEXTURE
        ../texture/Texture.h
        ../texture/TextureLoader.cpp
        ../texture/TextureLoader.h
)

set(BASE_SOURCES
        ../base/BaseWindow.cpp
        ../base/BaseWindow.h
        ../base/GLEWInitializer.h
        ../base/GLFWInitializer.h
)

add_executable(labyrinth
        main.cpp
        labyrinth/Labyrinth.h
        labyrinth/Window.h
        labyrinth/Window.cpp
        labyrinth/Labyrinth.cpp
        ${BASE_SOURCES}
        ${SHADER_SOURCES}
        ${TEXTURE}
        ${SOIL_SOURCES}
)

include_directories(${SOIL_INCLUDE_DIR})
target_link_libraries(labyrinth PRIVATE
        OpenGL::GL
        ${GLU_LIBRARY}
        ${X11_LIBRARIES}
        glfw
        glm::glm
        ${GLUT_LIBRARIES}
)

target_include_directories(labyrinth PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)
