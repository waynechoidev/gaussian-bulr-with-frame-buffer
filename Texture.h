#pragma once

#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>

class Texture
{
public:
	Texture();

	void initialise();
	void initialise(const char* fileLoc);
	void use();
	void clear();

	glm::vec2 getSize() { return glm::vec2(_width, _height); }
	GLuint getId() { return _textureID; }

	~Texture();

private:
	GLuint _textureID;
	int _width, _height, _bitDepth;
};