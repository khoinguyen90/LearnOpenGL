#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer.h"
#include "Texture.h"
#include <iostream>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void)
{
	// Init windows
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	float vertices[] =
	{
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		0, 2, 3
	};

	Shader shader{ "D:\\GitSource\\LearnOpenGL\\OpenGL\\Basic.shader" };
	shader.Bind();

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLCall(glGenBuffers(1, &vbo));
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glGenBuffers(1, &ebo));

	glBindVertexArray(vao);

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(2));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Texture texture{"D:\\GitSource\\LearnOpenGL\\OpenGL\\container.JPG"};
	texture.Bind(0);

	Texture otherTexture{ "D:\\GitSource\\LearnOpenGL\\OpenGL\\chrnoLogo.PNG" };
	otherTexture.Bind(1);

	shader.Unbind();

	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glm::mat4 matrix(1.0f);
		//matrix = glm::translate(matrix, glm::vec3(0.15f, 0.0f, 0.0f));
		//matrix = glm::rotate(matrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		shader.Bind();
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);
		otherTexture.Bind(1);
		shader.SetUniform1i("u_OtherTexture", 1);

		glm::mat4 model(1.0f);
		model = glm::rotate(model,  glm::radians((float)glfwGetTime() * 55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.SetUniformMat4f("model", model);

		glm::mat4 view(1.0);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		shader.SetUniformMat4f("view", view);

		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
		shader.SetUniformMat4f("projection", projection);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}