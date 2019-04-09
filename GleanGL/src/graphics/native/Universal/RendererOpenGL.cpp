#ifndef GLEAN_USE_VULKAN

#include "OpenGL/GleanGL.h"
#include "../../Renderer.h"

using namespace Glean::graphics;

Renderer::Renderer(__internalWindow window) : window(window) {
	context = Glean::graphics::initGL(window);
    
    glGenVertexArrays(1, &vaoID);
    
    glBindVertexArray(vaoID);
}

void Renderer::clearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers() {
    Glean::graphics::swapBuffers(context);
}

#endif
