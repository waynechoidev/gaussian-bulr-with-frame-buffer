#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL\glew.h>

class Program
{
public:
	Program();

	void createFromFiles(std::string vertexLocation, std::string fragmentLocation);
	void createFromFiles(std::string vertexLocation, std::string geometryLocation, std::string fragmentLocation);

	void use();

	GLuint getID() { return _programID; }

	~Program();

private:
	GLuint _programID;

	std::string readFile(std::string fileLocation);
	void compileShader(std::string vertexCode, std::string fragmentCode);
	void compileShader(std::string vertexCode, std::string gemoetryCode, std::string fragmentCode);
	void addShader(GLuint theProgram, std::string shaderCode, GLenum shaderType);
	void clear();
};
