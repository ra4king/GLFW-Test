#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "utils.hpp"

using namespace std;

static void error_callback(int error, const char* description) {
	cout << "Error code " << error << ": " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char** args)
{
	glfwSetErrorCallback(error_callback);

	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	cout << "Epoxy GL Version: " << epoxy_gl_version() << endl;
	cout << "OpenGL Version:  " << glGetString(GL_VERSION) << endl;
	cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << endl;

	const unsigned int TRIANGLE_DATA_SIZE = 3 /* vertices */ * (2 + 3) /* vec2 pos + vec3 col */ * sizeof(float);
	const float triangle[] = {
		0.0f, 0.5f, //pos
		1.0f, 0.0f, 0.0f, //col
		0.5f, -0.5f,
		0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,
		0.0f, 0.0f, 1.0f
	};

	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, TRIANGLE_DATA_SIZE, triangle, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (2 + 3) * sizeof(float), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (2 + 3) * sizeof(float), (void*)(2 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	string* vertShader = readFile("snake.vert");
	string* fragShader = readFile("snake.frag");

	GLuint program;
	if(vertShader && fragShader) {
		program = createProgram(vertShader, fragShader);
		delete vertShader;
		delete fragShader;
	} else {
		cout << "Failed to read shaders!" << endl;
		return -1;
	}

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
