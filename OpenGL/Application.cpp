//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//
//#include "Renderer.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexArray.h"
//#include "Shader.h"
//#include "VertexBufferLayout.h"
//#include "Texture.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//
//#define SCREEN_WIDTH	640
//#define SCREEN_HEIGHT	480
//
//int main(void)
//{
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Error !" << std::endl;
//	}
//
//	unsigned int buffer;
//	float position[] = {
//		0.0f,	0.0f,	0.0f,	0.0f,
//		0.0f,	480.0f, 0.0f,	1.0f,
//		640.0f, 480.0f, 1.0f,	1.0f,
//		640.0f, 0.0f,	1.0f,	0.0f,
//	};
//
//	unsigned int indices[] = {
//		0, 1, 2,
//		0, 2, 3
//	};
//
//	VertexArray va;
//	VertexBuffer vb(position, 4 * 4 * sizeof(float));
//
//	VertexBufferLayout layout;
//	layout.Push<float>(2);
//	layout.Push<float>(2);
//	va.AddBuffer(vb, layout);
//	IndexBuffer ib(indices, 6);
//
//	glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
//	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
//	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0));
//
//	glm::mat4 mvp = proj * view * model;
//
//	Shader shader("C:\\Users\\KTD\\source\\repos\\OpenGL\\OpenGL\\Basic.shader");
//	shader.Bind();
//	shader.SetUniform4f("u_Color", 0.0f, 1.0f, 1.0f, 0.0f);
//
//	shader.SetUniformMat4f("u_MVP", proj);
//	
//	Texture texture("C:\\Users\\KTD\\source\\repos\\OpenGL\\OpenGL\\chrnoLogo.PNG");
//	texture.Bind();
//	shader.SetUniform1i("u_Texture", 0);
//
//	va.Unbind();
//	shader.Unbind();
//	vb.Unbind();
//	ib.Unbind();
//
//	Renderer renderer(&shader);
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		renderer.Clear();
//
//		shader.Bind();
//
//		shader.SetUniform4f("u_Color", 0.0f, 1.0f, 1.0f, 0.0f);
//		shader.SetUniform1i("u_Texture", 0);
//		
//		renderer.Draw(va, ib, shader);
//		renderer.DrawLine(0xFF000000, 10, 10, 200, 200, 5);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}