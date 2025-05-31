cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)

find_package(X11 REQUIRED)

find_package(glfw3 3.3 REQUIRED)

find_package(glm REQUIRED)

add_executable(maze
        main.cpp
)

target_link_libraries(maze PRIVATE
        OpenGL::GL
        ${GLU_LIBRARY}
        ${X11_LIBRARIES}
        glfw
        glm::glm
)

target_include_directories(maze PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)
