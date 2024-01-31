#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Window.h"
#include "Program.h"
#include "StorageTexture.h"
#include "ComputeProgram.h"
#include "Quad.h"
#include "Texture.h"

GLint WIDTH = 1280;
GLint HEIGHT = 768;

int main()
{
	// Create window
	Window mainWindow = Window(WIDTH, HEIGHT);
	mainWindow.initialise();

	// Quad to draw
	Quad quad = Quad();
	quad.initialise();	

	// Texture
	Texture texInput = Texture();
	texInput.initialise("img.jpg");
	auto texSize = texInput.getSize();
	
	StorageTexture texOutput = StorageTexture();
	texOutput.initialise(glm::vec2(WIDTH,HEIGHT));

	// Frame buffer
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create programs
	Program drawProgram = Program();
	drawProgram.createFromFiles("vertex.glsl", "fragment.glsl");

	ComputeProgram computeProgram = ComputeProgram();
	computeProgram.createFromFile("compute.glsl");

	// Save image to frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawProgram.use();
	texInput.use();
	quad.draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Compute
	computeProgram.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	texOutput.useToCompute();
	glDispatchCompute(ceil(WIDTH / 32.0f), ceil(HEIGHT / 32.0f), 1);

	// Make sure writing to image has finished before read
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	// Wait for the GPU to finish its operation before proceeding
	glFinish();

	while (!mainWindow.getShouldClose()) {

		// Get + Handle user input events
		glfwPollEvents();

		// Clean window
		mainWindow.clear(0.0f, 0.0f, 0.0f, 1.0f);

		// Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawProgram.use();
		texOutput.useToDraw();

		// Draw
		quad.draw();

		mainWindow.swapBuffers();
	}
}