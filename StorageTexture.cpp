#include "StorageTexture.h"

StorageTexture::StorageTexture()
{
	_textureID = 0;
}

void StorageTexture::initialise(glm::vec2 size)
{
	glGenTextures(1, &_textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);

	glBindImageTexture(0, _textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void StorageTexture::useToCompute()
{
	glActiveTexture(GL_TEXTURE0);
	glBindImageTexture(0, _textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void StorageTexture::useToDraw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void StorageTexture::clear()
{
	glDeleteTextures(1, &_textureID);
	_textureID = 0;
}

StorageTexture::~StorageTexture()
{
	clear();
}