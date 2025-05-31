#include "../../base/GLFWInitializer.h"
#include "Window.h"
#include <GL/glew.h>

#include <cstdlib>

int main()
{
    glewInit();
	GLFWInitializer initGLFW;
    Window window{ 800, 600, "Canabola" };
    window.Run();

    return EXIT_SUCCESS;
}