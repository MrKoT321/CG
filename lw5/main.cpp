#include "../base//GLFWInitializer.h"
#include "labyrinth/Window.h"

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 800, 600, "Labyrinth" };
	window.Run();

	return EXIT_SUCCESS;
}