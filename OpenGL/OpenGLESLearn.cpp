#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <Renderer.h>
#include <iostream>

void GraphicsInit()
{
	Renderer::Instance().initializeRenderer();
}

void GraphicsResize(int width, int height)
{
	Renderer::Instance().resize(width, height);
}

void GraphicsRender()
{
	Renderer::Instance().setUpProjection();
	Renderer::Instance().render();
}

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

int main(void)
{
	// Init windows
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	GraphicsInit();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Render graphic
		GraphicsRender();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}