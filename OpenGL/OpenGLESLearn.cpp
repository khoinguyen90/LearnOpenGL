#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <Renderer.h>
#include <iostream>

bool leftBtnHold = false;

void mouse_position_callback(GLFWwindow* window, double x, double y)
{
	if (leftBtnHold == true)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Renderer::Instance().TouchEventMove(xpos, ypos);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		leftBtnHold = true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Renderer::Instance().TouchEventDown(xpos, ypos);
		// Tap event
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		leftBtnHold = false;
		// Release event
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Renderer::Instance().TouchEventRelease(xpos, ypos);
	}
}

void GraphicCallbackSetup(GLFWwindow* window)
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_position_callback);
}

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
#define SCREEN_HEIGHT	800

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

	GraphicCallbackSetup(window);
	GraphicsInit();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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