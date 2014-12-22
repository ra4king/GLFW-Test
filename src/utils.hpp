#pragma once

#include <string>
#include <epoxy/gl.h>

std::string* readFile(const char*);

GLuint createProgram(std::string* vertShader, std::string* fragShader);
