#ifndef GLEAN_USE_VULKAN

#include "OpenGL/GleanGL.h"
#include "../Renderer.h"

using namespace Glean::graphics;

Renderer::Renderer(__internalWindow window) : window(window) {
	context = Glean::graphics::initGL(window);
}

void Renderer::clearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Renderer::swapBuffers() {
#ifdef _WIN32
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!SwapBuffers(context)) printf("Swap buffers failed...\n");
#endif
}

#endif