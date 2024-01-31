#include "Quad.h"

Quad::Quad()
{
	_VAO = 0;
	_VBO = 0;
}

void Quad::initialise()
{
	float verts[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f };
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), verts, GL_STATIC_DRAW);
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glEnableVertexAttribArray(0);
	GLintptr stride = 4 * sizeof(float);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(1);
	GLintptr offset = 2 * sizeof(float);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
}

void Quad::draw()
{
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

Quad::~Quad()
{
	if (_VBO != 0)
	{
		glDeleteBuffers(1, &_VBO);
		_VBO = 0;
	}

	if (_VAO != 0)
	{
		glDeleteVertexArrays(1, &_VAO);
		_VAO = 0;
	}
}
