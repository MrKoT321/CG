#include <GL/glew.h>

#include "Window.h"

#include "../base/GLFWInitializer.h"

#include <cstdlib>

int main()
{
    glewInit();
	GLFWInitializer initGLFW;
    Window window(800, 600, "Shaders");
    window.Run();

    return EXIT_SUCCESS;
}