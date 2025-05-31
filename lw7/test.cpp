#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Создаём окно и OpenGL-контекст
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLEW Test", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // <-- ОБЯЗАТЕЛЬНО!

	// Теперь можно инициализировать GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(glewError));
		return 1;
	}

	// Получаем строку версии OpenGL
	const GLubyte* version = glGetString(GL_VERSION);
	printf("OpenGL version: %s\n", version);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
