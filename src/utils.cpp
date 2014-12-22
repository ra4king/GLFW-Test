#include <iostream>
#include <fstream>
#include <vector>

#include "utils.hpp"

using namespace std;

string* readFile(const char* filename) {
	vector<char> file;

	ifstream fileStream(filename);
	if(fileStream.is_open())
	{
		#define BUF_SIZE 1024
		char buf[BUF_SIZE];
		while(!fileStream.eof()) {
			fileStream.read(buf, BUF_SIZE);
			file.insert(file.end(), buf, buf + fileStream.gcount());
		}
	} else {
		return NULL;
	}
	
	fileStream.close();

	return new string(file.begin(), file.end());
}

static GLuint createShader(string* shaderSource, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if(shader == -1)
		return -1;

	const GLchar* shaders[] = { shaderSource->c_str() };
	GLint shadersLengths[] = { (GLint)shaderSource->size() };

	glShaderSource(shader, 1, shaders, shadersLengths);

	glCompileShader(shader);

	GLint param;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
	if(param != GL_TRUE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char infoLog[infoLogLength];
		int actualInfoLogLength;
		glGetShaderInfoLog(shader, infoLogLength, &actualInfoLogLength, infoLog);

		cout << "Log: " << infoLog << endl;
	}

	return shader;
}

GLuint createProgram(string* vertShader, string* fragShader) {
	GLuint vert = createShader(vertShader, GL_VERTEX_SHADER);
	GLuint frag = createShader(fragShader, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();

	glAttachShader(program, vert);
	glAttachShader(program, frag);

	glLinkProgram(program);

	glDetachShader(program, vert);
	glDetachShader(program, frag);
	glDeleteShader(vert);
	glDeleteShader(frag);

	return program;
}
