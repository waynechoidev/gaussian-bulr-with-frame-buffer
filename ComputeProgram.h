#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL\glew.h>

class ComputeProgram
{
public:
	ComputeProgram();

	void createFromFile(std::string fileLocation);

	void use();

	GLuint getID() { return _programID; }

	~ComputeProgram();

private:
	GLuint _programID;

	std::string readFile(std::string fileLocation);
	void compileShader(std::string shaderCode);
	void addShader(GLuint theComputeShader, std::string shaderCode, GLenum shaderType);
	void clear();
};
