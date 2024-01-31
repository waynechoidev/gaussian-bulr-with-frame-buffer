#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include<stdlib.h>

class StorageTexture
{
public:
	StorageTexture();

	void initialise(glm::vec2 size);
	void useToCompute();
	void useToDraw();
	void clear();

	~StorageTexture();

private:
	GLuint _textureID;
};