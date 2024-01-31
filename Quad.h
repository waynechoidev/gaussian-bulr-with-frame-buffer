#pragma once
#include <GL\glew.h>

class Quad
{
public:
	Quad();

	void initialise();
	void draw();

	~Quad();

private:
	GLuint _VAO, _VBO;
};

